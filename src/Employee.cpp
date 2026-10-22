// Employee.cpp
// Muc dich: Cai dat chuc nang nhan vien va doi mat khau.

#include "../include/Employee.h"

#include <cctype>
#include <iostream>C:\msys64\ucrt64\bin\g++.exe -g src/*.cpp -I include -o main.exe

#include "../include/GiaoDien.h"
#include "../include/XuLyFile.h"
#include "../include/TaiKhoan.h"
#include "../include/NhanVien.h"
#include "../include/Constants.h"

namespace
{
    // XuLyFile khong co ham static nen dung chung mot doi tuong cho file nay.
    XuLyFile& xuLyFile()
    {
        static XuLyFile doiTuongXuLyFile;
        return doiTuongXuLyFile;
    }

    // GiaoDien khong co ham static nen dung chung mot doi tuong cho file nay.
    GiaoDien& giaoDien()
    {
        static GiaoDien doiTuongGiaoDien;
        return doiTuongGiaoDien;
    }

    // nhapMatKhauAn() khong co nhan, nen in nhan truoc roi moi nhap an ky tu.
    std::string nhapMatKhauAn(const std::string& strNhan)
    {
        std::cout << strNhan;
        return giaoDien().nhapMatKhau();
    }

    // Cac lua chon trong menu Employee.
    const int MENU_XEM_THONG_TIN = 1;
    const int MENU_DOI_MAT_KHAU = 2;
    const int MENU_THOAT = 3;
    const int LUA_CHON_KHONG_HOP_LE = 0;

    // So lan duoc thu khi doi mat khau lan dau.
    // (Do dai toi thieu cua mat khau lay tu MIN_PASSWORD_LENGTH trong Constants.h.)
    const int MAX_FIRST_CHANGE_ATTEMPTS = 3;

    std::string thongBaoYeuCauMatKhau()
    {
        return "Mat khau phai co it nhat " + std::to_string(MIN_PASSWORD_LENGTH)
               + " ky tu, gom chu hoa, chu thuong, chu so, ky tu dac biet va khong co khoang trang.";
    }

    // Tra ve ly do mat khau moi khong hop le; chuoi rong neu hop le.
    std::string layLoiMatKhauMoi(bool bMatKhauManh, const std::string& strMatKhauMoi)
    {
        if (!bMatKhauManh)
        {
            return thongBaoYeuCauMatKhau();
        }
        if (strMatKhauMoi == DEFAULT_PASSWORD)
        {
            return "Mat khau moi khong duoc trung mat khau mac dinh.";
        }
        return "";
    }

    std::string nhapChuoi(const std::string& strNhan)
    {
        std::string strGiaTri = "";
        std::cout << strNhan;
        std::getline(std::cin, strGiaTri);
        return strGiaTri;
    }

    int nhapLuaChon()
    {
        const std::string strDong = nhapChuoi("Lua chon: ");
        if (strDong.size() != 1 || !std::isdigit(static_cast<unsigned char>(strDong[0])))
        {
            return LUA_CHON_KHONG_HOP_LE;
        }
        return strDong[0] - '0';
    }

    void tamDung()
    {
        nhapChuoi("Nhan Enter de tiep tuc...");
    }
}

void Employee::hienThiMenu(const std::string& strUsername)
{
    TaiKhoan taiKhoan;
    if (!xuLyFile().docTaiKhoan(strUsername, taiKhoan))
    {
        giaoDien().hienThiLoi("Khong doc duoc thong tin tai khoan.");
        return;
    }

    // Lan dang nhap dau tien (con mat khau mac dinh): bat buoc doi truoc khi vao menu.
    if (taiKhoan.getPassword() == DEFAULT_PASSWORD)
    {
        if (!this->doiMatKhauLanDau(strUsername))
        {
            giaoDien().hienThiLoi("Ban phai doi mat khau lan dau de tiep tuc su dung chuong trinh.");
            return;
        }
    }

    bool bTiepTuc = true;
    while (bTiepTuc)
    {
        giaoDien().hienThiMenuEmployee();
        const int iLuaChon = nhapLuaChon();

        switch (iLuaChon)
        {
        case MENU_XEM_THONG_TIN:
            this->xemThongTin(strUsername);
            tamDung();
            break;
        case MENU_DOI_MAT_KHAU:
            this->doiMatKhau(strUsername);
            tamDung();
            break;
        case MENU_THOAT:
            bTiepTuc = false;
            break;
        default:
            giaoDien().hienThiLoi("Lua chon khong hop le.");
            tamDung();
            break;
        }
    }
}

