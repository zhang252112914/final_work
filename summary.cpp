#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <conio.h>
#include <cstdlib>
#include<chrono>
#include<thread>    //��������ʱ���
#include "summary.h"
#include"type.h"
#include "ledger.h"
#include "date.h"
#include "account.h"
//��Ҫ���������ܽ������
extern std::vector<Ledger*> Book;
extern std::vector<Account*> all_subaccount;

std::vector<double> sum_io_daily() {
    std::vector<double> daily_sum;  // ����ͳ��������֧�������� vector ��Ԫ�ص�˳��Ϊ�����룬֧��������֧
    double sum_in = 0, sum_out = 0, net = 0;
    bool temp;

    std::cout << "����������鿴����ľ�������" << std::endl;  // ֻ�а�������û���ۺϱ���
    int y = 2023, m=1, d=1;
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
        int year = y, month = m, day = d;
        Date d(year, month, day, 12, 12);
   
        temp = d.IsDateLegal();
        if (temp) {
            break;
        }
        else {
            std::cout << "�뱣֤������������ƥ�䣬����������" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } while (true);
    std::vector<Ledger*>::iterator it = Book.begin();
    Date target_date(y, m, d);
    for (; it < Book.end(); it++) {
        if ((*it)->date == target_date) {
            break;
        }
    }
    if (it == Book.end() - 1) {
        std::cout << "û�и����ڵ�����" << std::endl;
        return {};  // ������Ҫ��纯���Է��������Ƿ���Ч���м��
    }
    for (; (*it)->date == target_date; it++) {
        if ((*it)->in_or_out) {
            sum_in += (*it)->transaction_amount;
        }
        else {
            sum_out += (*it)->transaction_amount;
        }
    }
    net = sum_in - sum_out;
    daily_sum.push_back(sum_in);
    daily_sum.push_back(sum_out);
    daily_sum.push_back(net);
    return daily_sum;
}

