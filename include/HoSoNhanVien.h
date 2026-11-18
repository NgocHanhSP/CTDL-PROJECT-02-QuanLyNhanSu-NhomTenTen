#ifndef HOSONHANVIEN_H_INCLUDED_
#define HOSONHANVIEN_H_INCLUDED_

#include <iosfwd>
#include <string>

class HoSoNhanVien
{
public:
	HoSoNhanVien();
	HoSoNhanVien(const std::string& strHoTen, const std::string& strDiaChi, const std::string& strSoDienThoai, const std::string& strEmail);
	HoSoNhanVien(const HoSoNhanVien& hoSoNguon);
	~HoSoNhanVien();
	HoSoNhanVien& operator=(const HoSoNhanVien& hoSoNguon) = default;

	std::string getHoTen() const;
	std::string getDiaChi() const;
	std::string getSoDienThoai() const;
	std::string getEmail() const;
	void setHoTen(const std::string& strHoTen);
	void setDiaChi(const std::string& strDiaChi);
	void setSoDienThoai(const std::string& strSoDienThoai);
	void setEmail(const std::string& strEmail);

	friend std::istream& operator>>(std::istream& luongVao, HoSoNhanVien& hoSoNhanVien);
	friend std::ostream& operator<<(std::ostream& luongRa, const HoSoNhanVien& hoSoNhanVien);

private:
	std::string _strHoTen;
	std::string _strDiaChi;
	std::string _strSoDienThoai;
	std::string _strEmail;
};
#endif