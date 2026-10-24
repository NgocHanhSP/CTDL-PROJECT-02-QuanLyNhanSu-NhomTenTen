
 // DangNhap.cpp
 // Muc dich: Cai dat luong dang nhap, gioi han so lan sai va dieu huong theo vai tro.

#include "../include/DangNhap.h"
#include "../include/Admin.h"
#include "../include/Employee.h"
#include "../include/GiaoDien.h"
#include "../include/XuLyFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>

namespace
{
    const std::string TEN_FILE_ADMIN = "Administrators.txt";
    const std::string TEN_FILE_EMPLOYEE = "Employees.txt";

    // Dat ten rieng de tranh trung ten voi cac file khac.
    const int DANGNHAP_MAX_LOGIN_ATTEMPTS = 3;
    const std::string DANGNHAP_DEFAULT_PASSWORD = "111111";

    struct DangNhapTaiKhoan
    {
        std::string username;
        std::string password;
    };

    // Doc danh sach tai khoan tu file.
    // Moi dong co dang: username password
    std::vector<DangNhapTaiKhoan> docTaiKhoan(
        const std::string& tenFile)
    {
        std::vector<DangNhapTaiKhoan> danhSach;
        std::ifstream file(tenFile);

        if (!file.is_open())
            return danhSach;

        std::string dong;

        while (std::getline(file, dong))
        {
            if (dong.empty())
                continue;

            // Ho tro dau phan cach ; va ,
            for (char& kyTu : dong)
            {
                if (kyTu == ';' || kyTu == ',')
                    kyTu = ' ';
            }

            std::istringstream iss(dong);
            DangNhapTaiKhoan tk;

            if (iss >> tk.username >> tk.password)
                danhSach.push_back(tk);
        }

        file.close();
        return danhSach;
    }

    // Kiem tra username va password.
    bool kiemTraTaiKhoan(
        const std::string& tenFile,
        const std::string& username,
        const std::string& password)
    {
        std::vector<DangNhapTaiKhoan> danhSach =
            docTaiKhoan(tenFile);

        for (const DangNhapTaiKhoan& tk : danhSach)
        {
            if (tk.username == username &&
                tk.password == password)
            {
                return true;
            }
        }

        return false;
    }

    // Lay mat khau hien tai cua nhan vien.
    bool layMatKhauNhanVien(
        const std::string& username,
        std::string& password)
    {
        std::vector<DangNhapTaiKhoan> danhSach =
            docTaiKhoan(TEN_FILE_EMPLOYEE);

        for (const DangNhapTaiKhoan& tk : danhSach)
        {
            if (tk.username == username)
            {
                password = tk.password;
                return true;
            }
        }

        return false;
    }

    // Cap nhat mat khau vao Employees.txt.
    bool capNhatMatKhauNhanVien(
        const std::string& username,
        const std::string& matKhauMoi)
    {
        std::vector<DangNhapTaiKhoan> danhSach =
            docTaiKhoan(TEN_FILE_EMPLOYEE);

        bool timThay = false;

        for (DangNhapTaiKhoan& tk : danhSach)
        {
            if (tk.username == username)
            {
                tk.password = matKhauMoi;
                timThay = true;
                break;
            }
        }

        if (!timThay)
            return false;

        std::ofstream file(
            TEN_FILE_EMPLOYEE, std::ios::trunc);

        if (!file.is_open())
            return false;

        for (const DangNhapTaiKhoan& tk : danhSach)
        {
            file << tk.username << ' '
                 << tk.password << '\n';
        }

        file.close();
        return !file.fail();
    }

    // Kiem tra mat khau co chu cai va chu so.
    bool matKhauManh(const std::string& password)
    {
        if (password.length() < 8)
            return false;

        bool coChu = false;
        bool coSo = false;

        for (unsigned char kyTu : password)
        {
            if (std::isalpha(kyTu))
                coChu = true;

            if (std::isdigit(kyTu))
                coSo = true;
        }

        return coChu && coSo;
    }

