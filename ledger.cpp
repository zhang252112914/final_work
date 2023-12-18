#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include <conio.h>
#include <cstdlib>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<chrono>
#include<thread>    //��������ʱ���
#include"type.h"
#include "ledger.h"

// ��ʼ��Books
std::vector<Ledger*> Book = {};

// ����һ���˵��Ľ�����������Ŀ�����ռ����ݣ������캯�����ڴ���������Ŀ��ʱ���Զ�����expense()�����˻�����ʵʱ�޸�
// ��ν�������˻���ѡ��
void create_ledger() {
    int y = 2023, m = 1, d = 1, h = 0, min = 0;
    std::string tp, n = "~";
    // subaccount����֮ǰ�Ѿ������õ��˻�����
    bool ioo;
    double ta;
    Type type;
    std::string st;     // ���ý�������

    bool temp = true;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    do {
        while (true) {
            system("cls");
            std::cout << "��ѡ����ʱ��(������ʱ��)��" << std::endl;
            std::cout << std::endl;
            std::cout << "��: " << y;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    y = ((y - 1) > 1) ? (y - 1) : 1;
                    break;
                case 72:  //�ϼ�ͷ
                    y = ((y + 1) < 2030) ? (y + 1) : 2030;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}\n", y);
            std::cout << "��: " << m;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    m = ((m - 1) > 1) ? (m - 1) : 1;
                    break;
                case 72:  //�ϼ�ͷ
                    m = ((m + 1) < 12) ? (m + 1) : 12;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}\n", y, m);
            std::cout << "��: " << d;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    d = ((d - 1) > 1) ? (d - 1) : 1;
                    break;
                case 72:  //�ϼ�ͷ
                    d = ((d + 1) < 31) ? (d + 1) : 31;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}.{}\n", y, m, d);
            std::cout << "Сʱ: " << h;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    h = ((h - 1) > 0) ? (h - 1) : 0;
                    break;
                case 72:  //�ϼ�ͷ
                    h = ((h + 1) < 24) ? (h + 1) : 24;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}.{}  {}\n", y, m, d, h);
            std::cout << "��: " << min;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    min = ((min - 1) > 0) ? (min - 1) : 0;
                    break;
                case 72:  //�ϼ�ͷ
                    min = ((min + 1) < 60) ? (min + 1) : 60;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        int year = y, month = m, day = d, minute = min, hour = h;
        Date d(year, month, day, hour, minute);
        temp = d.IsDateLegal();
        if (temp) {
            break;
        }
        else {
            std::cout << "�뱣֤������������ƥ�䣬����������" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }while (true);
    Date date(y, m, d, h, min);
    
    system("cls");
    std::cout << "�����뽻�׷���";
    std::cin >> tp;

    std::vector<Account*>::iterator it;
    it = all_subaccount.begin();  // ѡ�������˻�ʱҪȷ�������˻���Ϣ��Ϊ�գ���ؼ�������������ִ��
    while (true) {
        system("cls");
        std::cout << "��ѡ�����˻��� " << (*it)->get_name();
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //�¼�ͷ
                if (it == all_subaccount.begin()) {
                    break;
                }
                else {
                    it--;
                    break;
                }
            case 72:  //�ϼ�ͷ
                if (it == (all_subaccount.end() - 1))
                    break;
                else {
                    it++;
                    break;
                }
            }
        }
        else if (input == '\r') {
            break;
        }
    }

    system("cls");
    std::cout << "�����뽻�׽�";
    std::cin >> ta;
    ta = abs(ta);

    std::vector<std::string> inout = { "֧��","����" };
    int i = 0;
    while (true) {
        system("cls");
        std::cout << "��ѡ������/֧���� " << inout[i];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //�¼�ͷ
                i = ((i - 1) > 0) ? (i - 1) : 0;
                break;
            case 72:  //�ϼ�ͷ
                i = ((i + 1) < 1) ? (i + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            if (i == 0)
                ioo = false;
            else
                ioo = true;
            break;
        }
    }

    // ��������
    system("cls");
    type.show_alltype();
    std::string user_define = "A";
    std::vector<std::string> yes_or_no = { "��","��" };
    int j = 0;
    while (true) {
        system("cls");
        std::cout << "���Ƿ���Ҫ�Զ����������ͣ�";
        std::cout << yes_or_no[j];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //�¼�ͷ
                j = ((j - 1) > 0) ? (j - 1) : 0;
                break;
            case 72:  //�ϼ�ͷ
                j = ((j + 1) < 1) ? (j + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            break;
        }
    }
    int type_num = 1;
    if (j==1) {
        while (true) {
            system("cls");
            type.show_alltype();
            std::cout << "��ѡ����������: " << type_num;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //�¼�ͷ
                    type_num = ((type_num - 1) > 1) ? (type_num - 1) : 1;
                    break;
                case 72:  //�ϼ�ͷ
                    type_num = ((type_num + 1) < 10) ? (type_num + 1) : 10;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        st = type.predefined_type[type_num - 1];
    }
    else {
        system("cls");
        std::cout << "�������Զ��彻�����ͣ�";
        std::cin >> user_define;
        type.add_userdefined_type(user_define);
        st = user_define;            //��Ȼ������Զ������ͣ���˵������Ҫʹ��������ͣ���ô��Ҫ��ѡ����
    }
    //���ﲻ����ѡ��ķ�ʽ�ˣ�ֻ���еı�׼����

    int yon = 0;
    while (true) {
        system("cls");
        std::cout << "���Ƿ���Ҫ��ӱ�ע��";
        std::cout << yes_or_no[yon];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //�¼�ͷ
                yon = ((yon - 1) > 0) ? (yon - 1) : 0;
                break;
            case 72:  //�ϼ�ͷ
                yon = ((yon + 1) < 1) ? (yon + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            break;
        }
    }
    if (yon == 0) {
        system("cls");
        std::cout << "�����뱸ע��";
        std::cin >> n;
    }
    std::cout << std::endl;
    Ledger* l = new Ledger(date, tp, (*it), ioo, ta, st, n);
    l->expense();
    Book.push_back(l);
    std::sort(Book.begin(), Book.end(), [](const Ledger* a, const Ledger* b) {
        return *a < *b;
        });
    system("cls");
    if (!ioo) {
        if (!plan_collection.empty()) {
            auto plan_ptr = (plan_collection.end() - 1);
            (*plan_ptr).monitor();
        }
        else
            std::cout << "�����ڻ�δ�����κι滮�������������滮�Լ���ල����" << std::endl;
    }
}

