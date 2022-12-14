#include <iostream>

enum Days {Sunday = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6};
enum class Months : short {Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

const char* week[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday","Firday", "Saturday" };
const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const char* dayName(Days day) {
	if (day < Sunday || day > Saturday) { return "알 수 없는 주"; }
	return week[day];
}

int main() {
	Days today = Thursday;

	Days tomorrow = (Days)(Thursday + 1); //기본적으로 열거형 타입이 정수로 반환되어 정수에 대한 연산이 이루어지므로 열거형 타입의 요소로 다시 변환해야 함.

	std::cout << dayName(today) << "은 " << today + 1 << "번째 요일이다." << std::endl;
	std::cout << dayName(tomorrow) << "은 " << tomorrow + 1 << "번째 요일이다." << std::endl;

	today = (Days)(Saturday + Friday);
	std::cout << dayName(today) << "은 " << today + 1 << "번째 요일이다." << std::endl;

	Months thisMonth = Months::Dec;
	Months nextMonth = (Months)((thisMonth == Months::Dec) ? 1 : (short)thisMonth + 1);
	short  monthNumber = (short)thisMonth;

	std::cout << months[monthNumber - 1] << "월은 " << monthNumber << "번째 월이다." << std::endl;
	std::cout << months[(short)nextMonth - 1] << "월은 " << (int)nextMonth << "번째 월이다." << std::endl;

}