
 // GiaoDien.cpp
 // Muc dich: Cai dat phan hien thi console va nhap mat khau.

#include <iostream>
#include <string>
#include <../include/conio.h>
#include <../include/windows.h>
#include "../include/GiaoDien.h"

using namespace std;

// Hien thi menu dang nhap.
void GiaoDien::hienThiMenuDangNhap()
{
    system("cls");

    cout << "\n========================================\n";
    cout << "          DANG NHAP HE THONG            \n";
    cout << "========================================\n";
    cout << "1. Dang nhap Admin\n";
    cout << "2. Dang nhap Employee\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "========================================\n";
    cout << "Lua chon cua ban: ";
}

// Hien thi menu Admin.
void GiaoDien::hienThiMenuAdmin()
{
    cout << "\n========================================\n";
    cout << "               MENU ADMIN               \n";
    cout << "========================================\n";
    cout << "1. Them Employee\n";
    cout << "2. Xoa Employee\n";
    cout << "3. Tim Employee\n";
    cout << "4. Cap nhat Employee\n";
    cout << "5. Hien thi thong tin Employee\n";
    cout << "6. Dang xuat\n";
    cout << "========================================\n";
    cout << "Lua chon cua ban: ";
}

// Hien thi menu Employee.
void GiaoDien::hienThiMenuEmployee()
{
    cout << "\n========================================\n";
    cout << "             MENU EMPLOYEE              \n";
    cout << "========================================\n";
    cout << "1. Xem thong tin tai khoan\n";
    cout << "2. Doi password\n";
    cout << "3. Dang xuat\n";
    cout << "========================================\n";
    cout << "Lua chon cua ban: ";
}

// Hien thi thong bao thanh cong.
void GiaoDien::hienThiThongBao(const string& strThongBao)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Mau xanh la
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n[THONG BAO] " << strThongBao << endl;

    // Tra lai mau mac dinh
    SetConsoleTextAttribute(hConsole, 7);
}

// Hien thi thong bao loi.
void GiaoDien::hienThiLoi(const string& strThongBao)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Mau do
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n[LOI] " << strThongBao << endl;

    // Tra lai mau mac dinh
    SetConsoleTextAttribute(hConsole, 7);
}

// Nhap mat khau va hien thi dau *.
string GiaoDien::nhapMatKhau()
{
    string strMatKhau;
    int phim;

    while (true)
    {
        phim = _getch();

        // Enter: ket thuc nhap mat khau
        if (phim == 13)
        {
            cout << endl;
            break;
        }

        // Backspace: xoa ky tu cuoi
        else if (phim == 8)
        {
            if (!strMatKhau.empty())
            {
                strMatKhau.pop_back();
                cout << "\b \b";
            }
        }

        // Bo qua phim mui ten va phim dac biet
        else if (phim == 0 || phim == 224)
        {
            _getch();
        }

        // Nhan ky tu thong thuong
        else if (phim >= 32 && phim <= 126)
        {
            strMatKhau += static_cast<char>(phim);
            cout << '*';
        }
    }

    return strMatKhau;
}
