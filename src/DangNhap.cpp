#include "../include/DangNhap.h"
#include <string>
#include "../include/Admin.h"
#include "../include/Constants.h"
#include "../include/NguoiDungEmployee.h"
#include "../include/NguoiDung.h"

/**********************************************************
* @Description Chay vong lap menu dang nhap cho den khi nguoi dung thoat
*
* @return Khong co gia tri tra ve
* @attention Tao thu muc du lieu truoc khi hien thi menu
**********************************************************/
void DangNhap::chayDangNhap()
{
	if (!this->_xuLyFile.taoThuMucDuLieu())
	{
		this->_giaoDien.hienThiLoi("Khong tao duoc thu muc du lieu.");
	}

	bool bDangChay = true;

	while (bDangChay)
	{
		const int iLuaChon = this->_giaoDien.hienThiMenuDangNhap();

		bDangChay = this->xuLyLuaChon(iLuaChon);
	}
}

/**********************************************************
* @Description Xu ly lua chon tren menu dang nhap
*
* @return true neu tiep tuc chay chuong trinh, false neu thoat
* @attention Dang nhap Employee sai MAX_LOGIN_ATTEMPTS lan se thoat chuong trinh
**********************************************************/
bool DangNhap::xuLyLuaChon(const int iLuaChon) const
{
	switch (static_cast<LuaChon>(iLuaChon))
	{
	case LuaChon::ADMIN:
		this->xuLyDangNhapAdmin();
		return true;

	case LuaChon::EMPLOYEE:
		return this->xuLyDangNhapEmployee();

	case LuaChon::QUEN_PASSWORD:
		this->quenPassword();
		return true;

	case LuaChon::THOAT:
		this->hienThiKetThuc("Cam on ban da su dung chuong trinh.");
		return false;

	default:
		this->baoLoi("Lua chon khong hop le.");
		return true;
	}
}

/**********************************************************
* @Description Dang nhap Admin, thanh cong thi mo menu Admin
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::xuLyDangNhapAdmin() const
{
	std::string strUsername;

	if (this->dangNhapAdmin(strUsername))
	{
		this->chayAdmin(strUsername);
	}
}

/**********************************************************
* @Description Dang nhap Employee, thanh cong thi mo menu Employee
*
* @return true neu tiep tuc chay chuong trinh, false neu dang nhap sai qua so lan cho phep
**********************************************************/
bool DangNhap::xuLyDangNhapEmployee() const
{
	std::string strUsername;

	if (!this->dangNhapEmployee(strUsername))
	{
		this->hienThiKetThuc("Ban da dang nhap sai " + std::to_string(MAX_LOGIN_ATTEMPTS) + " lan. Chuong trinh se thoat.");
		return false;
	}

	this->chayEmployee(strUsername);
	return true;
}

/**********************************************************
* @Description Tao doi tuong Admin va mo menu Admin
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::chayAdmin(const std::string& strUsername) const
{
	const Admin admin(this->_giaoDien, this->_xuLyFile);

	this->chayNguoiDung(admin, strUsername);
}

/**********************************************************
* @Description Tao doi tuong Employee va mo menu Employee
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::chayEmployee(const std::string& strUsername) const
{
	const NguoiDungEmployee nguoiDungEmployee(this->_giaoDien, this->_xuLyFile);

	this->chayNguoiDung(nguoiDungEmployee, strUsername);
}

/**********************************************************
* @Description Mo menu cua mot nguoi dung (Admin hoac Employee) thong qua NguoiDung
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::chayNguoiDung(const NguoiDung& nguoiDung, const std::string& strUsername) const
{
	nguoiDung.hienThiMenu(strUsername);
}

/**********************************************************
* @Description Nhap thong tin va kiem tra dang nhap Admin
*
* @return true neu username/password dung, false neu sai
* @attention strUsername tra ve username da nhap
**********************************************************/
bool DangNhap::dangNhapAdmin(std::string& strUsername) const
{
	std::string strPassword;

	this->_giaoDien.hienThiManHinh("DANG NHAP ADMIN");
	this->nhapThongTinDangNhap("Password: ", strUsername, strPassword);

	if (!this->_xuLyFile.kiemTraDangNhap(strUsername, strPassword, VaiTro::ADMIN))
	{
		this->baoLoi("Username hoac Password Admin khong chinh xac.");
		return false;
	}

	this->_giaoDien.hienThiThongBao("Dang nhap Admin thanh cong.");
	this->_giaoDien.choEnter("Nhan Enter de tiep tuc...");
	return true;
}

/**********************************************************
* @Description Nhap thong tin va kiem tra dang nhap Employee, toi da MAX_LOGIN_ATTEMPTS lan
*
* @return true neu dang nhap thanh cong, false neu sai het so lan cho phep
* @attention strUsername tra ve username da nhap lan cuoi
**********************************************************/
bool DangNhap::dangNhapEmployee(std::string& strUsername) const
{
	for (int iLan = 1; iLan <= MAX_LOGIN_ATTEMPTS; ++iLan)
	{
		std::string strPassword;

		this->_giaoDien.hienThiManHinh("DANG NHAP EMPLOYEES");
		this->nhapThongTinDangNhap("Password: ", strUsername, strPassword);

		if (this->_xuLyFile.kiemTraDangNhap(strUsername, strPassword, VaiTro::EMPLOYEE))
		{
			this->_giaoDien.hienThiThongBao("Dang nhap Employee thanh cong.");
			this->_giaoDien.choEnter("Nhan Enter de tiep tuc...");
			return true;
		}

		this->_giaoDien.hienThiLoi("Sai Username hoac Password. Lan " + std::to_string(iLan) + "/" + std::to_string(MAX_LOGIN_ATTEMPTS));

		if (iLan < MAX_LOGIN_ATTEMPTS)
		{
			this->_giaoDien.choEnter();
		}
	}

	return false;
}

