#include "../include/KiemTraDuLieu.h"
#include <cctype>
#include <string>
#include <vector>
#include "../include/ChuoiUtf8.h"
#include "../include/Constants.h"

namespace
{
	const unsigned int ASCII_LIMIT = 0x80;
	const unsigned int LATIN_LETTER_FIRST = 0x00C0;
	const unsigned int LATIN_LETTER_LAST = 0x024F;
	const unsigned int MULTIPLICATION_SIGN = 0x00D7;
	const unsigned int DIVISION_SIGN = 0x00F7;
	const unsigned int LATIN_ADDITIONAL_FIRST = 0x1E00;
	const unsigned int LATIN_ADDITIONAL_LAST = 0x1EFF;
	const unsigned int COMBINING_FIRST = 0x0300;
	const unsigned int COMBINING_LAST = 0x036F;
	const unsigned int CONTROL_LIMIT = 0x20;
	const size_t MAX_COMBINING_PER_LETTER = 2;
	const unsigned int DELETE_CODE = 0x7F;

	const char NAME_SEPARATORS[] = " -'";
	const char EMAIL_LOCAL_SPECIALS[] = "._%+-";
	const char EMAIL_AT = '@';
	const char DOT_CHAR = '.';
	const char HYPHEN_CHAR = '-';
	const char UNDERSCORE_CHAR = '_';
	const char DOUBLE_DOT[] = "..";

	const char* const RESERVED_NAMES[] =
	{
		"administrators", "employees", "con", "prn", "aux", "nul"
	};
	const size_t RESERVED_NAME_COUNT = sizeof(RESERVED_NAMES) / sizeof(RESERVED_NAMES[0]);
	const char DEVICE_PREFIX_COM[] = "com";
	const char DEVICE_PREFIX_LPT[] = "lpt";
	const size_t DEVICE_PREFIX_LENGTH = 3;
	const size_t DEVICE_NAME_LENGTH = 4;
	const char DEVICE_NUMBER_FIRST = '1';
	const char DEVICE_NUMBER_LAST = '9';
	const char PHONE_FIRST_DIGIT = '0';
	const size_t MIN_DOMAIN_LABEL_COUNT = 2;
}

/**********************************************************
* @Description Kiem tra username hop le (chu, so, dau gach duoi, do dai cho phep)
*
* @return true neu hop le, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laUsernameHopLe(const std::string& strUsername)
{
	if (strUsername.size() < MIN_USERNAME_LENGTH || strUsername.size() > MAX_USERNAME_LENGTH)
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < strUsername.size(); ++uiViTri)
	{
		const unsigned char cKyTu = static_cast<unsigned char>(strUsername[uiViTri]);

		if (!std::isalnum(cKyTu) && cKyTu != UNDERSCORE_CHAR)
		{
			return false;
		}
	}

	return true;
}

/**********************************************************
* @Description Kiem tra username co phai ten danh rieng cua he thong khong
*
* @return true neu la ten danh rieng (ten file he thong, ten thiet bi), false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laUsernameDanhRieng(const std::string& strUsername)
{
	const std::string strThuong = ChuoiUtf8::chuyenThanhChuThuong(strUsername);

	for (size_t uiViTri = 0; uiViTri < RESERVED_NAME_COUNT; ++uiViTri)
	{
		if (strThuong == RESERVED_NAMES[uiViTri])
		{
			return true;
		}
	}

	return KiemTraDuLieu::laTenThietBi(strThuong);
}

/**********************************************************
* @Description Kiem tra password du manh
*
* @return true neu du do dai, co chu hoa, chu thuong, chu so, ky tu dac biet va khong co khoang trang
**********************************************************/
bool KiemTraDuLieu::laMatKhauManh(const std::string& strMatKhau)
{
	if (strMatKhau.size() < MIN_PASSWORD_LENGTH || strMatKhau.size() > MAX_PASSWORD_LENGTH)
	{
		return false;
	}

	bool bCoChuHoa = false;
	bool bCoChuThuong = false;
	bool bCoChuSo = false;
	bool bCoKyTuDacBiet = false;

	for (size_t uiViTri = 0; uiViTri < strMatKhau.size(); ++uiViTri)
	{
		const unsigned char cKyTu = static_cast<unsigned char>(strMatKhau[uiViTri]);

		if (!std::isgraph(cKyTu))
		{
			return false;
		}

		bCoChuHoa = bCoChuHoa || std::isupper(cKyTu);
		bCoChuThuong = bCoChuThuong || std::islower(cKyTu);
		bCoChuSo = bCoChuSo || std::isdigit(cKyTu);
		bCoKyTuDacBiet = bCoKyTuDacBiet || !std::isalnum(cKyTu);
	}

	return bCoChuHoa && bCoChuThuong && bCoChuSo && bCoKyTuDacBiet;
}