std::vector<std::vector<double>> sum_all_monthly() {
    std::cout << "����������鿴�±����������·�" << std::endl;
    int year, month, day = 1;
    std::cin >> year >> month;
    Date target_date(year, month, day);  // �����Ƚϵ�����
    std::vector<Ledger*>::iterator it = Book.begin();

    std::vector<double> io_sum;      // ��֧����
    double sum_in = 0, sum_out = 0, net = 0;  // ����˳��Ϊ���롢֧��������֧

    std::vector<double> type_sum;  // �������ͻ��ܵ����飬����Ϊ"ҽ��" , "ʳƷ" ,"ס��", "��ͨ" , "����", "����" ,"Ͷ��" ,"�罻","����", "����"
    double medicine = 0, food = 0, housing = 0;  // �������Զ���İ�����ȥ��
    double transportation = 0, entertainment = 0, salary = 0;
    double investment = 0, social = 0, savings = 0, other = 0;

    int n = all_subaccount.size();
    std::vector<double> account_sum(n, 0);  // �����˻����ܵ����飬���� all_subaccount ��˳��һһ��Ӧ
    std::vector<std::string> account_name;
    for (auto temp_it : all_subaccount) {
        std::string temp_str;
        temp_str = temp_it->get_name();
        account_name.push_back(temp_str);
    }

    // �����Ͷ�ʵľ�ϸͳ�ƣ������ˣ�����
    std::vector<double> invest_haha(2, 0);

    for (; it != Book.end(); it++) {
        if ((*it)->date == target_date) {  // ���Ƚ������ڵ��ж�

            // ��֧����
            if ((*it)->in_or_out) {
                sum_in += (*it)->transaction_amount;
            }
            else {
                sum_out += (*it)->transaction_amount;
            }

            // ���͹���
            if ((*it)->sle_type == "ҽ��") {  // 0
                medicine -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "ʳƷ") {  // 1
                food -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "ס��") {  // 2
                housing -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "��ͨ") {  // 3
                transportation -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "����") {  // 4
                entertainment -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "����") {  // 5
                salary += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "Ͷ��") {  // 6
                if ((*it)->in_or_out) {
                    investment += (*it)->transaction_amount;
                    invest_haha[0] += (*it)->transaction_amount;
                }
                else
                    investment -= (*it)->transaction_amount;
                invest_haha[1] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "�罻") {  // 7
                social -= (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "����") {  // 8
                savings += (*it)->transaction_amount;
            }
            else {  // 9
                if ((*it)->in_or_out) {
                    other += (*it)->transaction_amount;
                }
                else
                    other -= (*it)->transaction_amount;
            }

            // �˻�����
            for (int i = 0; i < n; i++) {
                if (*((*it)->subaccount) == account_name[i]) {
                    if ((*it)->in_or_out) {
                        account_sum[i] += (*it)->transaction_amount;
                        break;
                    }
                    else {
                        account_sum[i] -= (*it)->transaction_amount;
                        break;
                    }
                }
            }
            if ((*(it + 1))->date != target_date) {
                break;
            }
        }
    }
    net = sum_in - sum_out;
    io_sum.push_back(sum_in);  //��һ����ʱ�������֧����
    io_sum.push_back(sum_out);
    io_sum.push_back(net);

    type_sum.push_back(medicine);
    type_sum.push_back(food);
    type_sum.push_back(housing);
    type_sum.push_back(transportation);
    type_sum.push_back(entertainment);
    type_sum.push_back(salary);
    type_sum.push_back(investment);
    type_sum.push_back(social);
    type_sum.push_back(savings);
    type_sum.push_back(other);

    std::vector<std::vector<double>> all_sum;
    all_sum.push_back(io_sum);
    all_sum.push_back(type_sum);
    all_sum.push_back(account_sum);
    all_sum.push_back(invest_haha);  // �Ȼر�����Ͷ��
    return all_sum;
}

std::vector<std::vector<double>> sum_all_yearly() {
    std::cout << "����������鿴�걨������" << std::endl;
    int year, month = 1, day = 28;
    std::cin >> year;
    Type temp_type;
    Date target_date(year, month, day);  // �����Ƚϵ�����
    std::vector<Ledger*>::iterator it = Book.begin();
    std::vector<double> io_sum;
    double sum_in = 0, sum_out = 0, net = 0;

    std::vector<double> type_sum(10, 0);
    std::vector<std::string> type_name(temp_type.predefined_type.begin(), temp_type.predefined_type.end());

    std::vector<double> account_sum(all_subaccount.size(), 0);
    std::vector<std::string> account_name;
    int n = all_subaccount.size();
    for (auto temp_it : all_subaccount) {
        std::string temp_str;
        temp_str = temp_it->get_name();
        account_name.push_back(temp_str);
    }
    std::vector<double> invest_haha(2, 0);

    for (; it != Book.end(); it++) {
        std::vector<Account*>::iterator temp_it = all_subaccount.begin();
        if ((*it)->date == target_date) {  // ���Ƚ������ڵ��ж�
            // ��֧����
            if ((*it)->in_or_out) {
                sum_in += (*it)->transaction_amount;
            }
            else {
                sum_out += (*it)->transaction_amount;
            }

            // ���ͻ���
            for (int i = 0; i < 10; i++) {
                if ((*it)->sle_type == type_name[i] && (i == 5 || i == 8)) {
                    type_sum[i] += (*it)->transaction_amount;
                    break;
                }
                else if ((*it)->sle_type == type_name[i] && i == 6) {
                    if ((*it)->in_or_out) {  // ʹ��һ���ϣ�����Ļ���˼��
                        type_sum[i] += (*it)->transaction_amount;
                        invest_haha[0] += (*it)->transaction_amount;
                    }
                    else {
                        type_sum[i] -= (*it)->transaction_amount;
                        invest_haha[1] += (*it)->transaction_amount;
                    }
                    break;
                }
                else if ((*it)->sle_type == type_name[i] && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7)) {
                    type_sum[i] -= (*it)->transaction_amount;
                    break;
                }
                else {
                    if ((*it)->in_or_out) {
                        type_sum[i] += (*it)->transaction_amount;
                    }
                    else {
                        type_sum[i] -= (*it)->transaction_amount;
                    }
                    break;
                }
            }
            // �˻�����
            for (int i = 0; i < n; i++) {
                if (*((*it)->subaccount) == account_name[i]) {
                    if ((*it)->in_or_out) {
                        account_sum[i] += (*it)->transaction_amount;
                        break;
                    }
                    else {
                        account_sum[i] -= (*it)->transaction_amount;
                        break;
                    }
                }
            }
            if ((*(it + 1))->date != target_date) {
                break;
            }
        }
    }
    net = sum_in - sum_out;
    io_sum.push_back(sum_in);
    io_sum.push_back(sum_out);
    io_sum.push_back(net);
    std::vector<std::vector<double>> all_sum;
    all_sum.push_back(io_sum);
    all_sum.push_back(type_sum);
    all_sum.push_back(account_sum);
    all_sum.push_back(invest_haha);
    return all_sum;
}
//�����Ҫ��analyse��������ʹ�õ