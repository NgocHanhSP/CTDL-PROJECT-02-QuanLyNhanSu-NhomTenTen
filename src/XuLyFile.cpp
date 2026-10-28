// XuLyFile.cpp
// Muc dich: Noi duy nhat xu ly doc/ghi cac file du lieu.
// TODO: Thong nhat format dong trong Administrators.txt, Employees.txt va [username].txt
// truoc khi implement cac ham ben duoi.

#include "../include/XuLyFile.h"

#include <cstdio>
#include <fstream>

bool XuLyFile::kiemTraDangNhap(const std::string& strUsername,
                               const std::string& strPassword,
                               VaiTro eVaiTro)
{
    /*TODO: Not Implemented includ- doc file theo vai tro va so sanh thong tin.
    (void)strUsername;
    (void)strPassword;
    (void)eVaiTro;
    return false;*/

    // Doc file theo vai tro va so sanh thong tin.
    std::string strDuongDan = (eVaiTro == VaiTro::ADMIN) ? ADMIN_FILE_PATH : EMPLOYEE_FILE_PATH;
    std::ifstream fileDoc(strDuongDan);
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::string strUserDoc = "";
    std::string strPassDoc = "";
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        if (strUserDoc == strUsername && strPassDoc == strPassword)
        {
            return true;
        }
    }
    return false;
}

bool XuLyFile::kiemTraUsernameTonTai(const std::string& strUsername)
{
    /*TODO: Not Implemented - chi tim trong Employees.txt.
    (void)strUsername;
    return false;*/

    // Chi tim trong Employees.txt.
    std::ifstream fileDoc(EMPLOYEE_FILE_PATH);
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::string strUserDoc = "";
    std::string strPassDoc = "";
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        if (strUserDoc == strUsername)
        {
            return true;
        }
    }
    return false;
}

bool XuLyFile::docTaiKhoan(const std::string& strUsername, TaiKhoan& taiKhoan)
{
    /*TODO: Not Implemented - nap username va password vao taiKhoan.
    (void)strUsername;
    (void)taiKhoan;
    return false;*/

    // Nap username va password vao taiKhoan.
    std::ifstream fileDoc(EMPLOYEE_FILE_PATH);
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::string strUserDoc = "";
    std::string strPassDoc = "";
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        if (strUserDoc == strUsername)
        {
            taiKhoan.setUsername(strUserDoc);
            taiKhoan.setPassword(strPassDoc);
            return true;
        }
    }
    return false;
}

bool XuLyFile::themTaiKhoan(const TaiKhoan& taiKhoan)
{
    /**TODO: Not Implemented - them tai khoan vao Employees.txt.
    (void)taiKhoan;
    return false;**/

    // Them tai khoan vao Employees.txt (tu choi neu trung username).
    if (kiemTraUsernameTonTai(taiKhoan.getUsername()))
    {
        return false;
    }

    std::ofstream fileGhi(EMPLOYEE_FILE_PATH, std::ios::app);
    if (!fileGhi.is_open())
    {
        return false;
    }
    fileGhi << taiKhoan.getUsername() << " " << taiKhoan.getPassword() << "\n";
    return true;
}

bool XuLyFile::xoaTaiKhoan(const std::string& strUsername)
{
    /**TODO: Not Implemented - cap nhat Employees.txt va xu ly file ho so.
    (void)strUsername;
    return false;**/

    // Cap nhat Employees.txt va xoa file ho so.
    std::ifstream fileDoc(EMPLOYEE_FILE_PATH);
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::vector<TaiKhoan> danhSachTaiKhoan;
    std::string strUserDoc = "";
    std::string strPassDoc = "";
    bool bTimThay = false;
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        if (strUserDoc == strUsername)
        {
            bTimThay = true;
        }
        else
        {
            danhSachTaiKhoan.push_back(TaiKhoan(strUserDoc, strPassDoc));
        }
    }
    fileDoc.close();

    if (!bTimThay)
    {
        return false;
    }

    std::ofstream fileGhi(EMPLOYEE_FILE_PATH, std::ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }
    for (const TaiKhoan& taiKhoanHienTai : danhSachTaiKhoan)
    {
        fileGhi << taiKhoanHienTai.getUsername() << " "
                << taiKhoanHienTai.getPassword() << "\n";
    }
    fileGhi.close();

    std::remove((DATA_DIRECTORY + strUsername + ".txt").c_str());
    return true;
}