/**********************************************************
* @Description Nhap username (hien thi) va password (che bang dau *)
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::nhapThongTinDangNhap(const std::string& strNhanMatKhau, std::string& strUsername, std::string& strPassword) const
{
	this->_giaoDien.hienThiDong("");
	strUsername = this->_giaoDien.nhapChuoi("Username: ", true);
	strPassword = this->_giaoDien.nhapMatKhau(strNhanMatKhau, true);
}

/**********************************************************
* @Description Dat lai password Employee ve mac dinh sau khi Admin xac thuc
*
* @return Khong co gia tri tra ve
* @attention Khong thay doi password neu xac thuc Admin that bai
**********************************************************/
void DangNhap::quenPassword() const
{
	std::string strUsername;

	if (!this->nhapUsernameKhoiPhuc(strUsername))
	{
		return;
	}

	if (!this->xacThucAdmin(strUsername))
	{
		this->baoLoi("Xac thuc Admin khong thanh cong. Password chua duoc thay doi.");
		return;
	}

	if (!this->_xuLyFile.capNhatMatKhau(strUsername, DEFAULT_PASSWORD))
	{
		this->baoLoi("Admin da xac thuc nhung khong the cap nhat password.");
		return;
	}

	this->hienThiKetQuaKhoiPhuc(strUsername);
}

/**********************************************************
* @Description Nhap username can khoi phuc va kiem tra ton tai
*
* @return true neu username hop le va ton tai, false neu nguoc lai
**********************************************************/
bool DangNhap::nhapUsernameKhoiPhuc(std::string& strUsername) const
{
	this->_giaoDien.hienThiManHinh("YEU CAU KHOI PHUC PASSWORD");
	this->_giaoDien.hienThiDong("\n\t\tNhap Username cua tai khoan can khoi phuc.\n");

	strUsername = this->_giaoDien.nhapChuoi("Username: ", true);

	if (strUsername.empty())
	{
		this->baoLoi("Username khong duoc de trong.");
		return false;
	}

	if (!this->_xuLyFile.kiemTraUsernameTonTai(strUsername))
	{
		this->baoLoi("Khong tim thay tai khoan Employee.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Yeu cau Admin nhap username/password de xac thuc viec khoi phuc
*
* @return true neu Admin xac thuc thanh cong, false neu nguoc lai
**********************************************************/
bool DangNhap::xacThucAdmin(const std::string& strUsername) const
{
	this->_giaoDien.hienThiManHinh("DANG CHO ADMIN XAC THUC");
	this->_giaoDien.hienThiDong("\n\t\tTai khoan can khoi phuc: " + strUsername);
	this->_giaoDien.hienThiThongBao("Dang cho Admin xac thuc yeu cau.");
	this->_giaoDien.hienThiDong("\n\t\tVui long chuyen ban phim cho Admin.");
	this->_giaoDien.choEnter("Nhan ENTER de tiep tuc...");

	this->_giaoDien.hienThiManHinh("XAC THUC ADMIN");
	this->_giaoDien.hienThiDong("\n\t\tYeu cau dat lai password cho Employee: " + strUsername + "\n");

	const std::string strUsernameAdmin = this->_giaoDien.nhapChuoi("Username Admin: ", true);
	const std::string strPasswordAdmin = this->_giaoDien.nhapMatKhau("Password Admin: ", true);

	return this->_xuLyFile.kiemTraDangNhap(strUsernameAdmin, strPasswordAdmin, VaiTro::ADMIN);
}

/**********************************************************
* @Description Hien thi ket qua khoi phuc password thanh cong
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::hienThiKetQuaKhoiPhuc(const std::string& strUsername) const
{
	this->_giaoDien.hienThiManHinh("YEU CAU KHOI PHUC PASSWORD");
	this->_giaoDien.hienThiDong("\n\t\tTai khoan: " + strUsername);
	this->_giaoDien.hienThiThongBao("Xac thuc thong tin thanh cong.");
	this->_giaoDien.hienThiThongBao("Password moi cua ban la " + std::string(DEFAULT_PASSWORD) + ".");
	this->_giaoDien.hienThiDong("\n\t\tVui long quay ve trang chu de dang nhap va doi password moi.");
	this->_giaoDien.choEnter();
}

/**********************************************************
* @Description Hien thi man hinh ket thuc voi thong bao va cho nhan ENTER
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::hienThiKetThuc(const std::string& strThongBao) const
{
	this->_giaoDien.hienThiManHinh("KET THUC CHUONG TRINH");
	this->_giaoDien.hienThiThongBao(strThongBao);
	this->_giaoDien.choEnter("Nhan Enter de thoat chuong trinh...");
}

/**********************************************************
* @Description Hien thi thong bao loi va cho nhan ENTER
*
* @return Khong co gia tri tra ve
**********************************************************/
void DangNhap::baoLoi(const std::string& strThongBao) const
{
	this->_giaoDien.hienThiLoi(strThongBao);
	this->_giaoDien.choEnter();
}
