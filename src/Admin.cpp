#include "../include/Admin.h"

#include <string>
#include <vector>

#include "../include/BangDuLieu.h"
#include "../include/ChuoiUtf8.h"
#include "../include/Constants.h"
#include "../include/DanhSachLienKet.h"
#include "../include/GiaoDien.h"
#include "../include/KiemTraDuLieu.h"
#include "../include/HoSoNhanVien.h"
#include "../include/TaiKhoan.h"
#include "../include/XuLyFile.h"

namespace
{
	const size_t COLUMN_WIDTH_INDEX = 4;
	const size_t COLUMN_WIDTH_USERNAME = 14;
	const size_t COLUMN_WIDTH_FULLNAME = 20;
	const size_t COLUMN_WIDTH_ADDRESS = 25;
	const size_t COLUMN_WIDTH_PHONE = 10;
	const size_t COLUMN_WIDTH_EMAIL = 26;

	const char MISSING_PROFILE_TEXT[] = "(chua co ho so)";
}

/**********************************************************
* @Description Khoi tao Admin voi giao dien va xu ly file duoc truyen vao
*
* @return Khong co gia tri tra ve
**********************************************************/
Admin::Admin(const GiaoDien& giaoDien, const XuLyFile& xuLyFile)
	: NguoiDung(giaoDien, xuLyFile)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Huy Admin
*
* @return Khong co gia tri tra ve
* @attention Khong so huu tai nguyen nao (chi giu tham chieu den giao dien va xu ly file), nen khong can giai phong thu cong
* @attention Destructor lop co so NguoiDung la virtual nen duoc goi tu dong sau destructor nay
**********************************************************/
Admin::~Admin()
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Hien thi menu Admin va xu ly lua chon cho den khi Admin thoat
*
* @return Khong co gia tri tra ve
**********************************************************/
void Admin::hienThiMenu(const std::string& strUsername) const
{
	bool bTiepTuc = true;

	while (bTiepTuc)
	{
		const int iLuaChon = this->_giaoDien.hienThiMenuAdmin();

		bTiepTuc = this->xuLyLuaChon(iLuaChon, strUsername);
	}
}

/**********************************************************
* @Description Xu ly lua chon tren menu Admin
*
* @return true neu tiep tuc hien thi menu, false neu Admin chon thoat
**********************************************************/
bool Admin::xuLyLuaChon(const int iLuaChon, const std::string& strUsername) const
{
	switch (static_cast<LuaChon>(iLuaChon))
	{
	case LuaChon::THEM:
		this->chayChucNang("THEM EMPLOYEE", [this]()
		{
			this->themEmployee();
		});
		return true;

	case LuaChon::XOA:
		this->chayChucNang("XOA EMPLOYEE", [this]()
		{
			this->xoaEmployee();
		});
		return true;

	case LuaChon::TIM:
		this->chayChucNang("TIM EMPLOYEE", [this]()
		{
			this->timEmployee();
		});
		return true;

	case LuaChon::CAP_NHAT:
		this->chayChucNang("CAP NHAT EMPLOYEE", [this]()
		{
			this->capNhatEmployee();
		});
		return true;

	case LuaChon::HIEN_THI:
		this->chayChucNang("DANH SACH EMPLOYEE", [this]()
		{
			this->hienThiTatCaEmployee();
		});
		return true;

	case LuaChon::THOAT:
		this->_giaoDien.hienThiManHinh("THOAT ADMIN");
		this->_giaoDien.hienThiThongBao("Admin " + strUsername + " da thoat.");
		this->_giaoDien.choEnter("Nhan Enter de quay lai Dang Nhap He Thong...");
		return false;

	default:
		this->_giaoDien.hienThiLoi("Lua chon khong hop le.");
		this->_giaoDien.choEnter();
		return true;
	}
}

/**********************************************************
* @Description Nhap thong tin va them Employee moi
*
* @return Khong co gia tri tra ve
* @attention Dung lai neu bat ky du lieu nhap nao khong hop le
**********************************************************/
void Admin::themEmployee() const
{
	std::string strUsername;
	std::string strHoTen;
	std::string strDiaChi;
	std::string strSoDienThoai;
	std::string strEmail;

	const bool bNhapHopLe =
		this->nhapUsernameMoi("Username: ", strUsername) &&
		this->nhapHoTen("Ho ten: ", strHoTen) &&
		this->nhapDiaChi("Dia chi: ", strDiaChi) &&
		this->nhapSoDienThoai("So dien thoai: ", "", strSoDienThoai) &&
		this->nhapEmail("Email: ", "", strEmail);

	if (!bNhapHopLe)
	{
		return;
	}

	this->luuEmployeeMoi(strUsername, HoSoNhanVien(strHoTen, strDiaChi, strSoDienThoai, strEmail));
}

