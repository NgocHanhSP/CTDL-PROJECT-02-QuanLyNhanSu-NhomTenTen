#pragma once

#include <string>
#include <vector>

#include "Constants.h"
#include "TaiKhoan.h"
#include "NhanVien.h"

// XuLyFile.h
// Muc dich: Khai bao cac thao tac doc/ghi file; cac module khac khong tu y sua file txt.
// Quy uoc de xuat: moi tai khoan chi co username va password tren cac dong theo format da thong nhat.

class XuLyFile
{
public:
    // Xac thuc username/password theo vai tro.
    bool kiemTraDangNhap(const std::string& strUsername,
                         const std::string& strPassword,
                         VaiTro eVaiTro);

    // Chi kiem tra username trong danh sach Employee.
    bool kiemTraUsernameTonTai(const std::string& strUsername);

    // Doc thong tin tai khoan tu file danh sach tuong ung.
    bool docTaiKhoan(const std::string& strUsername, TaiKhoan& taiKhoan);

    // Them/xoa tai khoan Employee.
    bool themTaiKhoan(const TaiKhoan& taiKhoan);
    bool xoaTaiKhoan(const std::string& strUsername);

    // Cap nhat password. Khong can co tham so trang thai doi mat khau.
    bool capNhatMatKhau(const std::string& strUsername,
                        const std::string& strMatKhauMoi);

    // Doc/ghi/cap nhat ho so theo username.
    bool docNhanVien(const std::string& strUsername, NhanVien& nhanVien);
    bool ghiNhanVien(const std::string& strUsername, const NhanVien& nhanVien);
    bool capNhatNhanVien(const std::string& strUsername, const NhanVien& nhanVien);

    // Lay danh sach username nhan vien.
    bool docDanhSachNhanVien(std::vector<std::string>& danhSachUsername);
};
