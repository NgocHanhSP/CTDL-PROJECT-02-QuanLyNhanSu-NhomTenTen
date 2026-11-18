#include "../include/NguoiDungEmployee.h"
#include <string>
#include "../include/Constants.h"
#include "../include/GiaoDien.h"
#include "../include/KiemTraDuLieu.h"
#include "../include/HoSoNhanVien.h"
#include "../include/TaiKhoan.h"
#include "../include/XuLyFile.h"

/**********************************************************
* @Description Khoi tao NguoiDungEmployee voi giao dien va xu ly file duoc truyen vao
*
* @return Khong co gia tri tra ve
**********************************************************/
NguoiDungEmployee::NguoiDungEmployee(const GiaoDien& giaoDien, const XuLyFile& xuLyFile)
	: NguoiDung(giaoDien, xuLyFile)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Huy NguoiDungEmployee
*
* @return Khong co gia tri tra ve
* @attention Khong so huu tai nguyen nao (chi giu tham chieu den giao dien va xu ly file), nen khong can giai phong thu cong
* @attention Destructor lop co so NguoiDung la virtual nen duoc goi tu dong sau destructor nay
**********************************************************/
NguoiDungEmployee::~NguoiDungEmployee()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Hien thi menu Employee, bat buoc doi password neu dang dung password mac dinh
*
* @return Khong co gia tri tra ve
**********************************************************/
void NguoiDungEmployee::hienThiMenu(const std::string& strUsername) const
{
	if (!this->kiemTraDoiPasswordLanDau(strUsername))
	{
		return;
	}

	bool bTiepTuc = true;

	while (bTiepTuc)
	{
		const int iLuaChon = this->_giaoDien.hienThiMenuEmployee();

		bTiepTuc = this->xuLyLuaChon(iLuaChon, strUsername);
	}
}

/**********************************************************
* @Description Xu ly lua chon tren menu Employee
*
* @return true neu tiep tuc hien thi menu, false neu Employee chon thoat
**********************************************************/
bool NguoiDungEmployee::xuLyLuaChon(const int iLuaChon, const std::string& strUsername) const
{
	switch (static_cast<LuaChon>(iLuaChon))
	{
	case LuaChon::XEM_THONG_TIN:
		this->chayChucNang("THONG TIN TAI KHOAN", [this, &strUsername]()
		{
			this->xemThongTin(strUsername);
		});
		return true;

	case LuaChon::DOI_PASSWORD:
		this->chayChucNang("DOI PASSWORD", [this, &strUsername]()
		{
			this->doiPassword(strUsername);
		});
		return true;

	case LuaChon::THOAT:
		this->_giaoDien.hienThiManHinh("THOAT EMPLOYEE");
		this->_giaoDien.hienThiThongBao("Employee " + strUsername + " da thoat.");
		this->_giaoDien.choEnter();
		return false;

	default:
		this->_giaoDien.hienThiLoi("Lua chon khong hop le.");
		this->_giaoDien.choEnter();
		return true;
	}
}

/**********************************************************
* @Description Kiem tra va yeu cau doi password neu dang dung password mac dinh
*
* @return true neu co the tiep tuc vao menu, false neu loi hoac chua doi duoc password
**********************************************************/
bool NguoiDungEmployee::kiemTraDoiPasswordLanDau(const std::string& strUsername) const
{
	TaiKhoan taiKhoan;

	if (!this->_xuLyFile.docTaiKhoan(strUsername, taiKhoan))
	{
		this->_giaoDien.hienThiManHinh("LOI TAI KHOAN");
		this->_giaoDien.hienThiLoi("Khong doc duoc thong tin tai khoan.");
		this->_giaoDien.choEnter();
		return false;
	}

	if (taiKhoan.getPassword() != DEFAULT_PASSWORD)
	{
		return true;
	}

	this->_giaoDien.hienThiManHinh("DOI PASSWORD LAN DAU");
	this->_giaoDien.hienThiDong("\nBan dang dung password mac dinh.");
	this->_giaoDien.hienThiDong("Vui long doi password truoc khi tiep tuc.\n");
	this->_giaoDien.hienThiDong(this->layQuyTacPassword() + "\n");

	const bool bDoiThanhCong = this->doiPasswordLanDau(strUsername);

	if (!bDoiThanhCong)
	{
		this->_giaoDien.hienThiLoi("Ban chua doi duoc password. Vui long dang nhap lai.");
	}

	this->_giaoDien.choEnter();
	return bDoiThanhCong;
}

