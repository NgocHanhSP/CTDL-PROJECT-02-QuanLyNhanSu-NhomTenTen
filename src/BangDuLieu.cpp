#include "../include/BangDuLieu.h"
#include <iostream>
#include "../include/ChuoiUtf8.h"

namespace
{
	const char BOX_HORIZONTAL[] = "\xE2\x94\x80";
	const char BOX_VERTICAL[] = "\xE2\x94\x82";
	const char BOX_TOP_LEFT[] = "\xE2\x94\x8C";
	const char BOX_TOP_RIGHT[] = "\xE2\x94\x90";
	const char BOX_BOTTOM_LEFT[] = "\xE2\x94\x94";
	const char BOX_BOTTOM_RIGHT[] = "\xE2\x94\x98";
	const char BOX_TOP_JOIN[] = "\xE2\x94\xAC";
	const char BOX_BOTTOM_JOIN[] = "\xE2\x94\xB4";
	const char BOX_MIDDLE_LEFT[] = "\xE2\x94\x9C";
	const char BOX_MIDDLE_RIGHT[] = "\xE2\x94\xA4";
	const char BOX_CROSS[] = "\xE2\x94\xBC";

	const size_t CELL_PADDING_TOTAL = 2;
}

/**********************************************************
* @Description Khoi tao bang voi tieu de va do rong tung cot
*
* @return Khong co gia tri tra ve
* @attention Cot co do rong 0 duoc dat lai thanh 1 de tranh chia dong lap vo han
**********************************************************/
BangDuLieu::BangDuLieu(const std::vector<std::string>& vecTieuDe,
					   const std::vector<size_t>& vecDoRongCot)
	: _vecTieuDe(vecTieuDe),
	  _vecDoRongCot(vecDoRongCot),
	  _vecDong()
{
	// Cot 0 ky tu co the khien chiaNhieuDong lap vo han; dat toi thieu 1.
	for (size_t uiCot = 0; uiCot < this->_vecDoRongCot.size(); ++uiCot)
	{
		if (this->_vecDoRongCot[uiCot] == 0)
		{
			this->_vecDoRongCot[uiCot] = 1;
		}
	}
}

/**********************************************************
* @Description Them mot dong du lieu vao bang
*
* @return Khong co gia tri tra ve
**********************************************************/
void BangDuLieu::themDong(const std::vector<std::string>& vecDuLieu)
{
	this->_vecDong.push_back(vecDuLieu);
}

/**********************************************************
* @Description In toan bo bang (khung, tieu de, cac dong) ra man hinh
*
* @return Khong co gia tri tra ve
**********************************************************/
void BangDuLieu::hienThi() const
{
	this->inDuongKe(LoaiDuong::TREN);
	this->inDong(this->_vecTieuDe);

	for (size_t uiDong = 0; uiDong < this->_vecDong.size(); ++uiDong)
	{
		this->inDuongKe(LoaiDuong::GIUA);
		this->inDong(this->_vecDong[uiDong]);
	}

	this->inDuongKe(LoaiDuong::DUOI);
}

/**********************************************************
* @Description In mot duong ke ngang (tren, giua hoac duoi) cua bang
*
* @return Khong co gia tri tra ve
**********************************************************/
void BangDuLieu::inDuongKe(const LoaiDuong eLoaiDuong) const
{
	std::string strTrai;
	std::string strGiua;
	std::string strPhai;

	switch (eLoaiDuong)
	{
	case LoaiDuong::TREN:
		strTrai = BOX_TOP_LEFT;
		strGiua = BOX_TOP_JOIN;
		strPhai = BOX_TOP_RIGHT;
		break;

	case LoaiDuong::GIUA:
		strTrai = BOX_MIDDLE_LEFT;
		strGiua = BOX_CROSS;
		strPhai = BOX_MIDDLE_RIGHT;
		break;

	case LoaiDuong::DUOI:
		strTrai = BOX_BOTTOM_LEFT;
		strGiua = BOX_BOTTOM_JOIN;
		strPhai = BOX_BOTTOM_RIGHT;
		break;

	default:
		break;
	}

	std::cout << strTrai;

	for (size_t uiCot = 0; uiCot < this->_vecDoRongCot.size(); ++uiCot)
	{
		const size_t uiDoDai = this->_vecDoRongCot[uiCot] + CELL_PADDING_TOTAL;

		for (size_t uiKyTu = 0; uiKyTu < uiDoDai; ++uiKyTu)
		{
			std::cout << BOX_HORIZONTAL;
		}

		if (uiCot + 1 < this->_vecDoRongCot.size())
		{
			std::cout << strGiua;
		}
	}

	std::cout << strPhai << '\n';
}

