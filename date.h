#pragma once
class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
public:
    Date(int y, int m, int d, int h = 0, int min = 0);
    ~Date();
    int code1();
    int code2();
    void date_speshow();    //����ʱ��չʾ
    void date_show();       //����չʾ
    void day_reset(int d);
    int getyear();
    int getmonth();
    int getday();
    int gethour();
    int getminute();
    bool Isleapyear(int y);
    bool IsDateLegal();
    bool IsTimeLegal();
    int get_days_inmonth(int year, int month);
    int countDaysFromStart(int year, int month, int day);
    int operator-(const Date& d1);     //ĳ��ǰ�����������
    Date operator-(int d);        //�����ڼ��ж�����
    void operator=(Date& d1);    //����
    bool operator ==(const Date& d1)const;   //�Ƚ�
    bool operator !=(const Date& d1)const;
    bool operator <(const Date& d1)const;    //���ǰС
    bool operator >(const Date& d1)const;
};