    // Xu ly doi mat khau cho nhan vien.
    bool doiMatKhauNhanVien(
        const std::string& username,
        const std::string& matKhauCu,
        GiaoDien& giaoDien)
    {
        std::string matKhauXacNhan;
        std::string matKhauMoi;
        std::string nhapLai;

        std::cout << "Nhap lai mat khau hien tai: ";
        matKhauXacNhan = giaoDien.nhapMatKhau();

        if (matKhauXacNhan != matKhauCu)
        {
            giaoDien.hienThiLoi(
                "Mat khau hien tai khong dung.");
            return false;
        }

        while (true)
        {
            std::cout << "Nhap mat khau moi: ";
            matKhauMoi = giaoDien.nhapMatKhau();

            if (!matKhauManh(matKhauMoi))
            {
                giaoDien.hienThiLoi(
                    "Mat khau phai co it nhat 8 ky tu, "
                    "bao gom chu cai va chu so.");
                continue;
            }

            std::cout << "Nhap lai mat khau moi: ";
            nhapLai = giaoDien.nhapMatKhau();

            if (matKhauMoi != nhapLai)
            {
                giaoDien.hienThiLoi(
                    "Hai mat khau khong trung khop.");
                continue;
            }

            break;
        }

        if (!capNhatMatKhauNhanVien(
                username, matKhauMoi))
        {
            giaoDien.hienThiLoi(
                "Khong the cap nhat Employees.txt.");
            return false;
        }

        giaoDien.hienThiThongBao(
            "Doi mat khau thanh cong.");

        return true;
    }

    // Hien thi thong tin tu file username.txt.
    void xemThongTinNhanVien(
        const std::string& username,
        GiaoDien& giaoDien)
    {
        std::ifstream file(username + ".txt");

        if (!file.is_open())
        {
            giaoDien.hienThiLoi(
                "Khong tim thay file thong tin nhan vien.");
            return;
        }

        const char* tenTruong[] =
        {
            "Ho ten: ",
            "Dia chi: ",
            "So dien thoai: ",
            "Email: "
        };

        std::string dong;
        int viTri = 0;

        std::cout << "\n===== THONG TIN NHAN VIEN =====\n";

        while (std::getline(file, dong))
        {
            if (viTri < 4)
                std::cout << tenTruong[viTri];

            std::cout << dong << '\n';
            ++viTri;
        }

        std::cout << "===============================\n";
        file.close();
    }
}

// =====================================================
// HAM CHAY LUONG DANG NHAP CHINH
// =====================================================
void DangNhap::chayDangNhap()
{
    GiaoDien giaoDien;
    int luaChon;

    do
    {
        giaoDien.hienThiMenuDangNhap();

        if (!(std::cin >> luaChon))
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            giaoDien.hienThiLoi(
                "Vui long nhap lua chon bang so.");
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        std::string strUsername;

        switch (luaChon)
        {
        case 1:
            if (dangNhapAdmin(strUsername))
            {
                int chonAdmin;

                do
                {
                    giaoDien.hienThiMenuAdmin();

                    if (!(std::cin >> chonAdmin))
                    {
                        std::cin.clear();
                        std::cin.ignore(
                            std::numeric_limits<std::streamsize>::max(),
                            '\n');

                        giaoDien.hienThiLoi(
                            "Lua chon khong hop le.");
                        continue;
                    }

                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(),
                        '\n');

                    switch (chonAdmin)
                    {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                        giaoDien.hienThiThongBao(
                            "Chuc nang nay can ket noi voi "
                            "cac ham quan ly trong Admin.cpp.");
                        break;

                    case 6:
                        giaoDien.hienThiThongBao(
                            "Dang xuat Admin thanh cong.");
                        break;

                    default:
                        giaoDien.hienThiLoi(
                            "Lua chon khong hop le.");
                    }

                } while (chonAdmin != 6);
            }
            break;

        case 2:
            if (dangNhapEmployee(strUsername))
            {
                int chonEmployee;

                do
                {
                    giaoDien.hienThiMenuEmployee();

                    if (!(std::cin >> chonEmployee))
                    {
                        std::cin.clear();
                        std::cin.ignore(
                            std::numeric_limits<std::streamsize>::max(),
                            '\n');

                        giaoDien.hienThiLoi(
                            "Lua chon khong hop le.");
                        continue;
                    }

                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(),
                        '\n');

                    switch (chonEmployee)
                    {
                    case 1:
                        xemThongTinNhanVien(
                            strUsername, giaoDien);
                        break;

                    case 2:
                    {
                        std::string matKhauHienTai;

                        if (layMatKhauNhanVien(
                                strUsername, matKhauHienTai))
                        {
                            doiMatKhauNhanVien(
                                strUsername,
                                matKhauHienTai,
                                giaoDien);
                        }
                        else
                        {
                            giaoDien.hienThiLoi(
                                "Khong doc duoc tai khoan.");
                        }
                        break;
                    }

                    case 3:
                        giaoDien.hienThiThongBao(
                            "Dang xuat Employee thanh cong.");
                        break;

                    default:
                        giaoDien.hienThiLoi(
                            "Lua chon khong hop le.");
                    }

                } while (chonEmployee != 3);
            }
            break;

        case 0:
            giaoDien.hienThiThongBao(
                "Ket thuc chuong trinh.");
            break;

        default:
            giaoDien.hienThiLoi(
                "Lua chon khong hop le.");
        }

    } while (luaChon != 0);
}