/**********************************************************
* @Description Xoa Employee sau khi Admin xac nhan
*
* @return Khong co gia tri tra ve
**********************************************************/
void Admin::xoaEmployee() const
{
	std::string strUsername;

	if (!this->nhapUsernameTonTai("Username can xoa: ", strUsername))
	{
		return;
	}

	if (!this->_giaoDien.xacNhan("Ban co chac chan muon xoa Employee " + strUsername + "?"))
	{
		this->_giaoDien.hienThiThongBao("Da huy thao tac xoa.");
		return;
	}

	if (!this->_xuLyFile.xoaTaiKhoan(strUsername))
	{
		this->_giaoDien.hienThiLoi("Khong the xoa Employee " + strUsername + ".");
		return;
	}

	this->_giaoDien.hienThiThongBao("Da xoa Employee " + strUsername + ".");
}

/**********************************************************
* @Description Tim Employee theo username va hien thi ho so
*
* @return Khong co gia tri tra ve
**********************************************************/
void Admin::timEmployee() const
{
	std::string strUsername;
	HoSoNhanVien hoSoNhanVien;

	if (!this->nhapUsernameTonTai("Username can tim: ", strUsername))
	{
		return;
	}

	if (!this->_xuLyFile.docHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		this->_giaoDien.hienThiLoi("Khong doc duoc ho so cua " + strUsername + ".");
		return;
	}

	this->_giaoDien.hienThiDong("");
	this->hienThiHoSo(strUsername, hoSoNhanVien);
}

/**********************************************************
* @Description Chon thuoc tinh va cap nhat thong tin Employee
*
* @return Khong co gia tri tra ve
* @attention Thoat vong lap khi Admin chon quay lai hoac cap nhat that bai
**********************************************************/
void Admin::capNhatEmployee() const
{
	std::string strUsername;
	HoSoNhanVien hoSoNhanVien;

	if (!this->nhapUsernameTonTai("Username can cap nhat: ", strUsername))
	{
		return;
	}

	if (!this->_xuLyFile.docHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		this->_giaoDien.hienThiLoi("Khong doc duoc ho so cua " + strUsername + ".");
		return;
	}

	this->_giaoDien.hienThiDong("");
	this->hienThiHoSo(strUsername, hoSoNhanVien);
	this->_giaoDien.choEnter("Nhan ENTER de chon thuoc tinh can cap nhat...");

	const std::vector<std::string> vecThuocTinh =
	{
		"1. Ho ten",
		"2. Dia chi",
		"3. So dien thoai",
		"4. Email"
	};

	while (true)
	{
		const int iLuaChon = this->_giaoDien.chonMenu("CHON THUOC TINH CAN CAP NHAT", vecThuocTinh, true);

		if (iLuaChon == MENU_CANCELLED)
		{
			this->_giaoDien.hienThiManHinh("CAP NHAT EMPLOYEE");
			this->_giaoDien.hienThiThongBao("Ket thuc cap nhat " + strUsername + ".");
			return;
		}

		if (!this->capNhatThuocTinh(static_cast<ThuocTinh>(iLuaChon), strUsername, hoSoNhanVien))
		{
			return;
		}

		this->_giaoDien.choEnter("Nhan ENTER de tiep tuc cap nhat...");
	}
}

