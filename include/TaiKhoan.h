#pragma once

#include <string>

// TaiKhoan.h
// Muc dich: Khai bao lop luu username va password.
// Quy uoc lan dang nhap dau: password == DEFAULT_PASSWORD.
// Khong can luu them co MustChangePassword vi co the suy ra tu password.

class TaiKhoan
{
private:
    std::string _strUsername;
    std::string _strPassword;

public:
    // Khoi tao tai khoan rong.
    TaiKhoan();

    // Khoi tao tai khoan tu username va password.
    TaiKhoan(const std::string& strUsername,
             const std::string& strPassword);

    // Lay thong tin tai khoan.
    std::string getUsername() const;
    std::string getPassword() const;

    // Cap nhat thong tin tai khoan.
    void setUsername(const std::string& strUsername);
    void setPassword(const std::string& strPassword);
};
