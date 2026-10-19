#pragma once

#include <string>

// Admin.h
// Muc dich: Khai bao cac chuc nang quan tri nhan vien.

class Admin
{
public:
    // Hien thi menu Admin va xu ly lua chon.
    void hienThiMenu(const std::string& strUsername);

private:
    // Them Employee moi; password ban dau theo yeu cau la 111111.
    void themEmployee();

    // Xoa tai khoan va ho so Employee.
    void xoaEmployee();

    // Tim Employee theo username.
    void timEmployee();

    // Cap nhat thong tin Employee.
    void capNhatEmployee();

    // Hien thi danh sach Employee.
    void hienThiTatCaEmployee();
};
