#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include<chrono>
#include<thread>    //��������ʱ���
#include "search.h"
#include"ledger.h"
#include"date.h"  

// ��Ѱ��Ӧ������
void search_by_date_print() {
    int y = 2023, m = 1, d = 1;
    bool temp = true;
    
    do {
        std::cout << "��ѡ�������գ�";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        while (true) {
            system("cls");
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
                case 80:    //�¼�ͷ
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
        int year = y, month = m, day = d;
        Date d(year, month, day);
        temp = d.IsDateLegal();
        if (temp) {
            break;
        }
        else {
            std::cout << "�뱣֤������������ƥ�䣬����������" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } while (true);
    Date target_date(y, m, d);
    auto it = Book.begin();
    for (; it != Book.end(); it++) {
        if ((*it)->date == target_date) {
            (*it)->ledger_show();
            auto nextIt = std::next(it);  // ��ȡ��һ��������,��ֱ��ʹ��it++����ָ��endʹ����Ч
            if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                continue;
            }
            else {
                break;
            }
        }
        if (it == Book.end() - 1 && (*it)->date != target_date) {
            std::cout << "δ�ҵ������ڶ�Ӧ����Ŀ" << std::endl;
        }
    }
}

void search_by_month_print() {         
    int y = 2023, m = 1, day = 1;
    std::cout << "��ѡ�����£�";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (true) {
        system("cls");
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
    Date target_date(y, m, day);
    auto it = Book.begin();
    for (; it != Book.end(); it++) {
        if ((*it)->date == target_date) {
            (*it)->ledger_show();
            auto nextIt = std::next(it);  // ��ȡ��һ��������,��ֱ��ʹ��it++����ָ��endʹ����Ч
            if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                continue;
            }
            else {
                break;
            }
        }
        if (it == Book.end() - 1 && (*it)->date != target_date) {
            std::cout << "δ�ҵ������ڶ�Ӧ����Ŀ" << std::endl;
        }
    }
}

void search_by_year_print() {
    int year, month = 1, day = 28;
    std::cout << "�������꣺";
    std::cin >> year;
    Date target_date(year, month, day);
    auto it = Book.begin();
    for (; it != Book.end(); it++) {
        if ((*it)->date == target_date) {
            (*it)->ledger_show();
            auto nextIt = std::next(it);  // ��ȡ��һ��������,��ֱ��ʹ��it++����ָ��endʹ����Ч
            if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                continue;
            }
            else {
                break;
            }
        }
        if (it == Book.end() - 1 && (*it)->date != target_date) {
            std::cout << "δ�ҵ������ڶ�Ӧ����Ŀ" << std::endl;
        }
    }
}
