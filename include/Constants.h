#pragma once

// Constants.h
// Muc dich: Tap trung cac hang so va kieu du lieu dung chung trong chuong trinh.

const int MAX_LOGIN_ATTEMPTS = 3;
const int MIN_PASSWORD_LENGTH = 8;
const char DEFAULT_PASSWORD[] = "111111";

const char ADMIN_FILE_PATH[] = "data/Administrators.txt";
const char EMPLOYEE_FILE_PATH[] = "data/Employees.txt";
const char DATA_DIRECTORY[] = "data/";

enum class VaiTro
{
    ADMIN = 1,
    EMPLOYEE = 2
};

// Quy uoc mat khau manh de nhom thong nhat:
// toi thieu 8 ky tu, co chu hoa, chu thuong, chu so va ky tu dac biet.
// TODO: Implement kiem tra quy tac nay trong Employee.cpp.