/**********************************************************
* @Description Kiem tra ho ten hop le (chu cai, dau ghep, khoang trang, dau - va ')
*
* @return true neu hop le, false neu nguoc lai
* @attention Ho ten phai da duoc chuan hoa khoang trang
* @attention Do dai tinh theo so chu cai va dau cach, khong tinh dau ghep
* @attention Dau cach, '-' va ''' chi duoc dat sau chu cai (khong dung dau chuoi, khong lien tiep)
* @attention Dau ghep chi duoc bam vao chu cai, toi da MAX_COMBINING_PER_LETTER dau moi chu
* @attention Ho ten phai ket thuc bang chu cai va co it nhat mot khoang trang (>= 2 tu)
**********************************************************/
bool KiemTraDuLieu::laHoTenHopLe(const std::string& strHoTen)
{
	if (strHoTen != ChuoiUtf8::chuanHoaKhoangTrang(strHoTen))
	{
		return false;
	}

	std::vector<unsigned int> vecKyTu;

	if (!ChuoiUtf8::giaiMa(strHoTen, vecKyTu))
	{
		return false;
	}

	// Ky tu ngay truoc la chu cai (hoac dau ghep dang bam vao chu cai).
	bool bTruocLaChuCai = false;
	bool bCoKhoangTrang = false;
	size_t uiSoDauGhep = 0;
	size_t uiSoKyTu = 0;

	for (size_t uiViTri = 0; uiViTri < vecKyTu.size(); ++uiViTri)
	{
		const unsigned int uiMaKyTu = vecKyTu[uiViTri];

		if (KiemTraDuLieu::laChuCai(uiMaKyTu))
		{
			bTruocLaChuCai = true;
			uiSoDauGhep = 0;
			++uiSoKyTu;
		}
		else if (KiemTraDuLieu::laKyTuGhepDau(uiMaKyTu))
		{
			++uiSoDauGhep;

			if (!bTruocLaChuCai || uiSoDauGhep > MAX_COMBINING_PER_LETTER)
			{
				return false;
			}
		}
		else if (KiemTraDuLieu::laKyTuPhanCach(uiMaKyTu))
		{
			if (!bTruocLaChuCai)
			{
				return false;
			}

			bTruocLaChuCai = false;
			bCoKhoangTrang = bCoKhoangTrang || uiMaKyTu == ' ';
			++uiSoKyTu;
		}
		else
		{
			return false;
		}
	}

	if (uiSoKyTu < MIN_FULLNAME_LENGTH || uiSoKyTu > MAX_FULLNAME_LENGTH)
	{
		return false;
	}

	return bTruocLaChuCai && bCoKhoangTrang;
}

/**********************************************************
* @Description Kiem tra dia chi hop le (do dai, khong co ky tu dieu khien)
*
* @return true neu hop le, false neu nguoc lai
* @attention Dia chi phai da duoc chuan hoa khoang trang
**********************************************************/
bool KiemTraDuLieu::laDiaChiHopLe(const std::string& strDiaChi)
{
	const bool bDoDaiHopLe =
		strDiaChi.size() >= MIN_ADDRESS_LENGTH && strDiaChi.size() <= MAX_ADDRESS_LENGTH;

	if (!bDoDaiHopLe || strDiaChi != ChuoiUtf8::chuanHoaKhoangTrang(strDiaChi))
	{
		return false;
	}

	std::vector<unsigned int> vecKyTu;

	if (!ChuoiUtf8::giaiMa(strDiaChi, vecKyTu))
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < vecKyTu.size(); ++uiViTri)
	{
		if (vecKyTu[uiViTri] < CONTROL_LIMIT || vecKyTu[uiViTri] == DELETE_CODE)
		{
			return false;
		}
	}

	return true;
}

