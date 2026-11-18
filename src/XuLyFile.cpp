#include "../include/XuLyFile.h"
#include <cerrno>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include "../include/ChuoiUtf8.h"
#include "../include/DanhSachLienKet.h"
#include "../include/KiemTraDuLieu.h"
#include "../include/HoSoNhanVien.h"
#include "../include/TaiKhoan.h"

namespace
{
	const char BLANK_CHARACTERS[] = " \t\r\n";
}

#ifndef _WIN32
namespace
{
	const int DIRECTORY_MODE = 0755;
}
#endif

/**********************************************************
* @Description Tao thu muc luu du lieu
*
* @return true neu tao thanh cong hoac thu muc da ton tai, false neu nguoc lai
**********************************************************/
bool XuLyFile::taoThuMucDuLieu() const
{
#ifdef _WIN32
	const int iKetQua = _mkdir(DATA_DIRECTORY_NAME);
#else
	const int iKetQua = mkdir(DATA_DIRECTORY_NAME, DIRECTORY_MODE);
#endif

	return (iKetQua == 0) || (errno == EEXIST);
}

/**********************************************************
* @Description Kiem tra username/password theo vai tro
*
* @return true neu co tai khoan khop, false neu nguoc lai
**********************************************************/
bool XuLyFile::kiemTraDangNhap(const std::string& strUsername, const std::string& strPassword,
							   const VaiTro eVaiTro) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(this->layDuongDanTaiKhoan(eVaiTro), danhSach))
	{
		return false;
	}

	return danhSach.timDauTien([&](const TaiKhoan& taiKhoan)
	{
		return taiKhoan.getUsername() == strUsername && taiKhoan.getPassword() == strPassword;
	}) != nullptr;
}

/**********************************************************
* @Description Kiem tra Employee da ton tai theo username
*
* @return true neu ton tai, false neu nguoc lai
**********************************************************/
bool XuLyFile::kiemTraUsernameTonTai(const std::string& strUsername) const
{
	TaiKhoan taiKhoan;

	return this->docTaiKhoan(strUsername, taiKhoan);
}

/**********************************************************
* @Description Kiem tra username da bi trung (khong phan biet hoa thuong)
*
* @return true neu trung, false neu nguoc lai
**********************************************************/
bool XuLyFile::kiemTraUsernameTrung(const std::string& strUsername) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	const std::string strChuan = ChuoiUtf8::chuyenThanhChuThuong(strUsername);

	return danhSach.timDauTien([&](const TaiKhoan& taiKhoan)
	{
		return ChuoiUtf8::chuyenThanhChuThuong(taiKhoan.getUsername()) == strChuan;
	}) != nullptr;
}

/**********************************************************
* @Description Kiem tra so dien thoai da thuoc Employee khac
*
* @return true neu trung, false neu nguoc lai
**********************************************************/
bool XuLyFile::kiemTraTrungSoDienThoai(const std::string& strSoDienThoai, const std::string& strUsernameBoQua) const
{
	return this->kiemTraTrungThongTin(strSoDienThoai, strUsernameBoQua, TruongThongTin::SO_DIEN_THOAI);
}

/**********************************************************
* @Description Kiem tra email da thuoc Employee khac
*
* @return true neu trung, false neu nguoc lai
**********************************************************/
bool XuLyFile::kiemTraTrungEmail(const std::string& strEmail, const std::string& strUsernameBoQua) const
{
	return this->kiemTraTrungThongTin(strEmail, strUsernameBoQua, TruongThongTin::EMAIL);
}

/**********************************************************
* @Description Doc tai khoan Employee theo username
*
* @return true neu tim thay, false neu nguoc lai
**********************************************************/
bool XuLyFile::docTaiKhoan(const std::string& strUsername, TaiKhoan& taiKhoan) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	const TaiKhoan* pTaiKhoan = danhSach.timDauTien([&](const TaiKhoan& taiKhoanDuyet)
	{
		return taiKhoanDuyet.getUsername() == strUsername;
	});

	if (pTaiKhoan == nullptr)
	{
		return false;
	}

	taiKhoan = *pTaiKhoan;
	return true;
}

/**********************************************************
* @Description Doc danh sach tat ca tai khoan Employee
*
* @return true neu doc duoc file, false neu nguoc lai
**********************************************************/
bool XuLyFile::docDanhSachTaiKhoan(DanhSachLienKet<TaiKhoan>& danhSach) const
{
	return this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach);
}

