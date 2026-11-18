#ifndef GIAODIEN_H_INCLUDED_
#define GIAODIEN_H_INCLUDED_

#include <string>
#include <vector>
#include "Constants.h"

class GiaoDien
{
public:
	int hienThiMenuDangNhap() const;
	int hienThiMenuAdmin() const;
	int hienThiMenuEmployee() const;
	int chonMenu(const std::string& strTieuDe, const std::vector<std::string>& vecLuaChon, const bool bChoPhepQuayLai = false) const;

	void xoaManHinh() const;
	void hienThiTieuDe(const std::string& strTieuDe) const;
	void hienThiManHinh(const std::string& strTieuDe) const;
	void hienThiChu(const std::string& strNoiDung, const bool bCanLe = false) const;
	void hienThiDong(const std::string& strNoiDung) const;
	void hienThiThongBao(const std::string& strThongBao) const;
	void hienThiLoi(const std::string& strThongBao) const;
	void choEnter(const std::string& strLoiNhac = "Nhan ENTER de quay lai...") const;

	std::string nhapChuoi(const std::string& strLoiNhac, const bool bCanLe = false) const;
	std::string nhapMatKhau(const std::string& strLoiNhac, const bool bCanLe = false) const;
	bool xacNhan(const std::string& strCauHoi) const;

private:
	void khoiTaoMaHoa() const;
	void datMau(const MauSac eMau) const;
	int tinhLeTrai(const std::string& strNoiDung) const;
	void inCanGiua(const std::string& strNoiDung) const;
	void veDuongKe(const char cKyTu) const;
	void veTieuDe(const std::string& strTieuDe) const;
	std::vector<std::string> canLeLuaChon(const std::vector<std::string>& vecLuaChon) const;
	void veMenu(const std::string& strTieuDe, const std::vector<std::string>& vecCanLe, const bool bChoPhepQuayLai, std::vector<int>& vecToaDoY) const;
	void veDongMenu(const std::string& strDong, const int iToaDoY, const bool bDangChon) const;
	int docLuaChonMenu(const std::vector<std::string>& vecCanLe, const std::vector<int>& vecToaDoY, const bool bChoPhepQuayLai) const;
	int docPhim(bool& bPhimMoRong) const;
};
#endif