// =====================================================
// DANG NHAP ADMIN
// =====================================================
bool DangNhap::dangNhapAdmin(std::string& strUsername)
{
    GiaoDien giaoDien;
    std::string strPassword;

    std::cout << "\n========== DANG NHAP ADMIN ==========\n";
    std::cout << "Username: ";
    std::getline(std::cin, strUsername);

    std::cout << "Password: ";
    strPassword = giaoDien.nhapMatKhau();

    if (kiemTraTaiKhoan(
            TEN_FILE_ADMIN, strUsername, strPassword))
    {
        giaoDien.hienThiThongBao(
            "Dang nhap Admin thanh cong.");
        return true;
    }

    giaoDien.hienThiLoi(
        "Sai username hoac password Admin.");

    return false;
}

// =====================================================
// DANG NHAP EMPLOYEE
// =====================================================
bool DangNhap::dangNhapEmployee(std::string& strUsername)
{
    GiaoDien giaoDien;
    std::string strPassword;

    std::cout << "\n======== DANG NHAP EMPLOYEE ========\n";
    std::cout << "Username: ";
    std::getline(std::cin, strUsername);

    for (int lan = 1;
         lan <= DANGNHAP_MAX_LOGIN_ATTEMPTS;
         ++lan)
    {
        std::cout << "Password: ";
        strPassword = giaoDien.nhapMatKhau();

        if (kiemTraTaiKhoan(
                TEN_FILE_EMPLOYEE,
                strUsername,
                strPassword))
        {
            giaoDien.hienThiThongBao(
                "Dang nhap Employee thanh cong.");

            // Bat buoc doi mat khau mac dinh.
            if (strPassword == DANGNHAP_DEFAULT_PASSWORD)
            {
                giaoDien.hienThiThongBao(
                    "Ban dang su dung mat khau mac dinh. "
                    "Vui long doi mat khau.");

                if (!doiMatKhauNhanVien(
                        strUsername,
                        DANGNHAP_DEFAULT_PASSWORD,
                        giaoDien))
                {
                    giaoDien.hienThiLoi(
                        "Doi mat khau that bai. "
                        "Khong the vao menu Employee.");
                    return false;
                }
            }

            return true;
        }

        giaoDien.hienThiLoi(
            "Sai username hoac password. Lan " +
            std::to_string(lan) + "/" +
            std::to_string(DANGNHAP_MAX_LOGIN_ATTEMPTS));

        if (lan == DANGNHAP_MAX_LOGIN_ATTEMPTS)
        {
            giaoDien.hienThiLoi(
                "Ban da nhap sai 3 lan. "
                "Khong the tiep tuc dang nhap.");
            return false;
        }
    }

    return false;
}