/**********************************************************
* @Description Kiem tra so dien thoai hop le
*
* @return true neu gom PHONE_LENGTH chu so va bat dau bang 0, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laSoDienThoaiHopLe(const std::string& strSoDienThoai)
{
	if (strSoDienThoai.size() != PHONE_LENGTH || strSoDienThoai[0] != PHONE_FIRST_DIGIT)
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < strSoDienThoai.size(); ++uiViTri)
	{
		if (!std::isdigit(static_cast<unsigned char>(strSoDienThoai[uiViTri])))
		{
			return false;
		}
	}

	return true;
}

/**********************************************************
* @Description Kiem tra email hop le (phan ten, dau @, ten mien)
*
* @return true neu hop le, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laEmailHopLe(const std::string& strEmail)
{
	if (strEmail.empty() || strEmail.size() > MAX_EMAIL_LENGTH)
	{
		return false;
	}

	const size_t uiViTriAt = strEmail.find(EMAIL_AT);

	if (uiViTriAt == std::string::npos ||
		strEmail.find(EMAIL_AT, uiViTriAt + 1) != std::string::npos)
	{
		return false;
	}

	const std::string strPhanTen = strEmail.substr(0, uiViTriAt);
	const std::string strTenMien = strEmail.substr(uiViTriAt + 1);

	return KiemTraDuLieu::laPhanTenEmailHopLe(strPhanTen) && KiemTraDuLieu::laTenMienHopLe(strTenMien);
}

/**********************************************************
* @Description Kiem tra ma ky tu co phai chu cai (bao gom chu Latin co dau)
*
* @return true neu la chu cai, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laChuCai(const unsigned int uiMaKyTu)
{
	if (uiMaKyTu < ASCII_LIMIT)
	{
		return std::isalpha(static_cast<int>(uiMaKyTu)) != 0;
	}

	if (uiMaKyTu >= LATIN_LETTER_FIRST && uiMaKyTu <= LATIN_LETTER_LAST)
	{
		return uiMaKyTu != MULTIPLICATION_SIGN && uiMaKyTu != DIVISION_SIGN;
	}

	return uiMaKyTu >= LATIN_ADDITIONAL_FIRST && uiMaKyTu <= LATIN_ADDITIONAL_LAST;
}

/**********************************************************
* @Description Kiem tra ma ky tu co phai dau ghep (combining mark)
*
* @return true neu la dau ghep, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laKyTuGhepDau(const unsigned int uiMaKyTu)
{
	return uiMaKyTu >= COMBINING_FIRST && uiMaKyTu <= COMBINING_LAST;
}

/**********************************************************
* @Description Kiem tra ma ky tu co phai ky tu phan cach trong ten
*
* @return true neu la khoang trang, dau - hoac dau ', false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laKyTuPhanCach(const unsigned int uiMaKyTu)
{
	if (uiMaKyTu >= ASCII_LIMIT)
	{
		return false;
	}

	return std::string(NAME_SEPARATORS).find(static_cast<char>(uiMaKyTu)) != std::string::npos;
}

/**********************************************************
* @Description Kiem tra chuoi co trung ten thiet bi Windows (COM1-9, LPT1-9)
*
* @return true neu trung ten thiet bi, false neu nguoc lai
* @attention Chuoi phai da duoc chuyen thanh chu thuong
**********************************************************/
bool KiemTraDuLieu::laTenThietBi(const std::string& strTenThuong)
{
	if (strTenThuong.size() != DEVICE_NAME_LENGTH)
	{
		return false;
	}

	const std::string strTienTo = strTenThuong.substr(0, DEVICE_PREFIX_LENGTH);
	const char cSo = strTenThuong[DEVICE_PREFIX_LENGTH];
	const bool bTienToHopLe = strTienTo == DEVICE_PREFIX_COM || strTienTo == DEVICE_PREFIX_LPT;

	return bTienToHopLe && cSo >= DEVICE_NUMBER_FIRST && cSo <= DEVICE_NUMBER_LAST;
}

