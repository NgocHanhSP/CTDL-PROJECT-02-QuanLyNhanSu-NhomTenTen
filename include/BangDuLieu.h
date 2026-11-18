#ifndef BANGDULIEU_H_INCLUDED_
#define BANGDULIEU_H_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>

class BangDuLieu
{
public:
	BangDuLieu(const std::vector<std::string>& vecTieuDe, const std::vector<size_t>& vecDoRongCot);
	void themDong(const std::vector<std::string>& vecDuLieu);
	void hienThi() const;

private:
	enum class LoaiDuong
	{
		TREN,
		GIUA,
		DUOI
	};

	void inDuongKe(const LoaiDuong eLoaiDuong) const;
	void inDong(const std::vector<std::string>& vecDuLieu) const;
	std::vector<std::string> chiaNhieuDong(const std::string& strNoiDung, const size_t uiDoRong) const;
	size_t timViTriNgat(const std::string& strNoiDung, const size_t uiDoRong) const;

	std::vector<std::string> _vecTieuDe;
	std::vector<size_t> _vecDoRongCot;
	std::vector<std::vector<std::string> > _vecDong;
};
#endif