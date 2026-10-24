
#pragma once

#include <string>

// GiaoDien.h
// Muc dich: Khai bao cac ham hien thi menu, thong bao va nhap mat khau an ky tu.

class GiaoDien
{
public:
    // Hien thi cac menu theo vai tro.
    void hienThiMenuDangNhap();

    void hienThiMenuAdmin();

    void hienThiMenuEmployee();

    // Hien thi thong bao ket qua va thong bao loi.
    void hienThiThongBao(const std::string& strThongBao);

    void hienThiLoi(const std::string& strThongBao);

    // Nhap password, hien thi dau * thay cho ky tu that.
    std::string nhapMatKhau();
};
