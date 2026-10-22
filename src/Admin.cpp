// Admin.cpp
// Muc dich: Cai dat cac chuc nang quan tri nhan vien.

#include "../include/Admin.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <vector>

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

    // Cac lua chon trong menu Admin.
    const int MENU_THEM = 1;
    const int MENU_XOA = 2;
    const int MENU_TIM = 3;
    const int MENU_CAP_NHAT = 4;
    const int MENU_HIEN_THI = 5;
    const int MENU_THOAT = 6;
    const int LUA_CHON_KHONG_HOP_LE = 0;

    // Cac lua chon thuoc tinh khi cap nhat ho so.
    const int THUOC_TINH_HO_TEN = 1;
    const int THUOC_TINH_DIA_CHI = 2;
    const int THUOC_TINH_SO_DIEN_THOAI = 3;
    const int THUOC_TINH_EMAIL = 4;

    // Do rong cac cot khi hien thi danh sach.
    const int WIDTH_USERNAME = 14;
    const int WIDTH_HO_TEN = 26;
    const int WIDTH_DIA_CHI = 32;
    const int WIDTH_SO_DIEN_THOAI = 14;
    const int WIDTH_EMAIL = 28;

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

    // Username la ten file ho so nen chi cho phep chu, so va dau gach duoi.
    bool hopLeUsername(const std::string& strUsername)
    {
        if (strUsername.empty())
        {
            return false;
        }
        for (size_t iIndex = 0; iIndex < strUsername.size(); ++iIndex)
        {
            const unsigned char cKyTu = static_cast<unsigned char>(strUsername[iIndex]);
            if (!std::isalnum(cKyTu) && cKyTu != '_')
            {
                return false;
            }
        }
        return true;
    }

    // In ho so cua mot Employee ra man hinh.
    void inHoSo(const std::string& strUsername, const NhanVien& nhanVien)
    {
        std::cout << "Username      : " << strUsername << "\n"
                  << "Ho ten        : " << nhanVien.getHoTen() << "\n"
                  << "Dia chi       : " << nhanVien.getDiaChi() << "\n"
                  << "So dien thoai : " << nhanVien.getSoDienThoai() << "\n"
                  << "Email         : " << nhanVien.getEmail() << "\n";
    }
}

