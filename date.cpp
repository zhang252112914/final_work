#include<iostream>
#include<iomanip>
#include<sstream>
#include<stdexcept>  // �������
#include"date.h"

static const int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
static const int arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
//���캯��
Date::Date(int y, int m, int d, int h, int min) :year(y), month(m), day(d), hour(h), minute(min) {}

int Date::code1() {
    return year * 100 + month;
}
int Date::code2() {
    return day * 10000 + hour * 100 + minute;
}

//չʾ��ϸ�����ڣ�����ֻ������Ŀչʾʱʹ��
void Date::date_speshow() {
    std::ostringstream oss;
    oss << year << "."
        << std::setw(2) << std::setfill('0') << month << "."
        << std::setw(2) << std::setfill('0') << day << "  "
        << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute;
    std::cout << oss.str() << std::endl;
}
//չ�ִ�����ڣ�����ͳ��
void Date::date_show() {
    std::cout << year << "." << std::setw(2) << std::setfill('0') << month << "." << std::setw(2) << std::setfill('0') << day << std::endl;
}

void Date::day_reset(int d) {
    this->day = d;
}

//��������
Date::~Date() {}
//�ж��Ƿ������꣬�����ж����������Ƿ�Ƿ�
bool Date::Isleapyear(int y) {                           //�ж����������Ƿ�������
    if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) {
        return true;
    }
    else
        return false;
}
//�����յĻ�ȡ
int Date::getyear() {
    return year;
}
int Date::getmonth() {
    return month;
}
int Date::getday() {
    return day;
}
int Date::gethour() {
    return hour;
}
int Date::getminute() {
    return minute;
}

//�ж�����ľ���ʱ���Ƿ�Ϸ�
bool Date::IsTimeLegal() {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }
    return true;
}

//�������ڣ��ж������Ƿ�Ϸ�
bool Date::IsDateLegal() {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false; // �ꡢ�¡��ձ�����ڵ���1
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (Isleapyear(year)) {
        daysInMonth[2] = 29; // ���������29��
    }
    if (day > daysInMonth[month]) {
        return false; // ��������ڴ��ڸ����������
    }
    return true; // ���ںϷ�
}

int Date::get_days_inmonth(int year, int month) {
    static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = daysInMonth[month];
    if (month == 2 && Isleapyear(year)) {
        days = 29;
    }
    return days;
}


//��������������֮���������������Ҫ������ÿ���ծ������Ϣ�ļ���
int Date::operator-(const Date& d) {
    // ����������ת��Ϊ�ӹ�Ԫ1��1��1�տ�ʼ������
    int days1 = countDaysFromStart(year, month, day);
    int days2 = countDaysFromStart(d.year, d.month, d.day);

    // ������������֮��Ĳ�ֵ
    return days1 - days2;
}

int Date::countDaysFromStart(int year, int month, int day) {
    static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = 0;
    // ��������������ݵ�����
    for (int y = 1; y < year; ++y) {
        days += (Isleapyear(y) ? 366 : 365);
    }
    // ���ϵ�ǰ����������·ݵ�����
    for (int m = 1; m < month; ++m) {
        days += daysInMonth[m];
        if (m == 2 && Isleapyear(year)) {
            days += 1; // ������¶�һ��
        }
    }
    // ���ϵ�ǰ�·��е�����
    days += day;
    return days;
}

Date Date::operator-(int d) {
    Date result = *this;  // ����һ���µ����ڶ��󲢸��Ƶ�ǰ����
    result.day -= d;

    while (result.day <= 0) {
        result.month--;
        if (result.month <= 0) {
            result.year--;
            result.month = 12;
        }
        int daysbefore = get_days_inmonth(result.year, result.month);
        result.day += daysbefore;
    }
    return result;
}


bool Date::operator ==(const Date& d1)const {
    if (d1.day == 1) {
        if (d1.year == year && d1.month == month)
            return true;                        //d1.day=1ʱ����ζ�Ű������½��бȽ�
        else                                     //���Ǿ�����Ŀ���Ǳ����ڣ�Ҳ�ܹ�ʵ�����¼���
            return false;
    }
    else if (d1.day == 28) {                          //d1.day=28ʱ����ζ�Ű�����бȽ�
        if (d1.month == 1) {                        //��ȻҲ���������ڱȽ�
            if (d1.year == year)
                return true;
            else
                return false;
        }
        else {
            if (d1.year == year && d1.month == month)   //�������������ս��бȽ�
                return true;
            else
                return false;
        }
    }
    else {
        if (year == d1.year && month == d1.month && day == d1.day)
            return true;
        else
            return false;
    }
}

bool Date::operator!=(const Date& d1)const {
    return !(*this == d1);
}

void Date::operator =(Date& d1) {
    year = d1.year;
    month = d1.month;
    day = d1.day;
}

bool Date::operator <(const Date& d1)const {
    if (year < d1.year)
        return true;
    else if (year == d1.year && month < d1.month)
        return true;
    else if (year == d1.year && month == d1.month && day < d1.day)
        return true;
    else
        return false;
}

bool Date::operator >(const Date& d1)const {
    if (year > d1.year)
        return true;
    else if (year == d1.year && month > d1.month)
        return true;
    else if (year == d1.year && month > d1.month && day > d1.day)
        return true;
    else
        return false;
}
