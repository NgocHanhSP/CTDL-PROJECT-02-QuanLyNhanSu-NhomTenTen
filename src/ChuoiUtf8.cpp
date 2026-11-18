#include "../include/ChuoiUtf8.h"
#include <cctype>

namespace
{
	const unsigned int ASCII_LIMIT = 0x80;
	const unsigned int LEAD_2_MASK = 0xE0;
	const unsigned int LEAD_2_TAG = 0xC0;
	const unsigned int LEAD_2_DATA = 0x1F;
	const unsigned int LEAD_3_MASK = 0xF0;
	const unsigned int LEAD_3_TAG = 0xE0;
	const unsigned int LEAD_3_DATA = 0x0F;
	const unsigned int LEAD_4_MASK = 0xF8;
	const unsigned int LEAD_4_TAG = 0xF0;
	const unsigned int LEAD_4_DATA = 0x07;
	const unsigned int CONTINUATION_MASK = 0xC0;
	const unsigned int CONTINUATION_TAG = 0x80;
	const unsigned int CONTINUATION_DATA = 0x3F;
	const unsigned int CONTINUATION_SHIFT = 6;
	const unsigned int MIN_CODE_2_BYTES = 0x80;
	const unsigned int MIN_CODE_3_BYTES = 0x800;
	const unsigned int MIN_CODE_4_BYTES = 0x10000;
	const unsigned int MAX_CODE_POINT = 0x10FFFF;
	const unsigned int SURROGATE_FIRST = 0xD800;
	const unsigned int SURROGATE_LAST = 0xDFFF;
	const size_t TRAILING_BYTES_2 = 1;
	const size_t TRAILING_BYTES_3 = 2;
	const size_t TRAILING_BYTES_4 = 3;
}

/**********************************************************
* @Description Giai ma chuoi UTF-8 thanh danh sach ma ky tu (code point)
*
* @return true neu chuoi UTF-8 hop le, false neu nguoc lai
**********************************************************/
bool ChuoiUtf8::giaiMa(const std::string& strNguon, std::vector<unsigned int>& vecKyTu)
{
	vecKyTu.clear();
	size_t uiViTri = 0;

	while (uiViTri < strNguon.size())
	{
		unsigned int uiMaKyTu = 0;
		size_t uiDoDai = 0;

		if (!ChuoiUtf8::docMotKyTu(strNguon, uiViTri, uiMaKyTu, uiDoDai))
		{
			return false;
		}

		vecKyTu.push_back(uiMaKyTu);
		uiViTri += uiDoDai;
	}

	return true;
}

/**********************************************************
* @Description Dem so ky tu (khong phai byte) cua chuoi UTF-8
*
* @return So ky tu
**********************************************************/
size_t ChuoiUtf8::demKyTu(const std::string& strNguon)
{
	size_t uiSoKyTu = 0;

	for (size_t uiViTri = 0; uiViTri < strNguon.size(); ++uiViTri)
	{
		const unsigned int uiByte = static_cast<unsigned char>(strNguon[uiViTri]);

		if ((uiByte & CONTINUATION_MASK) != CONTINUATION_TAG)
		{
			++uiSoKyTu;
		}
	}

	return uiSoKyTu;
}

/**********************************************************
* @Description Lay uiSoKyTu ky tu dau tien cua chuoi
*
* @return Chuoi con gom cac ky tu dau
**********************************************************/
std::string ChuoiUtf8::catKyTu(const std::string& strNguon, const size_t uiSoKyTu)
{
	return strNguon.substr(0, ChuoiUtf8::timViTriByte(strNguon, uiSoKyTu));
}

/**********************************************************
* @Description Bo uiSoKyTu ky tu dau tien cua chuoi
*
* @return Phan chuoi con lai
**********************************************************/
std::string ChuoiUtf8::boKyTuDau(const std::string& strNguon, const size_t uiSoKyTu)
{
	return strNguon.substr(ChuoiUtf8::timViTriByte(strNguon, uiSoKyTu));
}

/**********************************************************
* @Description Xoa khoang trang dau/cuoi va gop nhieu khoang trang lien tiep thanh mot
*
* @return Chuoi da chuan hoa
**********************************************************/
std::string ChuoiUtf8::chuanHoaKhoangTrang(const std::string& strNguon)
{
	std::string strKetQua;
	bool bChoKhoangTrang = false;

	for (size_t uiViTri = 0; uiViTri < strNguon.size(); ++uiViTri)
	{
		const char cKyTu = strNguon[uiViTri];

		if (cKyTu == ' ' || cKyTu == '\t')
		{
			bChoKhoangTrang = !strKetQua.empty();
			continue;
		}

		if (bChoKhoangTrang)
		{
			strKetQua += ' ';
			bChoKhoangTrang = false;
		}

		strKetQua += cKyTu;
	}

	return strKetQua;
}

