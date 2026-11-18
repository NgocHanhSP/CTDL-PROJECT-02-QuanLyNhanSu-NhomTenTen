#include "../include/NguoiDung.h"
#include <string>
#include <vector>
#include "../include/BangDuLieu.h"
#include "../include/GiaoDien.h"
#include "../include/HoSoNhanVien.h"
#include "../include/XuLyFile.h"

namespace
{
	const size_t PROFILE_LABEL_WIDTH = 20;
	const size_t PROFILE_VALUE_WIDTH = 55;
}

/**********************************************************
* @Description Khoi tao NguoiDung voi giao dien va xu ly file duoc truyen vao
*
* @return Khong co gia tri tra ve
* @attention Chi luu tham chieu, khong so huu hai doi tuong nay
**********************************************************/
NguoiDung::NguoiDung(const GiaoDien& giaoDien, const XuLyFile& xuLyFile)
	: _giaoDien(giaoDien),
	  _xuLyFile(xuLyFile)
{
	//TODO: Empty Method
}

/**********************************************************
* @Description Hien thi ho so nhan vien dang bang thuoc tinh/thong tin
*
* @return Khong co gia tri tra ve
**********************************************************/
void NguoiDung::hienThiHoSo(const std::string& strUsername, const HoSoNhanVien& hoSoNhanVien) const
{
	const std::vector<std::string> vecTieuDe = {"THUOC TINH", "THONG TIN"};
	const std::vector<size_t> vecDoRongCot = {PROFILE_LABEL_WIDTH, PROFILE_VALUE_WIDTH};
	BangDuLieu bangHoSo(vecTieuDe, vecDoRongCot);

	bangHoSo.themDong({"USERNAME", strUsername});
	bangHoSo.themDong({"HO TEN", hoSoNhanVien.getHoTen()});
	bangHoSo.themDong({"DIA CHI", hoSoNhanVien.getDiaChi()});
	bangHoSo.themDong({"SO DIEN THOAI", hoSoNhanVien.getSoDienThoai()});
	bangHoSo.themDong({"EMAIL", hoSoNhanVien.getEmail()});

	bangHoSo.hienThi();
}

/**********************************************************
* @Description Hien thi man hinh voi tieu de, chay chuc nang duoc chon roi cho nhan ENTER
*
* @return Khong co gia tri tra ve
**********************************************************/
void NguoiDung::chayChucNang(const std::string& strTieuDe, const std::function<void()>& chucNang) const
{
	this->_giaoDien.hienThiManHinh(strTieuDe);
	chucNang();
	this->_giaoDien.choEnter();
}
