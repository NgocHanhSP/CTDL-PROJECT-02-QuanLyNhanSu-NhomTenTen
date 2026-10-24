// XuLyFile.cpp
// Muc dich: Noi duy nhat xu ly doc/ghi cac file du lieu.
// TODO: Thong nhat format dong trong Administrators.txt, Employees.txt va [username].txt
// truoc khi implement cac ham ben duoi.

#include "../include/XuLyFile.h"

bool XuLyFile::kiemTraDangNhap(const std::string& strUsername,
                               const std::string& strPassword,
                               VaiTro eVaiTro)
{
    // TODO: Not Implemented - doc file theo vai tro va so sanh thong tin.
    (void)strUsername;
    (void)strPassword;
    (void)eVaiTro;
    return false;
}

bool XuLyFile::kiemTraUsernameTonTai(const std::string& strUsername)
{
    // TODO: Not Implemented - chi tim trong Employees.txt.
    (void)strUsername;
    return false;
}

bool XuLyFile::docTaiKhoan(const std::string& strUsername, TaiKhoan& taiKhoan)
{
    // TODO: Not Implemented - nap username va password vao taiKhoan.
    (void)strUsername;
    (void)taiKhoan;
    return false;
}

bool XuLyFile::themTaiKhoan(const TaiKhoan& taiKhoan)
{
    // TODO: Not Implemented - them tai khoan vao Employees.txt.
    (void)taiKhoan;
    return false;
}

bool XuLyFile::xoaTaiKhoan(const std::string& strUsername)
{
    // TODO: Not Implemented - cap nhat Employees.txt va xu ly file ho so.
    (void)strUsername;
    return false;
}

bool XuLyFile::capNhatMatKhau(const std::string& strUsername,
                              const std::string& strMatKhauMoi)
{
    // TODO: Not Implemented - cap nhat password trong file dung.
    (void)strUsername;
    (void)strMatKhauMoi;
    return false;
}

bool XuLyFile::docNhanVien(const std::string& strUsername, NhanVien& nhanVien)
{
    // TODO: Not Implemented - doc 4 truong ho so tu data/[username].txt.
    (void)strUsername;
    (void)nhanVien;
    return false;
}

bool XuLyFile::ghiNhanVien(const std::string& strUsername, const NhanVien& nhanVien)
{
    // TODO: Not Implemented - tao/ghi moi file ho so.
    (void)strUsername;
    (void)nhanVien;
    return false;
}

bool XuLyFile::capNhatNhanVien(const std::string& strUsername, const NhanVien& nhanVien)
{
    // TODO: Not Implemented - cap nhat file ho so hien co.
    (void)strUsername;
    (void)nhanVien;
    return false;
}

bool XuLyFile::docDanhSachNhanVien(std::vector<std::string>& danhSachUsername)
{
    // TODO: Not Implemented - doc danh sach username tu Employees.txt.
    (void)danhSachUsername;
    return false;
}
