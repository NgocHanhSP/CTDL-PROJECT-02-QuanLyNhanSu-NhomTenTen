// NhanVien.cpp
// Muc dich: Cai dat constructor, getter va setter cua lop NhanVien.

#include "NhanVien.h"

NhanVien::NhanVien()
    : _strHoTen(""), _strDiaChi(""), _strSoDienThoai(""), _strEmail("")
{
}

NhanVien::NhanVien(const std::string& strHoTen,
                   const std::string& strDiaChi,
                   const std::string& strSoDienThoai,
                   const std::string& strEmail)
    : _strHoTen(strHoTen),
      _strDiaChi(strDiaChi),
      _strSoDienThoai(strSoDienThoai),
      _strEmail(strEmail)
{
}

std::string NhanVien::getHoTen() const
{
    return this->_strHoTen;
}

std::string NhanVien::getDiaChi() const
{
    return this->_strDiaChi;
}

std::string NhanVien::getSoDienThoai() const
{
    return this->_strSoDienThoai;
}

std::string NhanVien::getEmail() const
{
    return this->_strEmail;
}

void NhanVien::setHoTen(const std::string& strHoTen)
{
    this->_strHoTen = strHoTen;
}

void NhanVien::setDiaChi(const std::string& strDiaChi)
{
    this->_strDiaChi = strDiaChi;
}

void NhanVien::setSoDienThoai(const std::string& strSoDienThoai)
{
    this->_strSoDienThoai = strSoDienThoai;
}

void NhanVien::setEmail(const std::string& strEmail)
{
    this->_strEmail = strEmail;
}
