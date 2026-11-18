#ifndef ADMIN_H_INCLUDED_
#define ADMIN_H_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>
#include "NguoiDung.h"

class HoSoNhanVien;
class Admin : public NguoiDung
{
public:
	Admin(const GiaoDien& giaoDien, const XuLyFile& xuLyFile);
	virtual ~Admin();
	virtual void hienThiMenu(const std::string& strUsername) const override;
private:
	enum class LuaChon
	{
		THEM = 1,
		XOA = 2,
		TIM = 3,
		CAP_NHAT = 4,
		HIEN_THI = 5,
		THOAT = 6
	};

	enum class ThuocTinh
	{
		HO_TEN = 1,
		DIA_CHI = 2,
		SO_DIEN_THOAI = 3,
		EMAIL = 4
	};

	bool xuLyLuaChon(const int iLuaChon, const std::string& strUsername) const;

	void themEmployee() const;
	void xoaEmployee() const;
	void timEmployee() const;
	void capNhatEmployee() const;
	void hienThiTatCaEmployee() const;

	bool nhapUsernameMoi(const std::string& strLoiNhac, std::string& strUsername) const;
	bool nhapUsernameTonTai(const std::string& strLoiNhac, std::string& strUsername) const;
	bool nhapHoTen(const std::string& strLoiNhac, std::string& strHoTen) const;
	bool nhapDiaChi(const std::string& strLoiNhac, std::string& strDiaChi) const;
	bool nhapSoDienThoai(const std::string& strLoiNhac, const std::string& strUsernameBoQua, std::string& strSoDienThoai) const;
	bool nhapEmail(const std::string& strLoiNhac, const std::string& strUsernameBoQua, std::string& strEmail) const;

	void luuEmployeeMoi(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatThuocTinh(const ThuocTinh eThuocTinh, const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatHoTen(HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatDiaChi(HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatSoDienThoai(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatEmail(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const;

	std::vector<std::string> taoDongEmployee(const size_t uiSoThuTu, const std::string& strUsername) const;
};
#endif