/**********************************************************
* @Description Hien thi danh sach tat ca Employee dang bang
*
* @return Khong co gia tri tra ve
**********************************************************/
void Admin::hienThiTatCaEmployee() const
{
	DanhSachLienKet<TaiKhoan> danhSach;

	if (!this->_xuLyFile.docDanhSachTaiKhoan(danhSach))
	{
		this->_giaoDien.hienThiLoi("Khong doc duoc file " + std::string(EMPLOYEE_FILE_PATH) + ".");
		return;
	}

	if (danhSach.laRong())
	{
		this->_giaoDien.hienThiThongBao("Chua co Employee nao.");
		return;
	}

	const std::vector<std::string> vecTieuDe = {"STT", "USERNAME", "HO TEN", "DIA CHI", "SDT", "EMAIL"};
	const std::vector<size_t> vecDoRongCot =
	{
		COLUMN_WIDTH_INDEX, COLUMN_WIDTH_USERNAME, COLUMN_WIDTH_FULLNAME,
		COLUMN_WIDTH_ADDRESS, COLUMN_WIDTH_PHONE, COLUMN_WIDTH_EMAIL
	};
	BangDuLieu bangEmployee(vecTieuDe, vecDoRongCot);
	size_t uiSoThuTu = 0;

	danhSach.duyet([&](const TaiKhoan& taiKhoan)
	{
		++uiSoThuTu;
		bangEmployee.themDong(this->taoDongEmployee(uiSoThuTu, taiKhoan.getUsername()));
	});

	this->_giaoDien.hienThiDong("");
	bangEmployee.hienThi();
	this->_giaoDien.hienThiDong("Tong so Employee: " + std::to_string(danhSach.layKichThuoc()));
}