void Admin::hienThiMenu(const std::string& strUsername)
{
    (void)strUsername;

    bool bTiepTuc = true;
    while (bTiepTuc)
    {
        giaoDien().hienThiMenuAdmin();
        const int iLuaChon = nhapLuaChon();

        switch (iLuaChon)
        {
        case MENU_THEM:
            this->themEmployee();
            tamDung();
            break;
        case MENU_XOA:
            this->xoaEmployee();
            tamDung();
            break;
        case MENU_TIM:
            this->timEmployee();
            tamDung();
            break;
        case MENU_CAP_NHAT:
            this->capNhatEmployee();
            tamDung();
            break;
        case MENU_HIEN_THI:
            this->hienThiTatCaEmployee();
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

void Admin::themEmployee()
{
    const std::string strUsername = nhapChuoi("Username: ");
    if (!hopLeUsername(strUsername))
    {
        giaoDien().hienThiLoi("Username khong hop le (chi gom chu, so va dau _).");
        return;
    }
    if (xuLyFile().kiemTraUsernameTonTai(strUsername))
    {
        giaoDien().hienThiLoi("Username da ton tai, khong the them.");
        return;
    }

    const std::string strHoTen = nhapChuoi("Ho ten: ");
    const std::string strDiaChi = nhapChuoi("Dia chi: ");
    const std::string strSoDienThoai = nhapChuoi("So dien thoai: ");
    const std::string strEmail = nhapChuoi("Email: ");
    if (strHoTen.empty() || strDiaChi.empty() || strSoDienThoai.empty() || strEmail.empty())
    {
        giaoDien().hienThiLoi("Thong tin khong duoc de trong.");
        return;
    }

    const TaiKhoan taiKhoan(strUsername, DEFAULT_PASSWORD);
    if (!xuLyFile().themTaiKhoan(taiKhoan))
    {
        giaoDien().hienThiLoi("Khong the ghi tai khoan vao file.");
        return;
    }

    const NhanVien nhanVien(strHoTen, strDiaChi, strSoDienThoai, strEmail);
    if (!xuLyFile().ghiNhanVien(strUsername, nhanVien))
    {
        // Hoan tac de tranh co tai khoan nhung khong co ho so.
        xuLyFile().xoaTaiKhoan(strUsername);
        giaoDien().hienThiLoi("Khong the tao file ho so nhan vien.");
        return;
    }
    giaoDien().hienThiThongBao(std::string("Them employee thanh cong. Mat khau mac dinh la ") + DEFAULT_PASSWORD + ".");
}

void Admin::xoaEmployee()
{
    const std::string strUsername = nhapChuoi("Username can xoa: ");
    if (!xuLyFile().kiemTraUsernameTonTai(strUsername))
    {
        giaoDien().hienThiLoi("Username khong ton tai.");
        return;
    }
    if (!xuLyFile().xoaTaiKhoan(strUsername))
    {
        giaoDien().hienThiLoi("Khong the xoa employee.");
        return;
    }
    giaoDien().hienThiThongBao("Da xoa employee " + strUsername + ".");
}

void Admin::timEmployee()
{
    const std::string strUsername = nhapChuoi("Username can tim: ");
    if (!xuLyFile().kiemTraUsernameTonTai(strUsername))
    {
        giaoDien().hienThiLoi("Khong tim thay employee.");
        return;
    }

    NhanVien nhanVien;
    if (!xuLyFile().docNhanVien(strUsername, nhanVien))
    {
        giaoDien().hienThiLoi("Khong doc duoc ho so employee.");
        return;
    }
    inHoSo(strUsername, nhanVien);
}

void Admin::capNhatEmployee()
{
    const std::string strUsername = nhapChuoi("Username can cap nhat: ");
    if (!xuLyFile().kiemTraUsernameTonTai(strUsername))
    {
        giaoDien().hienThiLoi("Username khong ton tai.");
        return;
    }

    NhanVien nhanVien;
    if (!xuLyFile().docNhanVien(strUsername, nhanVien))
    {
        giaoDien().hienThiLoi("Khong doc duoc ho so employee.");
        return;
    }
    inHoSo(strUsername, nhanVien);

    std::cout << "\nChon thuoc tinh can cap nhat:\n"
              << THUOC_TINH_HO_TEN << ". Ho ten\n"
              << THUOC_TINH_DIA_CHI << ". Dia chi\n"
              << THUOC_TINH_SO_DIEN_THOAI << ". So dien thoai\n"
              << THUOC_TINH_EMAIL << ". Email\n";
    const int iThuocTinh = nhapLuaChon();

    // Chon thuoc tinh truoc, nhap gia tri moi sau.
    if (iThuocTinh < THUOC_TINH_HO_TEN || iThuocTinh > THUOC_TINH_EMAIL)
    {
        giaoDien().hienThiLoi("Thuoc tinh khong hop le.");
        return;
    }
    const std::string strGiaTriMoi = nhapChuoi("Gia tri moi: ");
    if (strGiaTriMoi.empty())
    {
        giaoDien().hienThiLoi("Gia tri moi khong duoc de trong.");
        return;
    }

    switch (iThuocTinh)
    {
    case THUOC_TINH_HO_TEN:
        nhanVien.setHoTen(strGiaTriMoi);
        break;
    case THUOC_TINH_DIA_CHI:
        nhanVien.setDiaChi(strGiaTriMoi);
        break;
    case THUOC_TINH_SO_DIEN_THOAI:
        nhanVien.setSoDienThoai(strGiaTriMoi);
        break;
    case THUOC_TINH_EMAIL:
        nhanVien.setEmail(strGiaTriMoi);
        break;
    default:
        break;
    }

    if (!xuLyFile().capNhatNhanVien(strUsername, nhanVien))
    {
        giaoDien().hienThiLoi("Khong the ghi cap nhat ho so.");
        return;
    }
    giaoDien().hienThiThongBao("Cap nhat thanh cong.");
}

void Admin::hienThiTatCaEmployee()
{
    std::vector<std::string> danhSachUsername;
    if (!xuLyFile().docDanhSachNhanVien(danhSachUsername))
    {
        giaoDien().hienThiLoi("Khong doc duoc danh sach employee.");
        return;
    }
    if (danhSachUsername.empty())
    {
        giaoDien().hienThiLoi("Chua co employee nao.");
        return;
    }

    std::cout << std::left
              << std::setw(WIDTH_USERNAME) << "Username"
              << std::setw(WIDTH_HO_TEN) << "Ho ten"
              << std::setw(WIDTH_DIA_CHI) << "Dia chi"
              << std::setw(WIDTH_SO_DIEN_THOAI) << "So dien thoai"
              << std::setw(WIDTH_EMAIL) << "Email" << "\n";

    for (size_t iIndex = 0; iIndex < danhSachUsername.size(); ++iIndex)
    {
        NhanVien nhanVien;
        if (!xuLyFile().docNhanVien(danhSachUsername[iIndex], nhanVien))
        {
            giaoDien().hienThiLoi("Khong doc duoc ho so cua " + danhSachUsername[iIndex] + ".");
            continue;
        }
        std::cout << std::left
                  << std::setw(WIDTH_USERNAME) << danhSachUsername[iIndex]
                  << std::setw(WIDTH_HO_TEN) << nhanVien.getHoTen()
                  << std::setw(WIDTH_DIA_CHI) << nhanVien.getDiaChi()
                  << std::setw(WIDTH_SO_DIEN_THOAI) << nhanVien.getSoDienThoai()
                  << std::setw(WIDTH_EMAIL) << nhanVien.getEmail() << "\n";
    }
}
