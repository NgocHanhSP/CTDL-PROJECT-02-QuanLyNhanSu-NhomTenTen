#ifndef NGUOIDUNG_H_INCLUDED_
#define NGUOIDUNG_H_INCLUDED_

#include <functional>
#include <string>

class GiaoDien;
class XuLyFile;
class HoSoNhanVien;

class NguoiDung
{
public:
	NguoiDung(const GiaoDien& giaoDien, const XuLyFile& xuLyFile);
	virtual ~NguoiDung() = default;
	virtual void hienThiMenu(const std::string& strUsername) const = 0;

protected:
	void hienThiHoSo(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const;
	void chayChucNang(const std::string& strTieuDe, const std::function<void()>& chucNang) const;
	const GiaoDien& _giaoDien;
	const XuLyFile& _xuLyFile;
};
#endif