/**********************************************************
* @Description In mot dong cua bang, tu dong chia nhieu dong neu noi dung dai hon do rong cot
*
* @return Khong co gia tri tra ve
**********************************************************/
void BangDuLieu::inDong(const std::vector<std::string>& vecDuLieu) const
{
	std::vector<std::vector<std::string> > vecCacO;
	size_t uiSoDongToiDa = 1;

	for (size_t uiCot = 0; uiCot < this->_vecDoRongCot.size(); ++uiCot)
	{
		const std::string strNoiDung = (uiCot < vecDuLieu.size()) ? vecDuLieu[uiCot] : "";

		vecCacO.push_back(this->chiaNhieuDong(strNoiDung, this->_vecDoRongCot[uiCot]));

		if (vecCacO[uiCot].size() > uiSoDongToiDa)
		{
			uiSoDongToiDa = vecCacO[uiCot].size();
		}
	}

	for (size_t uiDong = 0; uiDong < uiSoDongToiDa; ++uiDong)
	{
		std::cout << BOX_VERTICAL;

		for (size_t uiCot = 0; uiCot < vecCacO.size(); ++uiCot)
		{
			const std::string strDoan = (uiDong < vecCacO[uiCot].size()) ? vecCacO[uiCot][uiDong] : "";
			const size_t uiKhoangTrang = this->_vecDoRongCot[uiCot] - ChuoiUtf8::demKyTu(strDoan);

			std::cout << ' ' << strDoan << std::string(uiKhoangTrang, ' ') << ' ' << BOX_VERTICAL;
		}

		std::cout << '\n';
	}
}

/**********************************************************
* @Description Chia chuoi thanh cac doan khong vuot qua do rong cot
*
* @return Vector cac doan, uu tien ngat tai khoang trang
**********************************************************/
std::vector<std::string> BangDuLieu::chiaNhieuDong(const std::string& strNoiDung, const size_t uiDoRong) const
{
	std::vector<std::string> vecDoan;
	std::string strConLai = strNoiDung;

	while (ChuoiUtf8::demKyTu(strConLai) > uiDoRong)
	{
		const size_t uiViTriNgat = this->timViTriNgat(strConLai, uiDoRong);

		vecDoan.push_back(ChuoiUtf8::catKyTu(strConLai, uiViTriNgat));
		strConLai = ChuoiUtf8::boKyTuDau(strConLai, uiViTriNgat);

		// Bo khoang trang dau dong tiep theo.
		strConLai.erase(0, strConLai.find_first_not_of(' '));
	}

	vecDoan.push_back(strConLai);
	return vecDoan;
}

/**********************************************************
* @Description Tim vi tri (so ky tu) de ngat chuoi theo do rong
*
* @return So ky tu cua doan dau tien
* @attention Neu khong co khoang trang thi ngat dung tai uiDoRong
**********************************************************/
size_t BangDuLieu::timViTriNgat(const std::string& strNoiDung, const size_t uiDoRong) const
{
	// Lay them 1 ky tu de biet ky tu ke tiep co phai khoang trang hay khong,
	// sau do ngat tai khoang trang cuoi cung de khong cat doi tu.
	const std::string strDau = ChuoiUtf8::catKyTu(strNoiDung, uiDoRong + 1);
	const size_t uiViTriByte = strDau.rfind(' ');

	// Khong co khoang trang de ngat (hoac o ngay dau): cat cung tai do rong cot.
	if (uiViTriByte == std::string::npos || uiViTriByte == 0)
	{
		return uiDoRong;
	}

	return ChuoiUtf8::demKyTu(strDau.substr(0, uiViTriByte));
}
