#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include"account.h"

std::vector<Account*> all_subaccount = {};

// �����������������˻�������AccountΪ����������ʣ�ʵ��ָ��Ŀ�ʹ��
void create_account() {
    std::string n, h, num;
    int m;
    Account* a = nullptr;
    std::cout << "�������˻�����";
    std::cin >> n;
    std::cout << "�������˻�������������";
    std::cin >> h;
    std::cout << "�������˻�id��";
    std::cin >> num;
    while (true) {
        std::cout << "�������˻���";
        std::cin >> m;
        if (m <= 100000000000000.00&&m>=0) {
            break;
        }
        else {
            std::cout << "���磨�ţ����鷳���������룬����ʲ��Ѿ������й���㴢����" << std::endl;
        }
    }
    a = new Account(n, h, num, m);
    all_subaccount.push_back(a);
    std::cout << "�˻������ɹ��������˳��˻���������" << std::endl;
}

//-----------Account---------------
// ���캯��
Account::Account(std::string n, std::string h, std::string num, double m) : name(n), holder(h), number(num), money(m) {}


// �������ݳ�Ա���ⲿ�ӿ�
std::string Account::get_name() {
    return name;
}
std::string Account::get_holder() {
    return holder;
}
std::string Account::get_number() {
    return number;
}
double Account::get_money() {
    return money;
}

// �޸��˻���Ϣ�ĺ���
void Account::set_name(std::string n) {
    name = n;
}
void Account::set_holder(std::string h) {
    holder = h;
}
void Account::set_number(std::string n) {
    number = n;
}
void Account::set_money(double m) {
    money = m;
}

// չ���˻���Ϣ
void Account::account_show() {
    std::cout << std::left << std::setw(10) << "holder: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", holder);
    std::cout << std::setw(10) <<"number: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", number);
    std::cout << std::setw(10) << "money: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", money);
}

// ȡǮ
void Account::withdraw(int m) {
    money -= m;
}

// ��Ǯ
void Account::deposit(int m) {
    money += m;
}

void Account::warning() {};

Account::~Account() {};

bool Account::operator ==(Account& a) {
    std::string temp = this->get_name();
    if (temp == a.get_name()) {
        return true;
    }
    else {
        return false;
    }
}

bool Account::operator ==(std::string& a) {
    std::string temp = this->get_name();
    if (temp == a) {
        return true;
    }
    else {
        return false;
    }
}
