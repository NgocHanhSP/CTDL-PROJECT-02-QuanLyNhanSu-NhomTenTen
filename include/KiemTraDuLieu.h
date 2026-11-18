#ifndef KIEMTRADULIEU_H_INCLUDED_
#define KIEMTRADULIEU_H_INCLUDED_

#include <string>

class KiemTraDuLieu
{
public:
	KiemTraDuLieu() = delete;

	static bool laUsernameHopLe(const std::string& strUsername);
	static bool laUsernameDanhRieng(const std::string& strUsername);
	static bool laMatKhauManh(const std::string& strMatKhau);
	static bool laHoTenHopLe(const std::string& strHoTen);
	static bool laDiaChiHopLe(const std::string& strDiaChi);
	static bool laSoDienThoaiHopLe(const std::string& strSoDienThoai);
	static bool laEmailHopLe(const std::string& strEmail);

private:
	static bool laChuCai(const unsigned int uiMaKyTu);
	static bool laKyTuGhepDau(const unsigned int uiMaKyTu);
	static bool laKyTuPhanCach(const unsigned int uiMaKyTu);
	static bool laTenThietBi(const std::string& strTenThuong);
	static bool laPhanTenEmailHopLe(const std::string& strPhanTen);
	static bool laTenMienHopLe(const std::string& strTenMien);
	static bool laNhanTenMienHopLe(const std::string& strNhan);
	static bool laNhanCuoiHopLe(const std::string& strNhan);
};
#endif