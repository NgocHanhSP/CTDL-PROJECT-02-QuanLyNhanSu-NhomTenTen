#include "../include/GiaoDien.h"

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "../include/ChuoiUtf8.h"

/**********************************************************
* @Description Hien thi menu dang nhap va nhan lua chon
*
* @return So thu tu muc duoc chon
**********************************************************/
int GiaoDien::hienThiMenuDangNhap() const
{
	const std::vector<std::string> vecLuaChon =
	{
		"1. Dang nhap Admin",
		"2. Dang nhap Employee",
		"3. Quen password (danh cho Employee)",
		"4. Thoat chuong trinh"
	};

	return this->chonMenu("DANG NHAP HE THONG", vecLuaChon);
}

/**********************************************************
* @Description Hien thi menu Admin va nhan lua chon
*
* @return So thu tu muc duoc chon
**********************************************************/
int GiaoDien::hienThiMenuAdmin() const
{
	const std::vector<std::string> vecLuaChon =
	{
		"1. Them Employee",
		"2. Xoa Employee",
		"3. Tim Employee",
		"4. Cap nhat Employee",
		"5. Hien thi thong tin Employee",
		"6. Thoat"
	};

	return this->chonMenu("MENU ADMIN", vecLuaChon);
}

/**********************************************************
* @Description Hien thi menu Employee va nhan lua chon
*
* @return So thu tu muc duoc chon
**********************************************************/
int GiaoDien::hienThiMenuEmployee() const
{
	const std::vector<std::string> vecLuaChon =
	{
		"1. Xem thong tin tai khoan",
		"2. Doi password",
		"3. Thoat"
	};

	return this->chonMenu("MENU EMPLOYEE", vecLuaChon);
}

/**********************************************************
* @Description Hien thi menu chon bang phim LEN/XUONG va ENTER
*
* @return So thu tu muc duoc chon (bat dau tu MENU_FIRST_OPTION), MENU_CANCELLED neu chon quay lai hoac menu rong
* @attention Phim B chi co tac dung khi bChoPhepQuayLai la true
**********************************************************/
int GiaoDien::chonMenu(const std::string& strTieuDe, const std::vector<std::string>& vecLuaChon,
					   const bool bChoPhepQuayLai) const
{
	if (vecLuaChon.empty())
	{
		return MENU_CANCELLED;
	}

	const std::vector<std::string> vecCanLe = this->canLeLuaChon(vecLuaChon);
	std::vector<int> vecToaDoY;

	this->veMenu(strTieuDe, vecCanLe, bChoPhepQuayLai, vecToaDoY);

	return this->docLuaChonMenu(vecCanLe, vecToaDoY, bChoPhepQuayLai);
}

/**********************************************************
* @Description Xoa man hinh console
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::xoaManHinh() const
{
	system("cls");
}

/**********************************************************
* @Description Hien thi khung tieu de
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiTieuDe(const std::string& strTieuDe) const
{
	this->veTieuDe(strTieuDe);
}

/**********************************************************
* @Description Xoa man hinh va hien thi tieu de
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiManHinh(const std::string& strTieuDe) const
{
	this->xoaManHinh();
	this->hienThiTieuDe(strTieuDe);
}

/**********************************************************
* @Description Hien thi chuoi, co the thut le theo kieu man hinh dang nhap
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiChu(const std::string& strNoiDung, const bool bCanLe) const
{
	if (bCanLe)
	{
		std::cout << LOGIN_INDENT;
	}

	std::cout << strNoiDung;
}

/**********************************************************
* @Description Hien thi chuoi va xuong dong
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiDong(const std::string& strNoiDung) const
{
	std::cout << strNoiDung << '\n';
}

/**********************************************************
* @Description Hien thi thong bao thanh cong (mau xanh)
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiThongBao(const std::string& strThongBao) const
{
	this->datMau(MauSac::THANH_CONG);
	std::cout << "\n[THONG BAO] " << strThongBao << '\n';
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Hien thi thong bao loi (mau do)
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::hienThiLoi(const std::string& strThongBao) const
{
	this->datMau(MauSac::LOI);
	std::cout << "\n[LOI] " << strThongBao << '\n';
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Hien thi loi nhac va cho nguoi dung nhan ENTER
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::choEnter(const std::string& strLoiNhac) const
{
	this->datMau(MauSac::TIEU_DE);
	std::cout << '\n';
	this->inCanGiua(strLoiNhac);
	std::cout << '\n';
	this->datMau(MauSac::MAC_DINH);

	while (true)
	{
		const int iPhim = _getch();

		if (iPhim == KEY_ENTER)
		{
			break;
		}

		if (iPhim == KEY_EXTENDED_A || iPhim == KEY_EXTENDED_B)
		{
			_getch();
		}
	}
}

/**********************************************************
* @Description Nhap mot dong van ban
*
* @return Chuoi nguoi dung nhap
**********************************************************/
std::string GiaoDien::nhapChuoi(const std::string& strLoiNhac, const bool bCanLe) const
{
	std::string strGiaTri;

	this->hienThiChu(strLoiNhac, bCanLe);
	std::getline(std::cin, strGiaTri);

	return strGiaTri;
}

