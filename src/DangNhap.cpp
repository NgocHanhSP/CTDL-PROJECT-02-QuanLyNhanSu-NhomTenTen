// DangNhap.cpp
// Muc dich: Cai dat luong dang nhap, gioi han so lan sai va dieu huong theo vai tro.

#include "../include/DangNhap.h"
#include "../include/Admin.h"
#include "../include/Employee.h"
#include "../include/GiaoDien.h"
#include "../include/XuLyFile.h"

void DangNhap::chayDangNhap()
{
    // TODO: Not Implemented
    // Buoc 1: hien thi menu dang nhap.
    // Buoc 2: nhan lua chon Admin/Employee/Thoat.
    // Buoc 3: goi ham dang nhap tuong ung.
    // Buoc 4: neu thanh cong, chuyen den menu theo vai tro.
}

bool DangNhap::dangNhapAdmin(std::string& strUsername)
{
    // TODO: Not Implemented - nhap username/password va xac thuc vai tro ADMIN.
    (void)strUsername;
    return false;
}

bool DangNhap::dangNhapEmployee(std::string& strUsername)
{
    // TODO: Not Implemented
    // Gioi han so lan nhap sai theo MAX_LOGIN_ATTEMPTS.
    // Neu password hien tai bang DEFAULT_PASSWORD thi bat buoc doi password manh.
    // Chi vao menu Employee sau khi doi password thanh cong.
    (void)strUsername;
    return false;
}
