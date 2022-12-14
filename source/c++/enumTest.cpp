#include <iostream>

enum Days {Sunday = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6};
enum class Months : short {Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

const char* week[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday","Firday", "Saturday" };
const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const char* dayName(Days day) {
	if (day < Sunday || day > Saturday) { return "�� �� ���� ��"; }
	return week[day];
}

int main() {
	Days today = Thursday;

	Days tomorrow = (Days)(Thursday + 1); //�⺻������ ������ Ÿ���� ������ ��ȯ�Ǿ� ������ ���� ������ �̷�����Ƿ� ������ Ÿ���� ��ҷ� �ٽ� ��ȯ�ؾ� ��.

	std::cout << dayName(today) << "�� " << today + 1 << "��° �����̴�." << std::endl;
	std::cout << dayName(tomorrow) << "�� " << tomorrow + 1 << "��° �����̴�." << std::endl;

	today = (Days)(Saturday + Friday);
	std::cout << dayName(today) << "�� " << today + 1 << "��° �����̴�." << std::endl;

	Months thisMonth = Months::Dec;
	Months nextMonth = (Months)((thisMonth == Months::Dec) ? 1 : (short)thisMonth + 1);
	short  monthNumber = (short)thisMonth;

	std::cout << months[monthNumber - 1] << "���� " << monthNumber << "��° ���̴�." << std::endl;
	std::cout << months[(short)nextMonth - 1] << "���� " << (int)nextMonth << "��° ���̴�." << std::endl;

}