/**********************************************************
* @Description Nhap password, hien thi dau * thay cho ky tu
*
* @return Password nguoi dung nhap
* @attention Ho tro phim BACKSPACE, chi nhan ky tu ASCII in duoc
**********************************************************/
std::string GiaoDien::nhapMatKhau(const std::string& strLoiNhac, const bool bCanLe) const
{
	std::string strMatKhau;

	this->hienThiChu(strLoiNhac, bCanLe);

	while (true)
	{
		const int iPhim = _getch();

		if (iPhim == KEY_ENTER)
		{
			std::cout << '\n';
			return strMatKhau;
		}

		if (iPhim == KEY_BACKSPACE)
		{
			if (!strMatKhau.empty())
			{
				strMatKhau.pop_back();
				std::cout << "\b \b";
			}
		}
		else if (iPhim == KEY_EXTENDED_A || iPhim == KEY_EXTENDED_B)
		{
			_getch();
		}
		else if (iPhim >= KEY_PRINTABLE_FIRST && iPhim <= KEY_PRINTABLE_LAST)
		{
			strMatKhau += static_cast<char>(iPhim);
			std::cout << PASSWORD_MASK;
		}
	}
}

/**********************************************************
* @Description Hien thi cau hoi xac nhan va doi nhan phim Y hoac N
*
* @return true neu chon Y, false neu chon N
**********************************************************/
bool GiaoDien::xacNhan(const std::string& strCauHoi) const
{
	this->datMau(MauSac::TIEU_DE);
	std::cout << "\n[XAC NHAN] " << strCauHoi << " (Y/N): ";
	this->datMau(MauSac::MAC_DINH);

	while (true)
	{
		const int iPhim = _getch();

		if (iPhim == KEY_YES_LOWER || iPhim == KEY_YES_UPPER)
		{
			std::cout << "Y\n";
			return true;
		}

		if (iPhim == KEY_NO_LOWER || iPhim == KEY_NO_UPPER)
		{
			std::cout << "N\n";
			return false;
		}
	}
}

/**********************************************************
* @Description Dat bang ma console sang UTF-8
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::khoiTaoMaHoa() const
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
}

/**********************************************************
* @Description Dat mau chu cho console
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::datMau(const MauSac eMau) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(eMau));
}

/**********************************************************
* @Description Tinh so khoang trang can chen ben trai de can giua chuoi
*
* @return So khoang trang, khong am
**********************************************************/
int GiaoDien::tinhLeTrai(const std::string& strNoiDung) const
{
	const int iDoDai = static_cast<int>(ChuoiUtf8::demKyTu(strNoiDung));
	const int iLeTrai = (CONSOLE_WIDTH - iDoDai) / CENTER_DIVISOR;

	return (iLeTrai < 0) ? 0 : iLeTrai;
}

