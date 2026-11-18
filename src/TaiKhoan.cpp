#include "../include/TaiKhoan.h"
#include <istream>
#include <ostream>
#include <stdexcept>
#include <cctype>
#include "../include/KiemTraDuLieu.h"
#include "../include/Constants.h"

namespace
{
	const char CARRIAGE_RETURN = '\r';
}

/**********************************************************
* @Description Bo ky tu '\r' o cuoi dong (file luu theo kieu xuong dong Windows)
*
* @return Khong co gia tri tra ve
**********************************************************/
static void boCarriageReturn(std::string& strDong)
{
	if (!strDong.empty() && strDong[strDong.size() - 1] == CARRIAGE_RETURN)
	{
		strDong.erase(strDong.size() - 1);
	}
}

/**********************************************************
* @Description Khoi tao TaiKhoan rong (username va password rong)
*
* @return Khong co gia tri tra ve
* @attention Khong goi setter de tranh nem ngoai le do du lieu rong khong hop le
**********************************************************/
TaiKhoan::TaiKhoan()
	: _strUsername(),
	  _strPassword()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Khoi tao TaiKhoan tu username va password
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu username hoac password khong hop le
**********************************************************/
TaiKhoan::TaiKhoan(const std::string& strUsername, const std::string& strPassword)
{
	this->setUsername(strUsername);
	this->setPassword(strPassword);
}

/**********************************************************
* @Description Khoi tao TaiKhoan bang ban sao cua taiKhoanNguon
*
* @return Khong co gia tri tra ve
* @attention Sao chep truc tiep cac thuoc tinh vi du lieu nguon da duoc kiem tra hop le
**********************************************************/
TaiKhoan::TaiKhoan(const TaiKhoan& taiKhoanNguon)
	: _strUsername(taiKhoanNguon._strUsername),
	  _strPassword(taiKhoanNguon._strPassword)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Huy TaiKhoan
*
* @return Khong co gia tri tra ve
* @attention Cac thuoc tinh std::string tu giai phong, khong can giai phong thu cong
**********************************************************/
TaiKhoan::~TaiKhoan()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Lay username
*
* @return Username cua tai khoan
**********************************************************/
std::string TaiKhoan::getUsername() const
{
	return this->_strUsername;
}

/**********************************************************
* @Description Lay password
*
* @return Password cua tai khoan
**********************************************************/
std::string TaiKhoan::getPassword() const
{
	return this->_strPassword;
}

/**********************************************************
* @Description Gan username sau khi kiem tra hop le
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu username khong hop le hoac la ten danh rieng
**********************************************************/
void TaiKhoan::setUsername(const std::string& strUsername)
{
	if (!KiemTraDuLieu::laUsernameHopLe(strUsername) ||
		KiemTraDuLieu::laUsernameDanhRieng(strUsername))
	{
		throw std::invalid_argument("TaiKhoan::setUsername: username khong hop le");
	}
	this->_strUsername = strUsername;
}

/**********************************************************
* @Description Gan password sau khi kiem tra do dai va ky tu
*
* @return Khong co gia tri tra ve
* @attention Nem std::invalid_argument neu password khong hop le
* @attention Chap nhan password tu MIN_LEGACY_PASSWORD_LENGTH ky tu de tuong thich du lieu cu
**********************************************************/
void TaiKhoan::setPassword(const std::string& strPassword)
{
	// Chap nhan mat khau cu trong du lieu mau (vi du 123456) va mat khau mac dinh.
	// Quy tac mat khau manh duoc kiem tra bo sung tai luong doi mat khau.
	if (strPassword.size() < MIN_LEGACY_PASSWORD_LENGTH || strPassword.size() > MAX_PASSWORD_LENGTH)
	{
		throw std::invalid_argument("TaiKhoan::setPassword: do dai mat khau khong hop le");
	}
	for (size_t uiViTri = 0; uiViTri < strPassword.size(); ++uiViTri)
	{
		if (!std::isgraph(static_cast<unsigned char>(strPassword[uiViTri])))
		{
			throw std::invalid_argument("TaiKhoan::setPassword: ky tu mat khau khong hop le");
		}
	}
	this->_strPassword = strPassword;
}

/**********************************************************
* @Description Doc 2 dong (username, password) tu luong vao
*
* @return Luong luongVao
* @attention Dat failbit neu du lieu doc duoc khong hop le
**********************************************************/
std::istream& operator>>(std::istream& luongVao, TaiKhoan& taiKhoan)
{
	std::string strUsername;
	std::string strPassword;

	if (std::getline(luongVao, strUsername) && std::getline(luongVao, strPassword))
	{
		boCarriageReturn(strUsername);
		boCarriageReturn(strPassword);

		try
		{
			TaiKhoan taiKhoanHopLe(strUsername, strPassword);
			taiKhoan = taiKhoanHopLe;
		}
		catch (const std::invalid_argument&)
		{
			luongVao.setstate(std::ios::failbit);
		}
	}

	return luongVao;
}

/**********************************************************
* @Description Ghi 2 dong (username, password) ra luong ra
*
* @return Luong luongRa
**********************************************************/
std::ostream& operator<<(std::ostream& luongRa, const TaiKhoan& taiKhoan)
{
	return luongRa << taiKhoan._strUsername << '\n' << taiKhoan._strPassword << '\n';
}
