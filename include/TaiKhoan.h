#ifndef TAIKHOAN_H_INCLUDED_
#define TAIKHOAN_H_INCLUDED_

#include <iosfwd>
#include <string>

class TaiKhoan
{
public:
	TaiKhoan();
	TaiKhoan(const std::string& strUsername, const std::string& strPassword);
	TaiKhoan(const TaiKhoan& taiKhoanNguon);
	~TaiKhoan();
	TaiKhoan& operator=(const TaiKhoan& taiKhoanNguon) = default;

	std::string getUsername() const;
	std::string getPassword() const;
	void setUsername(const std::string& strUsername);
	void setPassword(const std::string& strPassword);

	friend std::istream& operator>>(std::istream& luongVao, TaiKhoan& taiKhoan);
	friend std::ostream& operator<<(std::ostream& luongRa, const TaiKhoan& taiKhoan);

private:
	std::string _strUsername;
	std::string _strPassword;
};
#endif