/**********************************************************
* @Description Nhap username moi va kiem tra hop le, khong phai ten danh rieng, khong trung
*
* @return true neu username dung de tao moi, false neu nguoc lai
**********************************************************/
bool Admin::nhapUsernameMoi(const std::string& strLoiNhac, std::string& strUsername) const
{
	strUsername = this->_giaoDien.nhapChuoi(strLoiNhac);

	if (!KiemTraDuLieu::laUsernameHopLe(strUsername))
	{
		this->_giaoDien.hienThiLoi(
			"Username chi gom chu cai, chu so, dau gach duoi, dai " +
			std::to_string(MIN_USERNAME_LENGTH) + " den " +
			std::to_string(MAX_USERNAME_LENGTH) + " ky tu.");
		return false;
	}

	if (KiemTraDuLieu::laUsernameDanhRieng(strUsername))
	{
		this->_giaoDien.hienThiLoi("Username la ten danh rieng cua he thong.");
		return false;
	}

	if (this->_xuLyFile.kiemTraUsernameTrung(strUsername))
	{
		this->_giaoDien.hienThiLoi("Username da ton tai (khong phan biet hoa thuong).");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Nhap username va kiem tra Employee da ton tai
*
* @return true neu Employee ton tai, false neu nguoc lai
**********************************************************/
bool Admin::nhapUsernameTonTai(const std::string& strLoiNhac, std::string& strUsername) const
{
	strUsername = this->_giaoDien.nhapChuoi(strLoiNhac);

	if (strUsername.empty())
	{
		this->_giaoDien.hienThiLoi("Username khong duoc de trong.");
		return false;
	}

	if (!this->_xuLyFile.kiemTraUsernameTonTai(strUsername))
	{
		this->_giaoDien.hienThiLoi("Khong tim thay Employee " + strUsername + ".");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Nhap, chuan hoa khoang trang va kiem tra ho ten
*
* @return true neu ho ten hop le, false neu nguoc lai
**********************************************************/
bool Admin::nhapHoTen(const std::string& strLoiNhac, std::string& strHoTen) const
{
	strHoTen = ChuoiUtf8::chuanHoaKhoangTrang(this->_giaoDien.nhapChuoi(strLoiNhac));

	if (!KiemTraDuLieu::laHoTenHopLe(strHoTen))
	{
		this->_giaoDien.hienThiLoi(
			"Ho ten gom it nhat 2 tu, chi chua chu cai, khoang trang, '-' va ''' "
			"(khong bat dau/ket thuc bang '-' hay ''', khong viet lien tiep), dai " +
			std::to_string(MIN_FULLNAME_LENGTH) + " den " +
			std::to_string(MAX_FULLNAME_LENGTH) + " ky tu.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Nhap, chuan hoa khoang trang va kiem tra dia chi
*
* @return true neu dia chi hop le, false neu nguoc lai
**********************************************************/
bool Admin::nhapDiaChi(const std::string& strLoiNhac, std::string& strDiaChi) const
{
	strDiaChi = ChuoiUtf8::chuanHoaKhoangTrang(this->_giaoDien.nhapChuoi(strLoiNhac));

	if (!KiemTraDuLieu::laDiaChiHopLe(strDiaChi))
	{
		this->_giaoDien.hienThiLoi(
			"Dia chi dai " + std::to_string(MIN_ADDRESS_LENGTH) + " den " +
			std::to_string(MAX_ADDRESS_LENGTH) + " byte va khong chua ky tu dieu khien.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Nhap va kiem tra so dien thoai (dinh dang va khong trung)
*
* @return true neu so dien thoai hop le, false neu nguoc lai
* @attention strUsernameBoQua la username khong xet trung (dung khi cap nhat)
**********************************************************/
bool Admin::nhapSoDienThoai(const std::string& strLoiNhac, const std::string& strUsernameBoQua,
							std::string& strSoDienThoai) const
{
	strSoDienThoai = this->_giaoDien.nhapChuoi(strLoiNhac);

	if (!KiemTraDuLieu::laSoDienThoaiHopLe(strSoDienThoai))
	{
		this->_giaoDien.hienThiLoi(
			"So dien thoai gom dung " + std::to_string(PHONE_LENGTH) +
			" chu so va bat dau bang 0.");
		return false;
	}

	if (this->_xuLyFile.kiemTraTrungSoDienThoai(strSoDienThoai, strUsernameBoQua))
	{
		this->_giaoDien.hienThiLoi("So dien thoai da thuoc Employee khac.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Nhap va kiem tra email (dinh dang va khong trung)
*
* @return true neu email hop le, false neu nguoc lai
* @attention strUsernameBoQua la username khong xet trung (dung khi cap nhat)
**********************************************************/
bool Admin::nhapEmail(const std::string& strLoiNhac, const std::string& strUsernameBoQua,
					  std::string& strEmail) const
{
	strEmail = this->_giaoDien.nhapChuoi(strLoiNhac);

	if (!KiemTraDuLieu::laEmailHopLe(strEmail))
	{
		this->_giaoDien.hienThiLoi("Email khong dung dinh dang (vi du: ten@congty.com).");
		return false;
	}

	if (this->_xuLyFile.kiemTraTrungEmail(strEmail, strUsernameBoQua))
	{
		this->_giaoDien.hienThiLoi("Email da thuoc Employee khac.");
		return false;
	}

	return true;
}

/**********************************************************
* @Description Luu tai khoan va ho so cua Employee moi
*
* @return Khong co gia tri tra ve
* @attention Neu ghi ho so that bai thi xoa tai khoan vua them
* @attention Hien thi ket qua (thanh cong hoac loi) cho nguoi dung
**********************************************************/
void Admin::luuEmployeeMoi(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const
{
	if (!this->_xuLyFile.themTaiKhoan(TaiKhoan(strUsername, DEFAULT_PASSWORD)))
	{
		this->_giaoDien.hienThiLoi("Khong the them tai khoan vao " + std::string(EMPLOYEE_FILE_PATH) + ".");
		return;
	}

	if (!this->_xuLyFile.ghiHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		if (this->_xuLyFile.xoaTaiKhoan(strUsername))
		{
			this->_giaoDien.hienThiLoi("Khong the tao file ho so. Da huy them Employee.");
		}
		else
		{
			this->_giaoDien.hienThiLoi("Khong the tao file ho so va khong hoan tac duoc tai khoan " + strUsername + ".");
		}

		return;
	}

	this->_giaoDien.hienThiThongBao("Them Employee " + strUsername + " thanh cong.");
	this->_giaoDien.hienThiDong("Password mac dinh: " + std::string(DEFAULT_PASSWORD));
}

/**********************************************************
* @Description Cap nhat mot thuoc tinh cua Employee va ghi vao file ho so
*
* @return true neu cap nhat thanh cong, false neu nguoc lai
**********************************************************/
bool Admin::capNhatThuocTinh(const ThuocTinh eThuocTinh, const std::string& strUsername,
							 HoSoNhanVien& hoSoNhanVien) const
{
	bool bNhapHopLe = false;

	switch (eThuocTinh)
	{
	case ThuocTinh::HO_TEN:
		bNhapHopLe = this->capNhatHoTen(hoSoNhanVien);
		break;

	case ThuocTinh::DIA_CHI:
		bNhapHopLe = this->capNhatDiaChi(hoSoNhanVien);
		break;

	case ThuocTinh::SO_DIEN_THOAI:
		bNhapHopLe = this->capNhatSoDienThoai(strUsername, hoSoNhanVien);
		break;

	case ThuocTinh::EMAIL:
		bNhapHopLe = this->capNhatEmail(strUsername, hoSoNhanVien);
		break;

	default:
		this->_giaoDien.hienThiLoi("Lua chon khong hop le.");
		break;
	}

	if (!bNhapHopLe)
	{
		return false;
	}

	if (!this->_xuLyFile.capNhatHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		this->_giaoDien.hienThiLoi("Khong the ghi file ho so.");
		return false;
	}

	this->_giaoDien.hienThiThongBao("Cap nhat thanh cong.");
	return true;
}

/**********************************************************
* @Description Nhap ho ten moi va cap nhat vao doi tuong HoSoNhanVien
*
* @return true neu nhap hop le, false neu nguoc lai
**********************************************************/
bool Admin::capNhatHoTen(HoSoNhanVien& hoSoNhanVien) const
{
	std::string strHoTen;

	this->_giaoDien.hienThiManHinh("CAP NHAT HO TEN");
	this->_giaoDien.hienThiDong("\nHo ten hien tai: " + hoSoNhanVien.getHoTen());

	if (!this->nhapHoTen("Ho ten moi: ", strHoTen))
	{
		return false;
	}

	hoSoNhanVien.setHoTen(strHoTen);
	return true;
}

/**********************************************************
* @Description Nhap dia chi moi va cap nhat vao doi tuong HoSoNhanVien
*
* @return true neu nhap hop le, false neu nguoc lai
**********************************************************/
bool Admin::capNhatDiaChi(HoSoNhanVien& hoSoNhanVien) const
{
	std::string strDiaChi;

	this->_giaoDien.hienThiManHinh("CAP NHAT DIA CHI");
	this->_giaoDien.hienThiDong("\nDia chi hien tai: " + hoSoNhanVien.getDiaChi());

	if (!this->nhapDiaChi("Dia chi moi: ", strDiaChi))
	{
		return false;
	}

	hoSoNhanVien.setDiaChi(strDiaChi);
	return true;
}

/**********************************************************
* @Description Nhap so dien thoai moi va cap nhat vao doi tuong HoSoNhanVien
*
* @return true neu nhap hop le, false neu nguoc lai
**********************************************************/
bool Admin::capNhatSoDienThoai(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const
{
	std::string strSoDienThoai;

	this->_giaoDien.hienThiManHinh("CAP NHAT SO DIEN THOAI");
	this->_giaoDien.hienThiDong("\nSo dien thoai hien tai: " + hoSoNhanVien.getSoDienThoai());

	if (!this->nhapSoDienThoai("So dien thoai moi: ", strUsername, strSoDienThoai))
	{
		return false;
	}

	hoSoNhanVien.setSoDienThoai(strSoDienThoai);
	return true;
}

/**********************************************************
* @Description Nhap email moi va cap nhat vao doi tuong HoSoNhanVien
*
* @return true neu nhap hop le, false neu nguoc lai
**********************************************************/
bool Admin::capNhatEmail(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const
{
	std::string strEmail;

	this->_giaoDien.hienThiManHinh("CAP NHAT EMAIL");
	this->_giaoDien.hienThiDong("\nEmail hien tai: " + hoSoNhanVien.getEmail());

	if (!this->nhapEmail("Email moi: ", strUsername, strEmail))
	{
		return false;
	}

	hoSoNhanVien.setEmail(strEmail);
	return true;
}

/**********************************************************
* @Description Tao mot dong du lieu Employee cho bang hien thi
*
* @return Vector cac o cua dong (STT, username, ho ten, dia chi, SDT, email)
* @attention Neu khong doc duoc ho so thi o ho ten hien thi MISSING_PROFILE_TEXT
**********************************************************/
std::vector<std::string> Admin::taoDongEmployee(const size_t uiSoThuTu,
												const std::string& strUsername) const
{
	HoSoNhanVien hoSoNhanVien;
	std::vector<std::string> vecDong;

	vecDong.push_back(std::to_string(uiSoThuTu));
	vecDong.push_back(strUsername);

	if (!this->_xuLyFile.docHoSoNhanVien(strUsername, hoSoNhanVien))
	{
		vecDong.push_back(MISSING_PROFILE_TEXT);
		return vecDong;
	}

	vecDong.push_back(hoSoNhanVien.getHoTen());
	vecDong.push_back(hoSoNhanVien.getDiaChi());
	vecDong.push_back(hoSoNhanVien.getSoDienThoai());
	vecDong.push_back(hoSoNhanVien.getEmail());
	return vecDong;
}