/**********************************************************
* @Description Them tai khoan Employee moi vao file
*
* @return true neu them thanh cong, false neu nguoc lai
* @attention Chua co file tai khoan thi tao moi; file ton tai nhung doc loi thi khong ghi de
**********************************************************/
bool XuLyFile::themTaiKhoan(const TaiKhoan& taiKhoan) const
{
	const std::string strUsername = taiKhoan.getUsername();
	std::string strDuongDanHoSo;

	if (!this->layDuongDanHoSo(strUsername, strDuongDanHoSo) ||
		this->kiemTraUsernameTrung(strUsername))
	{
		return false;
	}

	const bool bFileTonTai = std::ifstream(EMPLOYEE_FILE_PATH).is_open();
	DanhSachLienKet<TaiKhoan> danhSach;

	if (bFileTonTai && !this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	danhSach.themCuoi(taiKhoan);

	return this->ghiFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach);
}

/**********************************************************
* @Description Xoa tai khoan Employee va file ho so tuong ung
*
* @return true neu xoa thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::xoaTaiKhoan(const std::string& strUsername) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	const bool bDaXoa = danhSach.xoaDauTien([&](const TaiKhoan& taiKhoan)
	{
		return taiKhoan.getUsername() == strUsername;
	});

	if (!bDaXoa || !this->ghiFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	std::string strDuongDanHoSo;

	if (this->layDuongDanHoSo(strUsername, strDuongDanHoSo))
	{
		// Ho so co the da bi mat truoc do, khong coi la loi vi tai khoan da duoc xoa.
		static_cast<void>(std::remove(strDuongDanHoSo.c_str()));
	}

	return true;
}

/**********************************************************
* @Description Cap nhat password cua Employee
*
* @return true neu cap nhat thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::capNhatMatKhau(const std::string& strUsername,
							  const std::string& strMatKhauMoi) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	TaiKhoan* pTaiKhoan = danhSach.timDauTien([&](const TaiKhoan& taiKhoan)
	{
		return taiKhoan.getUsername() == strUsername;
	});

	if (pTaiKhoan == nullptr)
	{
		return false;
	}

	pTaiKhoan->setPassword(strMatKhauMoi);
	return this->ghiFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach);
}

/**********************************************************
* @Description Doc ho so nhan vien tu file
*
* @return true neu doc thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::docHoSoNhanVien(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const
{
	std::string strDuongDan;

	if (!this->layDuongDanHoSo(strUsername, strDuongDan))
	{
		return false;
	}

	std::ifstream fileDoc(strDuongDan.c_str());

	if (!fileDoc.is_open())
	{
		return false;
	}

	HoSoNhanVien hoSoNhanVienDoc;
	const bool bDocDuoc = static_cast<bool>(fileDoc >> hoSoNhanVienDoc);

	fileDoc.close();

	if (!bDocDuoc)
	{
		return false;
	}

	hoSoNhanVien = hoSoNhanVienDoc;
	return true;
}

/**********************************************************
* @Description Ghi ho so nhan vien ra file (ghi file tam roi thay the)
*
* @return true neu ghi thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::ghiHoSoNhanVien(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const
{
	std::string strDuongDan;

	if (!this->layDuongDanHoSo(strUsername, strDuongDan))
	{
		return false;
	}

	const std::string strFileTam = strDuongDan + TEMP_EXTENSION;
	std::ofstream fileGhi(strFileTam.c_str(), std::ios::trunc);

	if (!fileGhi.is_open())
	{
		return false;
	}

	fileGhi << hoSoNhanVien;

	const bool bGhiDuoc = fileGhi.good();
	fileGhi.close();

	if (!bGhiDuoc || fileGhi.fail())
	{
		std::remove(strFileTam.c_str());
		return false;
	}

	return this->thayTheFile(strFileTam, strDuongDan);
}

/**********************************************************
* @Description Cap nhat ho so nhan vien da ton tai
*
* @return true neu cap nhat thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::capNhatHoSoNhanVien(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const
{
	HoSoNhanVien hoSoNhanVienHienTai;

	if (!this->docHoSoNhanVien(strUsername, hoSoNhanVienHienTai))
	{
		return false;
	}

	return this->ghiHoSoNhanVien(strUsername, hoSoNhanVien);
}

/**********************************************************
* @Description Lay duong dan file tai khoan theo vai tro
*
* @return Duong dan file, chuoi rong neu vai tro khong hop le
**********************************************************/
std::string XuLyFile::layDuongDanTaiKhoan(const VaiTro eVaiTro) const
{
	switch (eVaiTro)
	{
	case VaiTro::ADMIN:
		return ADMIN_FILE_PATH;

	case VaiTro::EMPLOYEE:
		return EMPLOYEE_FILE_PATH;

	default:
		return "";
	}
}

/**********************************************************
* @Description Tao duong dan file ho so tu username
*
* @return true neu username hop le, false neu nguoc lai
* @attention Chan username khong hop le de tranh duong dan nguy hiem
**********************************************************/
bool XuLyFile::layDuongDanHoSo(const std::string& strUsername, std::string& strDuongDan) const
{
	if (!KiemTraDuLieu::laUsernameHopLe(strUsername) ||
		KiemTraDuLieu::laUsernameDanhRieng(strUsername))
	{
		return false;
	}

	strDuongDan = std::string(DATA_DIRECTORY) + strUsername + PROFILE_EXTENSION;
	return true;
}