void Employee::xemThongTin(const std::string& strUsername)
{
    NhanVien nhanVien;
    if (!xuLyFile().docNhanVien(strUsername, nhanVien))
    {
        giaoDien().hienThiLoi("Khong doc duoc ho so ca nhan.");
        return;
    }

    std::cout << "Username      : " << strUsername << "\n"
              << "Ho ten        : " << nhanVien.getHoTen() << "\n"
              << "Dia chi       : " << nhanVien.getDiaChi() << "\n"
              << "So dien thoai : " << nhanVien.getSoDienThoai() << "\n"
              << "Email         : " << nhanVien.getEmail() << "\n";
}

void Employee::doiMatKhau(const std::string& strUsername)
{
    TaiKhoan taiKhoan;
    if (!xuLyFile().docTaiKhoan(strUsername, taiKhoan))
    {
        giaoDien().hienThiLoi("Khong doc duoc thong tin tai khoan.");
        return;
    }

    // Xac nhan chu tai khoan truoc khi cho nhap mat khau moi.
    const std::string strMatKhauCu = nhapMatKhauAn("Mat khau hien tai: ");
    if (strMatKhauCu != taiKhoan.getPassword())
    {
        giaoDien().hienThiLoi("Mat khau hien tai khong dung.");
        return;
    }

    const std::string strMatKhauMoi = nhapMatKhauAn("Mat khau moi: ");
    const std::string strLoi = layLoiMatKhauMoi(this->kiemTraMatKhauManh(strMatKhauMoi), strMatKhauMoi);
    if (!strLoi.empty())
    {
        giaoDien().hienThiLoi(strLoi);
        return;
    }
    if (strMatKhauMoi == strMatKhauCu)
    {
        giaoDien().hienThiLoi("Mat khau moi phai khac mat khau hien tai.");
        return;
    }

    const std::string strXacNhan = nhapMatKhauAn("Nhap lai mat khau moi: ");
    if (strMatKhauMoi != strXacNhan)
    {
        giaoDien().hienThiLoi("Hai lan nhap mat khau moi khong khop.");
        return;
    }

    if (!xuLyFile().capNhatMatKhau(strUsername, strMatKhauMoi))
    {
        giaoDien().hienThiLoi("Khong the ghi mat khau moi vao file.");
        return;
    }
    giaoDien().hienThiThongBao("Doi mat khau thanh cong.");
}

bool Employee::doiMatKhauLanDau(const std::string& strUsername)
{
    std::cout << "Day la lan dang nhap dau tien, ban phai doi mat khau.\n"
              << thongBaoYeuCauMatKhau() << "\n";

    for (int iLanThu = 0; iLanThu < MAX_FIRST_CHANGE_ATTEMPTS; ++iLanThu)
    {
        const std::string strMatKhauMoi = nhapMatKhauAn("Mat khau moi: ");
        const std::string strLoi = layLoiMatKhauMoi(this->kiemTraMatKhauManh(strMatKhauMoi), strMatKhauMoi);
        if (!strLoi.empty())
        {
            giaoDien().hienThiLoi(strLoi);
            continue;
        }

        const std::string strXacNhan = nhapMatKhauAn("Nhap lai mat khau moi: ");
        if (strMatKhauMoi != strXacNhan)
        {
            giaoDien().hienThiLoi("Hai lan nhap mat khau moi khong khop.");
            continue;
        }

        if (!xuLyFile().capNhatMatKhau(strUsername, strMatKhauMoi))
        {
            giaoDien().hienThiLoi("Khong the ghi mat khau moi vao file.");
            return false;
        }
        giaoDien().hienThiThongBao("Doi mat khau thanh cong.");
        return true;
    }
    return false;
}

bool Employee::kiemTraMatKhauManh(const std::string& strMatKhau)
{
    if (strMatKhau.size() < static_cast<size_t>(MIN_PASSWORD_LENGTH))
    {
        return false;
    }

    bool bCoChuHoa = false;
    bool bCoChuThuong = false;
    bool bCoChuSo = false;
    bool bCoKyTuDacBiet = false;

    for (size_t iIndex = 0; iIndex < strMatKhau.size(); ++iIndex)
    {
        const unsigned char cKyTu = static_cast<unsigned char>(strMatKhau[iIndex]);
        if (std::isspace(cKyTu))
        {
            return false; // khoang trang co the lam hong dinh dang file
        }
        bCoChuHoa = bCoChuHoa || std::isupper(cKyTu);
        bCoChuThuong = bCoChuThuong || std::islower(cKyTu);
        bCoChuSo = bCoChuSo || std::isdigit(cKyTu);
        bCoKyTuDacBiet = bCoKyTuDacBiet || !std::isalnum(cKyTu);
    }
    return bCoChuHoa && bCoChuThuong && bCoChuSo && bCoKyTuDacBiet;
}