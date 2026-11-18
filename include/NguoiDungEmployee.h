#ifndef NGUOIDUNGEMPLOYEE_H_INCLUDED_
#define NGUOIDUNGEMPLOYEE_H_INCLUDED_

#include <string>
#include "NguoiDung.h"

class NguoiDungEmployee : public NguoiDung
{
public:
	NguoiDungEmployee(const GiaoDien& giaoDien, const XuLyFile& xuLyFile);
	virtual ~NguoiDungEmployee();
	virtual void hienThiMenu(const std::string& strUsername) const override;

private:
	enum class LuaChon
	{
		XEM_THONG_TIN = 1,
		DOI_PASSWORD = 2,
		THOAT = 3
	};

	bool xuLyLuaChon(const int iLuaChon, const std::string& strUsername) const;
	bool kiemTraDoiPasswordLanDau(const std::string& strUsername) const;
	bool doiPasswordLanDau(const std::string& strUsername) const;
	void xemThongTin(const std::string& strUsername) const;
	void doiPassword(const std::string& strUsername) const;
	bool nhapPasswordMoi(const std::string& strPasswordCu, std::string& strPasswordMoi) const;
	std::string layQuyTacPassword() const;
};
#endif