#ifndef CONSTANTS_H_INCLUDED_
#define CONSTANTS_H_INCLUDED_

#include <cstddef>

const int MAX_LOGIN_ATTEMPTS = 3;
const int MAX_PASSWORD_ATTEMPTS = 3;
const size_t MIN_PASSWORD_LENGTH = 8;
const size_t MAX_PASSWORD_LENGTH = 32;
const size_t MIN_LEGACY_PASSWORD_LENGTH = 6;
const char DEFAULT_PASSWORD[] = "111111";

const size_t MIN_USERNAME_LENGTH = 3;
const size_t MAX_USERNAME_LENGTH = 20;
const size_t MIN_FULLNAME_LENGTH = 2;
const size_t MAX_FULLNAME_LENGTH = 50;
const size_t MIN_ADDRESS_LENGTH = 5;
const size_t MAX_ADDRESS_LENGTH = 150;
const size_t PHONE_LENGTH = 10;
const size_t MAX_EMAIL_LENGTH = 100;
const size_t MAX_EMAIL_LOCAL_LENGTH = 64;
const size_t MIN_EMAIL_TOP_LEVEL_LENGTH = 2;

const char DATA_DIRECTORY_NAME[] = "data";
const char DATA_DIRECTORY[] = "data/";
const char ADMIN_FILE_PATH[] = "data/Administrators.txt";
const char EMPLOYEE_FILE_PATH[] = "data/Employees.txt";
const char PROFILE_EXTENSION[] = ".txt";
const char TEMP_EXTENSION[] = ".tmp";

const int CONSOLE_WIDTH = 120;
const int LINE_WIDTH = 100;
const int TITLE_WIDTH = 88;
const int TITLE_BORDER_WIDTH = 2;
const int CENTER_DIVISOR = 2;
const char LOGIN_INDENT[] = "\t\t\t\t\t\t";
const char PASSWORD_MASK = '*';
const int MENU_CANCELLED = -1;
const int MENU_FIRST_OPTION = 1;
const char BORDER_CHAR = '*';

const int KEY_ENTER = 13;
const int KEY_BACKSPACE = 8;
const int KEY_EXTENDED_A = 224;
const int KEY_EXTENDED_B = 0;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_PRINTABLE_FIRST = 32;
const int KEY_PRINTABLE_LAST = 126;
const int KEY_YES_LOWER = 'y';
const int KEY_YES_UPPER = 'Y';
const int KEY_NO_LOWER = 'n';
const int KEY_NO_UPPER = 'N';
const int KEY_BACK_LOWER = 'b';
const int KEY_BACK_UPPER = 'B';

enum class VaiTro
{
	ADMIN = 1,
	EMPLOYEE = 2
};

enum class MauSac
{
	MAC_DINH = 7,
	DONG_DANG_CHON = 12,
	DONG_BINH_THUONG = 15,
	TIEU_DE = 14,
	DUONG_KE = 11,
	THANH_CONG = 10,
	LOI = 12
};
#endif