/**********************************************************
* @Description In chuoi can giua theo CONSOLE_WIDTH
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::inCanGiua(const std::string& strNoiDung) const
{
	std::cout << std::string(static_cast<size_t>(this->tinhLeTrai(strNoiDung)), ' ') << strNoiDung;
}

/**********************************************************
* @Description Ve mot duong ke ngang bang ky tu cKyTu
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::veDuongKe(const char cKyTu) const
{
	const int iLeTrai = (CONSOLE_WIDTH - LINE_WIDTH) / CENTER_DIVISOR;

	this->datMau(MauSac::DUONG_KE);
	std::cout << std::string(static_cast<size_t>(iLeTrai), ' ')
			  << std::string(static_cast<size_t>(LINE_WIDTH), cKyTu) << '\n';
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Ve khung tieu de, tieu de qua dai se bi cat bot
*
* @return Khong co gia tri tra ve
* @attention Dat bang ma UTF-8 tai day, moi man hinh chi dat mot lan
**********************************************************/
void GiaoDien::veTieuDe(const std::string& strTieuDe) const
{
	this->khoiTaoMaHoa();

	const int iDoRongNoiDung = TITLE_WIDTH - TITLE_BORDER_WIDTH;
	const std::string strHienThi = ChuoiUtf8::catKyTu(strTieuDe, static_cast<size_t>(iDoRongNoiDung));
	const int iDoDai = static_cast<int>(ChuoiUtf8::demKyTu(strHienThi));
	const int iTrai = (iDoRongNoiDung - iDoDai) / CENTER_DIVISOR;
	const int iPhai = iDoRongNoiDung - iDoDai - iTrai;
	const int iLeTrai = (CONSOLE_WIDTH - TITLE_WIDTH) / CENTER_DIVISOR;
	const std::string strLe(static_cast<size_t>(iLeTrai), ' ');
	const std::string strVien(static_cast<size_t>(TITLE_WIDTH), BORDER_CHAR);

	std::cout << '\n';
	this->datMau(MauSac::DUONG_KE);
	std::cout << strLe << strVien << '\n' << strLe << BORDER_CHAR;

	this->datMau(MauSac::TIEU_DE);
	std::cout << std::string(static_cast<size_t>(iTrai), ' ') << strHienThi
			  << std::string(static_cast<size_t>(iPhai), ' ');

	this->datMau(MauSac::DUONG_KE);
	std::cout << BORDER_CHAR << '\n' << strLe << strVien << '\n';
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Them khoang trang vao cac muc menu de cung do dai
*
* @return Vector cac muc da can le
**********************************************************/
std::vector<std::string> GiaoDien::canLeLuaChon(const std::vector<std::string>& vecLuaChon) const
{
	size_t uiDoDaiLonNhat = 0;

	for (size_t uiChiSo = 0; uiChiSo < vecLuaChon.size(); ++uiChiSo)
	{
		const size_t uiDoDai = ChuoiUtf8::demKyTu(vecLuaChon[uiChiSo]);

		if (uiDoDai > uiDoDaiLonNhat)
		{
			uiDoDaiLonNhat = uiDoDai;
		}
	}

	std::vector<std::string> vecCanLe;

	for (size_t uiChiSo = 0; uiChiSo < vecLuaChon.size(); ++uiChiSo)
	{
		const size_t uiDoDai = ChuoiUtf8::demKyTu(vecLuaChon[uiChiSo]);

		vecCanLe.push_back(vecLuaChon[uiChiSo] + std::string(uiDoDaiLonNhat - uiDoDai, ' '));
	}

	return vecCanLe;
}

/**********************************************************
* @Description Ve menu va luu toa do Y cua tung dong
*
* @return Khong co gia tri tra ve
* @attention vecToaDoY tra ve toa do Y cua tung muc de to mau lai khi di chuyen
**********************************************************/
void GiaoDien::veMenu(const std::string& strTieuDe, const std::vector<std::string>& vecCanLe,
					  const bool bChoPhepQuayLai, std::vector<int>& vecToaDoY) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	this->hienThiManHinh(strTieuDe);
	std::cout << '\n';
	vecToaDoY.clear();

	for (size_t uiChiSo = 0; uiChiSo < vecCanLe.size(); ++uiChiSo)
	{
		CONSOLE_SCREEN_BUFFER_INFO thongTin = CONSOLE_SCREEN_BUFFER_INFO();

		GetConsoleScreenBufferInfo(hConsole, &thongTin);
		vecToaDoY.push_back(static_cast<int>(thongTin.dwCursorPosition.Y));

		this->datMau(uiChiSo == 0 ? MauSac::DONG_DANG_CHON : MauSac::DONG_BINH_THUONG);
		this->inCanGiua(vecCanLe[uiChiSo]);
		std::cout << "\n\n";
	}

	this->veDuongKe(BORDER_CHAR);
	std::cout << '\n';
	this->datMau(MauSac::TIEU_DE);

	if (bChoPhepQuayLai)
	{
		this->inCanGiua("Dung phim LEN / XUONG, ENTER de chon, B de quay lai");
	}
	else
	{
		this->inCanGiua("Dung phim LEN / XUONG va ENTER de chon");
	}

	std::cout << '\n';
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Ve lai mot dong menu tai toa do iToaDoY, to mau neu dang duoc chon
*
* @return Khong co gia tri tra ve
**********************************************************/
void GiaoDien::veDongMenu(const std::string& strDong, const int iToaDoY, const bool bDangChon) const
{
	COORD toaDo = COORD();

	toaDo.X = static_cast<SHORT>(this->tinhLeTrai(strDong));
	toaDo.Y = static_cast<SHORT>(iToaDoY);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), toaDo);
	this->datMau(bDangChon ? MauSac::DONG_DANG_CHON : MauSac::DONG_BINH_THUONG);
	std::cout << strDong << std::flush;
	this->datMau(MauSac::MAC_DINH);
}

