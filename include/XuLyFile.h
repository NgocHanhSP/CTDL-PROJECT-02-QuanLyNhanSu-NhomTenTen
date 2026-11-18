#ifndef XULYFILE_H_INCLUDED_
#define XULYFILE_H_INCLUDED_

#include <string>
#include "Constants.h"

class TaiKhoan;
class HoSoNhanVien;

template <typename T>
class DanhSachLienKet;

class XuLyFile
{
public:
	bool taoThuMucDuLieu() const;

	bool kiemTraDangNhap(const std::string& strUsername, const std::string& strPassword, const VaiTro eVaiTro) const;
	bool kiemTraUsernameTonTai(const std::string& strUsername) const;
	bool kiemTraUsernameTrung(const std::string& strUsername) const;
	bool kiemTraTrungSoDienThoai(const std::string& strSoDienThoai, const std::string& strUsernameBoQua) const;
	bool kiemTraTrungEmail(const std::string& strEmail, const std::string& strUsernameBoQua) const;

	bool docTaiKhoan(const std::string& strUsername, TaiKhoan& taiKhoan) const;
	bool docDanhSachTaiKhoan(DanhSachLienKet<TaiKhoan>& danhSach) const;
	bool themTaiKhoan(const TaiKhoan& taiKhoan) const;
	bool xoaTaiKhoan(const std::string& strUsername) const;
	bool capNhatMatKhau(const std::string& strUsername, const std::string& strMatKhauMoi) const;

	bool docHoSoNhanVien(const std::string& strUsername, HoSoNhanVien& hoSoNhanVien) const;
	bool ghiHoSoNhanVien(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const;
	bool capNhatHoSoNhanVien(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const;

private:
	enum class TruongThongTin
	{
		SO_DIEN_THOAI,
		EMAIL
	};

	std::string layDuongDanTaiKhoan(const VaiTro eVaiTro) const;
	bool layDuongDanHoSo(const std::string& strUsername, std::string& strDuongDan) const;
	bool docFileTaiKhoan(const std::string& strDuongDan, DanhSachLienKet<TaiKhoan>& danhSach) const;
	bool ghiFileTaiKhoan(const std::string& strDuongDan, const DanhSachLienKet<TaiKhoan>& danhSach) const;
	bool thayTheFile(const std::string& strFileTam, const std::string& strFileDich) const;
	bool kiemTraTrungThongTin(const std::string& strGiaTri, const std::string& strUsernameBoQua, const TruongThongTin eTruong) const;
	std::string layGiaTriTruong(const HoSoNhanVien& hoSoNhanVien, const TruongThongTin eTruong) const;
};
#endif