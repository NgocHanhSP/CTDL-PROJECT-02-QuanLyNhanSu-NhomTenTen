
#pragma once

#include <string>

// DangNhap.h
// Muc dich: Dieu phoi dang nhap, xac thuc vai tro va chuyen den menu phu hop.

class DangNhap
{
public:
    // Chay luong dang nhap chinh.
    void chayDangNhap();

private:
    // Dang nhap Admin va tra ve username neu thanh cong.
    bool dangNhapAdmin(std::string& strUsername);

    // Dang nhap Employee; can kiem tra so lan nhap sai va password mac dinh.
    bool dangNhapEmployee(std::string& strUsername);
};
