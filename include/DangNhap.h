#ifndef DANGNHAP_H_INCLUDED_
#define DANGNHAP_H_INCLUDED_

#include <string>
#include "GiaoDien.h"
#include "XuLyFile.h"

class NguoiDung;
class DangNhap
{
public:
	void chayDangNhap();

private:
	enum class LuaChon
	{
		ADMIN = 1,
		EMPLOYEE = 2,
		QUEN_PASSWORD = 3,
		THOAT = 4
	};

	bool xuLyLuaChon(const int iLuaChon) const;
	void xuLyDangNhapAdmin() const;
	bool xuLyDangNhapEmployee() const;
	void chayAdmin(const std::string& strUsername) const;
	void chayEmployee(const std::string& strUsername) const;
	void chayNguoiDung(const NguoiDung& nguoiDung, const std::string& strUsername) const;

	bool dangNhapAdmin(std::string& strUsername) const;
	bool dangNhapEmployee(std::string& strUsername) const;
	void nhapThongTinDangNhap(const std::string& strNhanMatKhau, std::string& strUsername, std::string& strPassword) const;

	void quenPassword() const;
	bool nhapUsernameKhoiPhuc(std::string& strUsername) const;
	bool xacThucAdmin(const std::string& strUsername) const;
	void hienThiKetQuaKhoiPhuc(const std::string& strUsername) const;

	void hienThiKetThuc(const std::string& strThongBao) const;
	void baoLoi(const std::string& strThongBao) const;

	GiaoDien _giaoDien;
	XuLyFile _xuLyFile;
};
#endif