bool XuLyFile::capNhatMatKhau(const std::string& strUsername,
                              const std::string& strMatKhauMoi)
{
    /*TODO: Not Implemented - cap nhat password trong file dung.
    (void)strUsername;
    (void)strMatKhauMoi;
    return false;*/
    // Cap nhat password trong Employees.txt.
    std::ifstream fileDoc(EMPLOYEE_FILE_PATH);
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::vector<TaiKhoan> danhSachTaiKhoan;
    std::string strUserDoc = "";
    std::string strPassDoc = "";
    bool bTimThay = false;
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        if (strUserDoc == strUsername)
        {
            strPassDoc = strMatKhauMoi;
            bTimThay = true;
        }
        danhSachTaiKhoan.push_back(TaiKhoan(strUserDoc, strPassDoc));
    }
    fileDoc.close();

    if (!bTimThay)
    {
        return false;
    }

    std::ofstream fileGhi(EMPLOYEE_FILE_PATH, std::ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }
    for (const TaiKhoan& taiKhoanHienTai : danhSachTaiKhoan)
    {
        fileGhi << taiKhoanHienTai.getUsername() << " "
                << taiKhoanHienTai.getPassword() << "\n";
    }
    return true;
}

bool XuLyFile::docNhanVien(const std::string& strUsername, NhanVien& nhanVien)
{
    /*TODO: Not Implemented - doc 4 truong ho so tu data/[username].txt.
    (void)strUsername;
    (void)nhanVien;
    return false;*/
     // Doc 4 truong ho so tu data/[username].txt.
    std::ifstream fileDoc(DATA_DIRECTORY + strUsername + ".txt");
    if (!fileDoc.is_open())
    {
        return false;
    }

    std::string strHoTen = "";
    std::string strDiaChi = "";
    std::string strSoDienThoai = "";
    std::string strEmail = "";
    if (!std::getline(fileDoc, strHoTen) ||
        !std::getline(fileDoc, strDiaChi) ||
        !std::getline(fileDoc, strSoDienThoai) ||
        !std::getline(fileDoc, strEmail))
    {
        return false;
    }

    nhanVien.setHoTen(strHoTen);
    nhanVien.setDiaChi(strDiaChi);
    nhanVien.setSoDienThoai(strSoDienThoai);
    nhanVien.setEmail(strEmail);
    return true;
}

bool XuLyFile::ghiNhanVien(const std::string& strUsername, const NhanVien& nhanVien)
{
    /*TODO: Not Implemented - tao/ghi moi file ho so.
    (void)strUsername;
    (void)nhanVien;
    return false;*/
    // Tao/ghi moi file ho so (moi thong tin mot dong).
    std::ofstream fileGhi(DATA_DIRECTORY + strUsername + ".txt", std::ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }

    fileGhi << nhanVien.getHoTen() << "\n"
            << nhanVien.getDiaChi() << "\n"
            << nhanVien.getSoDienThoai() << "\n"
            << nhanVien.getEmail() << "\n";
    return true;
}

bool XuLyFile::capNhatNhanVien(const std::string& strUsername, const NhanVien& nhanVien)
{
    /*TODO: Not Implemented - cap nhat file ho so hien co.
    (void)strUsername;
    (void)nhanVien;
    return false;*/
    // Cap nhat file ho so hien co (khong tao moi neu chua co file).
    std::ifstream fileKiemTra(DATA_DIRECTORY + strUsername + ".txt");
    if (!fileKiemTra.is_open())
    {
        return false;
    }
    fileKiemTra.close();

    return ghiNhanVien(strUsername, nhanVien);
}

bool XuLyFile::docDanhSachNhanVien(std::vector<std::string>& danhSachUsername)
{
    /*TODO: Not Implemented - doc danh sach username tu Employees.txt.
    (void)danhSachUsername;
    return false;*/
     // Doc danh sach username tu Employees.txt.
    std::ifstream fileDoc(EMPLOYEE_FILE_PATH);
    if (!fileDoc.is_open())
    {
        return false;
    }

    danhSachUsername.clear();
    std::string strUserDoc = "";
    std::string strPassDoc = "";
    while (fileDoc >> strUserDoc >> strPassDoc)
    {
        danhSachUsername.push_back(strUserDoc);
    }
    return true;
}
