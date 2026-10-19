#pragma once

#include <string>

// Employee.h
// Muc dich: Khai bao menu va chuc nang cua nhan vien dang nhap.

class Employee
{
public:
    // Hien thi menu nhan vien; neu password mac dinh thi bat buoc doi truoc.
    void hienThiMenu(const std::string& strUsername);

private:
    // Xem ho so ca nhan.
    void xemThongTin(const std::string& strUsername);

    // Doi password thong thuong.
    void doiMatKhau(const std::string& strUsername);

    // Bat buoc doi password khi password hien tai van la DEFAULT_PASSWORD.
    // Tra ve true neu doi thanh cong; false neu huy/that bai.
    bool doiMatKhauLanDau(const std::string& strUsername);

    // Kiem tra mat khau manh theo quy tac trong Constants.h.
    bool kiemTraMatKhauManh(const std::string& strMatKhau);
};