/**********************************************************
* @Description Doc phim LEN/XUONG/ENTER/B de chon muc menu
*
* @return So thu tu muc duoc chon, MENU_CANCELLED neu chon quay lai
**********************************************************/
int GiaoDien::docLuaChonMenu(const std::vector<std::string>& vecCanLe,
							 const std::vector<int>& vecToaDoY, const bool bChoPhepQuayLai) const
{
	const int iSoMuc = static_cast<int>(vecCanLe.size());
	int iDangChon = 0;

	// Phim mui ten tra ve 2 ma lien tiep, bPhimMoRong phan biet voi phim thuong cung ma.
	while (true)
	{
		bool bPhimMoRong = false;
		const int iPhim = this->docPhim(bPhimMoRong);
		const int iLuaChonCu = iDangChon;

		if (bPhimMoRong && iPhim == KEY_UP)
		{
			// Cong them iSoMuc de tu muc dau quay vong len muc cuoi.
			iDangChon = (iDangChon - 1 + iSoMuc) % iSoMuc;
		}
		else if (bPhimMoRong && iPhim == KEY_DOWN)
		{
			iDangChon = (iDangChon + 1) % iSoMuc;
		}
		else if (!bPhimMoRong && iPhim == KEY_ENTER)
		{
			this->xoaManHinh();
			return iDangChon + MENU_FIRST_OPTION;
		}
		else if (!bPhimMoRong && bChoPhepQuayLai && (iPhim == KEY_BACK_LOWER || iPhim == KEY_BACK_UPPER))
		{
			this->xoaManHinh();
			return MENU_CANCELLED;
		}
		else
		{
			// Phim khac bi bo qua, khong can ve lai menu.
			continue;
		}

		this->veDongMenu(vecCanLe[static_cast<size_t>(iLuaChonCu)],
						 vecToaDoY[static_cast<size_t>(iLuaChonCu)], false);
		this->veDongMenu(vecCanLe[static_cast<size_t>(iDangChon)],
						 vecToaDoY[static_cast<size_t>(iDangChon)], true);
	}
}

/**********************************************************
* @Description Doc mot phim tu ban phim
*
* @return Ma phim
* @attention bPhimMoRong tra ve true neu la phim mo rong (phim mui ten...)
**********************************************************/
int GiaoDien::docPhim(bool& bPhimMoRong) const
{
	int iPhim = _getch();

	bPhimMoRong = false;

	if (iPhim == KEY_EXTENDED_A || iPhim == KEY_EXTENDED_B)
	{
		iPhim = _getch();
		bPhimMoRong = true;
	}

	return iPhim;
}
