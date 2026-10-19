// TaiKhoan.cpp
// Muc dich: Cai dat constructor, getter va setter cua lop TaiKhoan.

#include "TaiKhoan.h"

TaiKhoan::TaiKhoan()
    : _strUsername(""), _strPassword("")
{
}

TaiKhoan::TaiKhoan(const std::string& strUsername,
                   const std::string& strPassword)
    : _strUsername(strUsername), _strPassword(strPassword)
{
}

std::string TaiKhoan::getUsername() const
{
    return this->_strUsername;
}

std::string TaiKhoan::getPassword() const
{
    return this->_strPassword;
}

void TaiKhoan::setUsername(const std::string& strUsername)
{
    this->_strUsername = strUsername;
}

void TaiKhoan::setPassword(const std::string& strPassword)
{
    this->_strPassword = strPassword;
}
