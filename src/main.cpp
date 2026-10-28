// main.cpp
// Muc dich: Diem bat dau chuong trinh; tao luong dang nhap chinh.

#include "../include/DangNhap.h"
#include <iostream>
using namespace std;
int main()
{
    // TODO: Khoi tao va chay luong dang nhap.
    DangNhap dangNhap;
    dangNhap.chayDangNhap();
    cout << "\nNhan Enter de thoat...";
    cin.get();
    return 0;
}
