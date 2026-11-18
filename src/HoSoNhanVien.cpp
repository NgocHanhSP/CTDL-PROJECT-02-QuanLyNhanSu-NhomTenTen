#include "../include/HoSoNhanVien.h"
#include <istream>
#include <ostream>
#include <stdexcept>
#include "../include/KiemTraDuLieu.h"

/**********************************************************
* @Description Khoi tao HoSoNhanVien rong (tat ca thuoc tinh rong)
*
* @return Khong co gia tri tra ve
* @attention Khong goi setter de tranh nem ngoai le do du lieu rong khong hop le
**********************************************************/
HoSoNhanVien::HoSoNhanVien()
	: _strHoTen(),
	  _strDiaChi(),
	  _strSoDienThoai(),
	  _strEmail()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Khoi tao HoSoNhanVien tu ho ten, dia chi, so dien thoai, email
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu bat ky du lieu nao khong hop le
**********************************************************/
HoSoNhanVien::HoSoNhanVien(const std::string& strHoTen, const std::string& strDiaChi, const std::string& strSoDienThoai, const std::string& strEmail)
{
	this->setHoTen(strHoTen);
	this->setDiaChi(strDiaChi);
	this->setSoDienThoai(strSoDienThoai);
	this->setEmail(strEmail);
}

/**********************************************************
* @Description Khoi tao HoSoNhanVien bang ban sao cua hoSoNguon
*
* @return Khong co gia tri tra ve
* @attention Sao chep truc tiep cac thuoc tinh vi du lieu nguon da duoc kiem tra hop le
**********************************************************/
HoSoNhanVien::HoSoNhanVien(const HoSoNhanVien& hoSoNguon)
	: _strHoTen(hoSoNguon._strHoTen),
	  _strDiaChi(hoSoNguon._strDiaChi),
	  _strSoDienThoai(hoSoNguon._strSoDienThoai),
	  _strEmail(hoSoNguon._strEmail)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Huy HoSoNhanVien
*
* @return Khong co gia tri tra ve
* @attention Cac thuoc tinh std::string tu giai phong, khong can giai phong thu cong
**********************************************************/
HoSoNhanVien::~HoSoNhanVien()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Lay ho ten
*
* @return Ho ten nhan vien
**********************************************************/
std::string HoSoNhanVien::getHoTen() const
{
	return this->_strHoTen;
}

/**********************************************************
* @Description Lay dia chi
*
* @return Dia chi nhan vien
**********************************************************/
std::string HoSoNhanVien::getDiaChi() const
{
	return this->_strDiaChi;
}

/**********************************************************
* @Description Lay so dien thoai
*
* @return So dien thoai nhan vien
**********************************************************/
std::string HoSoNhanVien::getSoDienThoai() const
{
	return this->_strSoDienThoai;
}

/**********************************************************
* @Description Lay email
*
* @return Email nhan vien
**********************************************************/
std::string HoSoNhanVien::getEmail() const
{
	return this->_strEmail;
}

/**********************************************************
* @Description Gan ho ten sau khi kiem tra hop le
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu ho ten khong hop le
**********************************************************/
void HoSoNhanVien::setHoTen(const std::string& strHoTen)
{
	if (!KiemTraDuLieu::laHoTenHopLe(strHoTen))
	{
		throw std::invalid_argument("HoSoNhanVien::setHoTen: du lieu khong hop le");
	}
	this->_strHoTen = strHoTen;
}

/**********************************************************
* @Description Gan dia chi sau khi kiem tra hop le
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu dia chi khong hop le
**********************************************************/
void HoSoNhanVien::setDiaChi(const std::string& strDiaChi)
{
	if (!KiemTraDuLieu::laDiaChiHopLe(strDiaChi))
	{
		throw std::invalid_argument("HoSoNhanVien::setDiaChi: du lieu khong hop le");
	}
	this->_strDiaChi = strDiaChi;
}

/**********************************************************
* @Description Gan so dien thoai sau khi kiem tra hop le
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu so dien thoai khong hop le
**********************************************************/
void HoSoNhanVien::setSoDienThoai(const std::string& strSoDienThoai)
{
	if (!KiemTraDuLieu::laSoDienThoaiHopLe(strSoDienThoai))
	{
		throw std::invalid_argument("HoSoNhanVien::setSoDienThoai: du lieu khong hop le");
	}
	this->_strSoDienThoai = strSoDienThoai;
}

/**********************************************************
* @Description Gan email sau khi kiem tra hop le
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu email khong hop le
**********************************************************/
void HoSoNhanVien::setEmail(const std::string& strEmail)
{
	if (!KiemTraDuLieu::laEmailHopLe(strEmail))
	{
		throw std::invalid_argument("HoSoNhanVien::setEmail: du lieu khong hop le");
	}
	this->_strEmail = strEmail;
}

/**********************************************************
* @Description Doc 4 dong (ho ten, dia chi, so dien thoai, email) tu luong vao
*
* @return Luong luongVao
* @attention Dat failbit neu du lieu doc duoc khong hop le
**********************************************************/
std::istream& operator>>(std::istream& luongVao, HoSoNhanVien& hoSoNhanVien)
{
	std::string strHoTen;
	std::string strDiaChi;
	std::string strSoDienThoai;
	std::string strEmail;

	if (std::getline(luongVao, strHoTen) && std::getline(luongVao, strDiaChi) &&
		std::getline(luongVao, strSoDienThoai) && std::getline(luongVao, strEmail))
	{
		if (KiemTraDuLieu::laHoTenHopLe(strHoTen) &&
			KiemTraDuLieu::laDiaChiHopLe(strDiaChi) &&
			KiemTraDuLieu::laSoDienThoaiHopLe(strSoDienThoai) &&
			KiemTraDuLieu::laEmailHopLe(strEmail))
		{
			hoSoNhanVien._strHoTen = strHoTen;
			hoSoNhanVien._strDiaChi = strDiaChi;
			hoSoNhanVien._strSoDienThoai = strSoDienThoai;
			hoSoNhanVien._strEmail = strEmail;
		}
		else
		{
			luongVao.setstate(std::ios::failbit);
		}
	}

	return luongVao;
}

/**********************************************************
* @Description Ghi 4 dong (ho ten, dia chi, so dien thoai, email) ra luong ra
*
* @return Luong luongRa
**********************************************************/
std::ostream& operator<<(std::ostream& luongRa, const HoSoNhanVien& hoSoNhanVien)
{
	return luongRa << hoSoNhanVien._strHoTen << '\n'
				   << hoSoNhanVien._strDiaChi << '\n'
				   << hoSoNhanVien._strSoDienThoai << '\n'
				   << hoSoNhanVien._strEmail << '\n';
}