/**********************************************************
* @Description Kiem tra phan ten (truoc dau @) cua email
*
* @return true neu hop le, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laPhanTenEmailHopLe(const std::string& strPhanTen)
{
	if (strPhanTen.empty() || strPhanTen.size() > MAX_EMAIL_LOCAL_LENGTH)
	{
		return false;
	}

	if (strPhanTen[0] == DOT_CHAR || strPhanTen[strPhanTen.size() - 1] == DOT_CHAR ||
		strPhanTen.find(DOUBLE_DOT) != std::string::npos)
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < strPhanTen.size(); ++uiViTri)
	{
		const unsigned char cKyTu = static_cast<unsigned char>(strPhanTen[uiViTri]);
		const bool bKyTuDacBiet =
			std::string(EMAIL_LOCAL_SPECIALS).find(static_cast<char>(cKyTu)) != std::string::npos;

		if (!std::isalnum(cKyTu) && !bKyTuDacBiet)
		{
			return false;
		}
	}

	return true;
}

/**********************************************************
* @Description Kiem tra ten mien cua email (cac nhan cach nhau boi dau cham)
*
* @return true neu hop le, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laTenMienHopLe(const std::string& strTenMien)
{
	size_t uiBatDau = 0;
	size_t uiSoNhan = 0;
	std::string strNhanCuoi;

	// Tach ten mien thanh cac nhan theo dau cham va kiem tra tung nhan.
	while (true)
	{
		const size_t uiViTriCham = strTenMien.find(DOT_CHAR, uiBatDau);
		const size_t uiDoDai =
			(uiViTriCham == std::string::npos) ? std::string::npos : uiViTriCham - uiBatDau;
		const std::string strNhan = strTenMien.substr(uiBatDau, uiDoDai);

		if (!KiemTraDuLieu::laNhanTenMienHopLe(strNhan))
		{
			return false;
		}

		++uiSoNhan;
		strNhanCuoi = strNhan;

		if (uiViTriCham == std::string::npos)
		{
			break;
		}

		uiBatDau = uiViTriCham + 1;
	}

	// Ten mien can it nhat 2 nhan va nhan cuoi (top-level) chi gom chu cai.
	return uiSoNhan >= MIN_DOMAIN_LABEL_COUNT && KiemTraDuLieu::laNhanCuoiHopLe(strNhanCuoi);
}

/**********************************************************
* @Description Kiem tra mot nhan cua ten mien
*
* @return true neu hop le, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laNhanTenMienHopLe(const std::string& strNhan)
{
	if (strNhan.empty() || strNhan[0] == HYPHEN_CHAR || strNhan[strNhan.size() - 1] == HYPHEN_CHAR)
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < strNhan.size(); ++uiViTri)
	{
		const unsigned char cKyTu = static_cast<unsigned char>(strNhan[uiViTri]);

		if (!std::isalnum(cKyTu) && cKyTu != HYPHEN_CHAR)
		{
			return false;
		}
	}

	return true;
}

/**********************************************************
* @Description Kiem tra nhan cuoi (top-level) cua ten mien
*
* @return true neu chi gom chu cai va du do dai toi thieu, false neu nguoc lai
**********************************************************/
bool KiemTraDuLieu::laNhanCuoiHopLe(const std::string& strNhan)
{
	if (strNhan.size() < MIN_EMAIL_TOP_LEVEL_LENGTH)
	{
		return false;
	}

	for (size_t uiViTri = 0; uiViTri < strNhan.size(); ++uiViTri)
	{
		if (!std::isalpha(static_cast<unsigned char>(strNhan[uiViTri])))
		{
			return false;
		}
	}

	return true;
}