/**********************************************************
* @Description Chuyen cac chu cai ASCII thanh chu thuong
*
* @return Chuoi da chuyen
* @attention Cac ky tu khong thuoc ASCII duoc giu nguyen
**********************************************************/
std::string ChuoiUtf8::chuyenThanhChuThuong(const std::string& strNguon)
{
	std::string strKetQua = strNguon;

	for (size_t uiViTri = 0; uiViTri < strKetQua.size(); ++uiViTri)
	{
		const unsigned int uiByte = static_cast<unsigned char>(strKetQua[uiViTri]);

		if (uiByte < ASCII_LIMIT)
		{
			strKetQua[uiViTri] = static_cast<char>(std::tolower(static_cast<int>(uiByte)));
		}
	}

	return strKetQua;
}

/**********************************************************
* @Description Doc mot ky tu UTF-8 tai vi tri uiViTri
*
* @return true neu doc duoc ky tu hop le, false neu nguoc lai
* @attention uiMaKyTu tra ve ma ky tu, uiDoDai tra ve so byte cua ky tu
* @attention Tu choi ma qua dai (overlong), surrogate va ma vuot MAX_CODE_POINT
**********************************************************/
bool ChuoiUtf8::docMotKyTu(const std::string& strNguon, const size_t uiViTri,
						   unsigned int& uiMaKyTu, size_t& uiDoDai)
{
	size_t uiSoByteTiep = 0;
	unsigned int uiMa = 0;
	unsigned int uiMaNhoNhat = 0;
	const unsigned int uiByteDau = static_cast<unsigned char>(strNguon[uiViTri]);

	if (!ChuoiUtf8::layThongTinByteDau(uiByteDau, uiSoByteTiep, uiMa, uiMaNhoNhat))
	{
		return false;
	}

	// Chuoi bi cat ngang: khong du byte tiep theo cho ky tu nay.
	if (uiViTri + uiSoByteTiep >= strNguon.size())
	{
		return false;
	}

	// Moi byte tiep theo co dang 10xxxxxx; 6 bit cuoi la du lieu cua ma ky tu.
	for (size_t uiChiSo = 1; uiChiSo <= uiSoByteTiep; ++uiChiSo)
	{
		const unsigned int uiByteTiep = static_cast<unsigned char>(strNguon[uiViTri + uiChiSo]);

		if ((uiByteTiep & CONTINUATION_MASK) != CONTINUATION_TAG)
		{
			return false;
		}

		uiMa = (uiMa << CONTINUATION_SHIFT) | (uiByteTiep & CONTINUATION_DATA);
	}

	// Tu choi ma hoa dai khong can thiet (overlong), surrogate UTF-16 va ma vuot gioi han Unicode.
	const bool bQuaDai = uiMa < uiMaNhoNhat;
	const bool bSurrogate = uiMa >= SURROGATE_FIRST && uiMa <= SURROGATE_LAST;

	if (bQuaDai || bSurrogate || uiMa > MAX_CODE_POINT)
	{
		return false;
	}

	uiMaKyTu = uiMa;
	uiDoDai = uiSoByteTiep + 1;
	return true;
}

/**********************************************************
* @Description Xac dinh so byte tiep theo, bit du lieu va ma nho nhat tu byte dau cua ky tu UTF-8
*
* @return true neu byte dau hop le, false neu nguoc lai
**********************************************************/
bool ChuoiUtf8::layThongTinByteDau(const unsigned int uiByteDau, size_t& uiSoByteTiep, unsigned int& uiMaDau, unsigned int& uiMaNhoNhat)
{
	if (uiByteDau < ASCII_LIMIT)
	{
		uiSoByteTiep = 0;
		uiMaDau = uiByteDau;
		uiMaNhoNhat = 0;
		return true;
	}

	if ((uiByteDau & LEAD_2_MASK) == LEAD_2_TAG)
	{
		uiSoByteTiep = TRAILING_BYTES_2;
		uiMaDau = uiByteDau & LEAD_2_DATA;
		uiMaNhoNhat = MIN_CODE_2_BYTES;
		return true;
	}

	if ((uiByteDau & LEAD_3_MASK) == LEAD_3_TAG)
	{
		uiSoByteTiep = TRAILING_BYTES_3;
		uiMaDau = uiByteDau & LEAD_3_DATA;
		uiMaNhoNhat = MIN_CODE_3_BYTES;
		return true;
	}

	if ((uiByteDau & LEAD_4_MASK) == LEAD_4_TAG)
	{
		uiSoByteTiep = TRAILING_BYTES_4;
		uiMaDau = uiByteDau & LEAD_4_DATA;
		uiMaNhoNhat = MIN_CODE_4_BYTES;
		return true;
	}

	return false;
}

/**********************************************************
* @Description Tim vi tri byte cua ky tu thu uiSoKyTu trong chuoi
*
* @return Vi tri byte, bang kich thuoc chuoi neu uiSoKyTu vuot qua so ky tu
**********************************************************/
size_t ChuoiUtf8::timViTriByte(const std::string& strNguon, const size_t uiSoKyTu)
{
	size_t uiSoKyTuDaDem = 0;
	size_t uiViTri = 0;

	while (uiViTri < strNguon.size())
	{
		const unsigned int uiByte = static_cast<unsigned char>(strNguon[uiViTri]);

		if ((uiByte & CONTINUATION_MASK) != CONTINUATION_TAG)
		{
			if (uiSoKyTuDaDem == uiSoKyTu)
			{
				break;
			}

			++uiSoKyTuDaDem;
		}

		++uiViTri;
	}

	return uiViTri;
}
