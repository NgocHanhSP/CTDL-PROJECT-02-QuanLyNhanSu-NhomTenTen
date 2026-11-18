#ifndef CHUOIUTF8_H_INCLUDED_
#define CHUOIUTF8_H_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>

class ChuoiUtf8
{
public:
	ChuoiUtf8() = delete;

	static bool giaiMa(const std::string& strNguon, std::vector<unsigned int>& vecKyTu);
	static size_t demKyTu(const std::string& strNguon);
	static std::string catKyTu(const std::string& strNguon, const size_t uiSoKyTu);
	static std::string boKyTuDau(const std::string& strNguon, const size_t uiSoKyTu);
	static std::string chuanHoaKhoangTrang(const std::string& strNguon);
	static std::string chuyenThanhChuThuong(const std::string& strNguon);

private:
	static bool docMotKyTu(const std::string& strNguon, const size_t uiViTri, unsigned int& uiMaKyTu, size_t& uiDoDai);
	static bool layThongTinByteDau(const unsigned int uiByteDau, size_t& uiSoByteTiep, unsigned int& uiMaDau, unsigned int& uiMaNhoNhat);
	static size_t timViTriByte(const std::string& strNguon, const size_t uiSoKyTu);
};
#endif