/**********************************************************
* @Description Doc toan bo tai khoan tu file vao danh sach lien ket
*
* @return true neu mo duoc file, false neu nguoc lai
* @attention Tra ve false va xoa danh sach neu gap dong khong hop le, tranh ghi de lam mat tai khoan
* @attention Dinh dang file: moi tai khoan gom 2 dong (dong 1 la username, dong 2 la password)
**********************************************************/
bool XuLyFile::docFileTaiKhoan(const std::string& strDuongDan,
							   DanhSachLienKet<TaiKhoan>& danhSach) const
{
	danhSach.xoaTatCa();
	std::ifstream fileDoc(strDuongDan.c_str());

	if (!fileDoc.is_open())
	{
		return false;
	}

	std::string strUsername;

	while (std::getline(fileDoc, strUsername))
	{
		// Bo qua dong trong giua cac tai khoan.
		if (strUsername.find_first_not_of(BLANK_CHARACTERS) == std::string::npos)
		{
			continue;
		}

		// Moi tai khoan gom 2 dong: username roi toi password.
		std::string strPassword;
		const bool bCoPassword = static_cast<bool>(std::getline(fileDoc, strPassword));
		std::istringstream luongTaiKhoan(strUsername + '\n' + strPassword + '\n');
		TaiKhoan taiKhoan;

		if (!bCoPassword || !(luongTaiKhoan >> taiKhoan))
		{
			fileDoc.close();
			danhSach.xoaTatCa();
			return false;
		}

		danhSach.themCuoi(taiKhoan);
	}

	fileDoc.close();
	return true;
}

/**********************************************************
* @Description Ghi danh sach tai khoan ra file (ghi file tam roi thay the)
*
* @return true neu ghi thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::ghiFileTaiKhoan(const std::string& strDuongDan, const DanhSachLienKet<TaiKhoan>& danhSach) const
{
	const std::string strFileTam = strDuongDan + TEMP_EXTENSION;
	std::ofstream fileGhi(strFileTam.c_str(), std::ios::trunc);

	if (!fileGhi.is_open())
	{
		return false;
	}

	danhSach.duyet([&fileGhi](const TaiKhoan& taiKhoan)
	{
		fileGhi << taiKhoan;
	});

	const bool bGhiDuoc = fileGhi.good();
	fileGhi.close();

	if (!bGhiDuoc || fileGhi.fail())
	{
		std::remove(strFileTam.c_str());
		return false;
	}

	return this->thayTheFile(strFileTam, strDuongDan);
}

/**********************************************************
* @Description Thay file dich bang file tam
*
* @return true neu doi ten thanh cong, false neu nguoc lai
**********************************************************/
bool XuLyFile::thayTheFile(const std::string& strFileTam, const std::string& strFileDich) const
{
	std::remove(strFileDich.c_str());
	return std::rename(strFileTam.c_str(), strFileDich.c_str()) == 0;
}

/**********************************************************
* @Description Kiem tra gia tri (so dien thoai hoac email) co trung voi Employee khac
*
* @return true neu trung (khong phan biet hoa thuong), false neu nguoc lai
* @attention Bo qua Employee co username la strUsernameBoQua
**********************************************************/
bool XuLyFile::kiemTraTrungThongTin(const std::string& strGiaTri, const std::string& strUsernameBoQua, const TruongThongTin eTruong) const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->docFileTaiKhoan(EMPLOYEE_FILE_PATH, danhSach))
	{
		return false;
	}

	const std::string strGiaTriChuan = ChuoiUtf8::chuyenThanhChuThuong(strGiaTri);
	bool bTrung = false;

	danhSach.duyet([&](const TaiKhoan& taiKhoan)
	{
		HoSoNhanVien hoSoNhanVien;

		if (bTrung || taiKhoan.getUsername() == strUsernameBoQua ||
			!this->docHoSoNhanVien(taiKhoan.getUsername(), hoSoNhanVien))
		{
			return;
		}

		const std::string strHienTai = this->layGiaTriTruong(hoSoNhanVien, eTruong);

		if (ChuoiUtf8::chuyenThanhChuThuong(strHienTai) == strGiaTriChuan)
		{
			bTrung = true;
		}
	});

	return bTrung;
}

/**********************************************************
* @Description Lay gia tri truong thong tin can so sanh trung
*
* @return Gia tri truong, chuoi rong neu truong khong hop le
**********************************************************/
std::string XuLyFile::layGiaTriTruong(const HoSoNhanVien& hoSoNhanVien, const TruongThongTin eTruong) const
{
	switch (eTruong)
	{
	case TruongThongTin::SO_DIEN_THOAI:
		return hoSoNhanVien.getSoDienThoai();

	case TruongThongTin::EMAIL:
		return hoSoNhanVien.getEmail();

	default:
		return "";
	}
}