/**********************************************************
* @Description Cho Employee doi password lan dau, toi da MAX_PASSWORD_ATTEMPTS lan
*
* @return true neu doi thanh cong, false neu that bai
**********************************************************/
bool NguoiDungEmployee::doiPasswordLanDau(const std::string& strUsername) const
{
	for (int iLan = 1; iLan <= MAX_PASSWORD_ATTEMPTS; ++iLan)
	{
		std::string strPasswordMoi;

		this->_giaoDien.hienThiDong("Lan thu " + std::to_string(iLan) + "/" + std::to_string(MAX_PASSWORD_ATTEMPTS));

		if (!this->nhapPasswordMoi(DEFAULT_PASSWORD, strPasswordMoi))
		{
			continue;
		}

		if (!this->_xuLyFile.capNhatMatKhau(strUsername, strPasswordMoi))
		{
			this->_giaoDien.hienThiLoi("Khong the luu password moi vao file.");
			return false;
		}

		this->_giaoDien.hienThiThongBao("Doi password lan dau thanh cong.");
		return true;
	}

	return false;
}

/**********************************************************
* @Description Hien thi ho so ca nhan cua Employee
*
* @return Khong co gia tri tra ve
**********************************************************/
void NguoiDungEmployee::xemThongTin(const std::string& strUsername) const
{
	HoSoNhanVien hoSoNhanVien;

	if (!this->_xuLyFile.docHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		this->_giaoDien.hienThiLoi("Khong doc duoc ho so ca nhan.");
		return;
	}

	this->_giaoDien.hienThiDong("");
	this->hienThiHoSo(strUsername, hoSoNhanVien);
}

/**********************************************************
* @Description Doi password sau khi xac nhan password hien tai
*
* @return Khong co gia tri tra ve
**********************************************************/
void NguoiDungEmployee::doiPassword(const std::string& strUsername) const
{
	TaiKhoan taiKhoan;

	if (!this->_xuLyFile.docTaiKhoan(strUsername, taiKhoan))
	{
		this->_giaoDien.hienThiLoi("Khong doc duoc thong tin tai khoan.");
		return;
	}

	this->_giaoDien.hienThiDong("\n" + this->layQuyTacPassword() + "\n");

	const std::string strPasswordCu = this->_giaoDien.nhapMatKhau("Password hien tai: ");

	if (strPasswordCu != taiKhoan.getPassword())
	{
		this->_giaoDien.hienThiLoi("Password hien tai khong dung.");
		return;
	}

	std::string strPasswordMoi;

	if (!this->nhapPasswordMoi(strPasswordCu, strPasswordMoi))
	{
		return;
	}

	if (!this->_xuLyFile.capNhatMatKhau(strUsername, strPasswordMoi))
	{
		this->_giaoDien.hienThiLoi("Khong the ghi password moi vao file.");
		return;
	}

	this->_giaoDien.hienThiThongBao("Doi password thanh cong.");
}

/**********************************************************
* @Description Nhap password moi va kiem tra do manh, khac mac dinh, khac cu, nhap lai khop
*
* @return true neu password moi hop le, false neu nguoc lai
**********************************************************/
bool NguoiDungEmployee::nhapPasswordMoi(const std::string& strPasswordCu, std::string& strPasswordMoi) const
{
	strPasswordMoi = this->_giaoDien.nhapMatKhau("Password moi: ");

	if (!KiemTraDuLieu::laMatKhauManh(strPasswordMoi))
	{
		this->_giaoDien.hienThiLoi(this->layQuyTacPassword());
		return false;
	}

	if (strPasswordMoi == DEFAULT_PASSWORD)
	{
		this->_giaoDien.hienThiLoi("Password moi khong duoc trung password mac dinh.");
		return false;
	}

	if (strPasswordMoi == strPasswordCu)
	{
		this->_giaoDien.hienThiLoi("Password moi phai khac password hien tai.");
		return false;
	}

	if (strPasswordMoi != this->_giaoDien.nhapMatKhau("Nhap lai password moi: "))
	{
		this->_giaoDien.hienThiLoi("Hai lan nhap password moi khong khop.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Tao chuoi mo ta quy tac password
*
* @return Chuoi quy tac password
**********************************************************/
std::string NguoiDungEmployee::layQuyTacPassword() const
{
	return "Password dai " + std::to_string(MIN_PASSWORD_LENGTH) + " den " +
		   std::to_string(MAX_PASSWORD_LENGTH) +
		   " ky tu, gom chu hoa, chu thuong, chu so, ky tu dac biet va khong co khoang trang.";
}
