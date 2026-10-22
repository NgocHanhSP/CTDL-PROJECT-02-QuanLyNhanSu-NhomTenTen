// Employee.cpp
// Muc dich: Cai dat chuc nang nhan vien va doi mat khau.

#include "../include/Employee.h"
#include "../include/GiaoDien.h"
#include "../include/XuLyFile.h"
#include "../include/TaiKhoan.h"
#include "../include/NhanVien.h"
#include "../include/Constants.h"

void Employee::hienThiMenu(const std::string& strUsername)
{
    // TODO: Not Implemented
    // Doc tai khoan. Neu password == DEFAULT_PASSWORD thi bat buoc doi mat khau truoc.
    // Neu doi that bai/huy, khong cho vao menu thong thuong.
    // Sau do hien thi menu: xem thong tin, doi mat khau, thoat.
    (void)strUsername;
}

void Employee::xemThongTin(const std::string& strUsername)
{
    // TODO: Not Implemented - doc va hien thi ho so cua chinh nhan vien.
    (void)strUsername;
}

void Employee::doiMatKhau(const std::string& strUsername)
{
    // TODO: Not Implemented - yeu cau mat khau hien tai, mat khau moi va xac nhan lai.
    // Mat khau moi phai manh va khong duoc bang DEFAULT_PASSWORD.
    (void)strUsername;
}

bool Employee::doiMatKhauLanDau(const std::string& strUsername)
{
    // TODO: Not Implemented - bat buoc doi password mac dinh sang password manh.
    // Chi tra ve true sau khi cap nhat file thanh cong.
    (void)strUsername;
    return false;
}

bool Employee::kiemTraMatKhauManh(const std::string& strMatKhau)
{
    // TODO: Not Implemented - toi thieu 8 ky tu, co chu hoa, chu thuong,
    // chu so va ky tu dac biet.
    (void)strMatKhau;
    return false;
}
