#pragma once

#include <string>

// NhanVien.h
// Muc dich: Khai bao lop luu thong tin ho so nhan vien.

class NhanVien
{
private:
    std::string _strHoTen;
    std::string _strDiaChi;
    std::string _strSoDienThoai;
    std::string _strEmail;

public:
    // Khoi tao ho so rong.
    NhanVien();

    // Khoi tao ho so voi du lieu co san.
    NhanVien(const std::string& strHoTen,
             const std::string& strDiaChi,
             const std::string& strSoDienThoai,
             const std::string& strEmail);

    // Lay thong tin ho so.
    std::string getHoTen() const;
    std::string getDiaChi() const;
    std::string getSoDienThoai() const;
    std::string getEmail() const;

    // Cap nhat thong tin ho so.
    void setHoTen(const std::string& strHoTen);
    void setDiaChi(const std::string& strDiaChi);
    void setSoDienThoai(const std::string& strSoDienThoai);
    void setEmail(const std::string& strEmail);
};