Ledger::Ledger(Date d, std::string tp, Account* sa, bool ioo, double ta, std::string st, std::string n) :
    date(d), transaction_partners(tp), subaccount(sa), in_or_out(ioo), transaction_amount(ta), sle_type(st), note(n)
{}

void Ledger::ledger_show() {
    date.date_speshow();
    std::cout << "   ";
    std::cout << transaction_partners;
    std::cout << "   ";
    std::cout << subaccount->get_name();
    std::cout << "   ";
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "{:.2f}", transaction_amount);
    std::cout << "   ";
    std::cout << sle_type;
    std::cout << "   ";
    std::cout << note << std::endl;
}

std::string Ledger::get_transaction_partners() {
    return transaction_partners;
}

std::string Ledger::get_subaccount() {
    return subaccount->get_name();
}

int Ledger::get_in_or_out() {
    if (in_or_out) {
        return 1;
    }
    else {
        return 0;
    }
}



std::string Ledger::get_note() {
    return note;
}

// ��ȡ��֧����
std::string Ledger::get_sle_type() {
    return sle_type;
}

// ���׶�Ľӿ�
double Ledger::get_transaction_amount() {
    return transaction_amount;
}

// �����û�¼����Ŀ�������Ӧ�˻������޸�
// ͬʱҲ��ζ���û�������¼���˻���Ϣ
void Ledger::expense() {
    if (in_or_out)
        subaccount->deposit(get_transaction_amount());
    else
        subaccount->withdraw(get_transaction_amount());
}

bool Ledger::operator<(const Ledger& l) const {
    return date < l.date;
}
