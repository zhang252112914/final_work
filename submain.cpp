#define FMT_HEADER_ONLY  
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include<iomanip>
#include <conio.h>
#include<string>
#include<cstdio>
#include<vector>
#include<chrono>
#include<thread>    //��������ʱ���
#include"plan.h"
#include"account.h"
#include"ledger.h"
#include"summary.h"
#include"analyse.h"
#include"plan.h"
#include"data_in_out.h"
#include"search.h"
#include<mysql.h>


const char* host = "127.0.0.1";  //��������
const char* user = "root";              //���֣�Ĭ��root
const char* pw = "ZYl/20050507";        //����
const int port = 3306;                  //�˿ںţ�Ĭ��
const char* a_database = "account";     //���ݿ�����   
const char* l_database = "ledger";      //��ʹ�� MySQL C API �еĺ���ʱ��ͨ����Ҫ���� C �����ַ��������� std::string ����
const char* p_database = "plan";

std::vector<std::string> function_part_main = { "    �˻�      ","    �˱�      ","    ����      ","    �滮      ","    �˳�      " };
std::vector<std::string> function_part_account = { "    �����˻�    ","    �鿴�˻�    ","      �˳�      " };
std::vector<std::string> function_part_ledger = { "  ¼����Ŀ  ","  �鿴�˱�  ","  ��Ŀ����  ","    �˳�    " };
std::vector<std::string> way = { "��","��","��" };

void display_options(int selectedOption,std::vector<std::string> function_part) {
    system("cls");
    fmt::print("��ѡ����ģ��:\n");
    int n = size(function_part);
    for (int i = 1; i <= n; ++i) {
        fmt::print("{}{}\n", function_part[i - 1], (i == selectedOption) ? "<-" : "  ");
    }
}

int main() {
    std::cout << "���ݼ����У������ĵȺ�" << std::endl;
    //���ݵĶ���ģ�飬���������н������ݿ�����
    MYSQL* a_conn = mysql_init(NULL);
    MYSQL* l_conn = mysql_init(NULL);
    MYSQL* p_conn = mysql_init(NULL);
    mysql_options(a_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_options(l_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_options(p_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_real_connect(a_conn, host, user, pw, a_database, port, NULL, 0);
    mysql_real_connect(l_conn, host, user, pw, l_database, port, NULL, 0);
    mysql_real_connect(p_conn, host, user, pw, p_database, port, NULL, 0);
    account_reclaim(a_conn);
    ledger_reclaim(l_conn);
    plan_reclaim(p_conn);

    std::cout << "������ϣ�������" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    //���ϲ����Ѿ�û��������
    while (true) {
        if (all_subaccount.empty()) {
            std::cout << "�����ڻ�û���˻����޷�����ʹ�û������ܣ������ȴ���һ���˻�" << std::endl;
            create_account();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else
            break;
    }

    int selection = 1;
    while (true) {
        while (true) {
            display_options(selection, function_part_main);
            int n = size(function_part_main);
            char input = _getch(); // �Ӽ��̻�ȡ�ַ�

            if (input == -32) { // ����Ƿ����
                input = _getch(); // ��ȡ������ľ����ֵ

                switch (input) {
                case 72: // �ϼ�ͷ
                    selection = (1 > (selection - 1)) ? 1 : (selection - 1);
                    break;
                case 80: // �¼�ͷ
                    selection = (n < (selection + 1)) ? n : (selection + 1);
                    break;
                }
            }
            else if (input == '\r') { // Enter��
                if (selection != 5) {
                    fmt::print("��������{}ģ��\n", function_part_main[selection - 1]);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                else
                    break;
            }
        }
        system("cls");
        switch (selection) {
        case 1: {
            while (true) {
                int selection1 = 1;
                while (true) {
                    display_options(selection1, function_part_account);
                    int n = size(function_part_account);
                    char input1 = _getch(); // �Ӽ��̻�ȡ�ַ�

                    if (input1 == -32) {
                        input1 = _getch();

                        switch (input1) {
                        case 72: // �ϼ�ͷ
                            selection1 = (1 > (selection1 - 1)) ? 1 : (selection1 - 1);
                            break;
                        case 80: // �¼�ͷ
                            selection1 = (n < (selection1 + 1)) ? n : (selection1 + 1);
                            break;
                        }
                    }
                    else if (input1 == '\r') { // Enter��
                        if (selection1 != 3) {
                            fmt::print("��������{}ģ��\n", function_part_account[selection1 - 1]);
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        else
                            break;
                    }
                }
                system("cls");
                switch (selection1) {
                case 1: {
                    create_account();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                case 2: {
                    for (auto it : all_subaccount) {
                        it->account_show();
                        std::cout << std::endl;
                    }
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳��˻��鿴�밴Backspace���ý��潫��2min���Զ��رգ�");
                    char input1_1 = _getch();
                    if (input1_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 3: {
                    break;
                }
                }
                if (selection1 == 3) {
                    break;
                }
            }
            break;
        }
        case 2: {
            while (true) {
                int selection2 = 1;
                while (true) {
                    display_options(selection2, function_part_ledger);
                    int n = size(function_part_ledger);
                    char input2 = _getch(); // �Ӽ��̻�ȡ�ַ�

                    if (input2 == -32) {
                        input2 = _getch();

                        switch (input2) {
                        case 72: // �ϼ�ͷ
                            selection2 = (1 > (selection2 - 1)) ? 1 : (selection2 - 1);
                            break;
                        case 80: // �¼�ͷ
                            selection2 = (n < (selection2 + 1)) ? n : (selection2 + 1);
                            break;
                        }
                    }
                    else if (input2 == '\r') { // Enter��
                        if (selection2 != 4) {
                            fmt::print("��������{}ģ��\n", function_part_ledger[selection2 - 1]);
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        else
                            break;
                    }
                }
                switch (selection2) {
                case 1: {
                    create_ledger();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳���Ŀ�����밴Backspace���ý��潫��2min���Զ��رգ�");
                    char input2_1 = _getch();
                    if (input2_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 2: {
                    system("cls");
                    for (auto it = Book.rbegin(); it != Book.rend(); ++it) {
                        (*it)->ledger_show();
                        std::cout << std::endl;
                    }
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳���Ŀ�鿴�밴Backspace���ý��潫��2min���Զ��رգ�");
                    char input2_2 = _getch();
                    if (input2_2 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 3: {
                    int temp = 1;

                    while (true) {
                        system("cls");
                        fmt::print("��ѡ����ļ�����ʽ����{}����\n", way[temp-1]);
                        char input2_4 = _getch();
                        if (input2_4 == -32) {
                            input2_4 = _getch();
                            switch (input2_4) {
                            case 80:    //��
                                temp = ((temp - 1) > 1) ? (temp - 1) : 1;
                                break;
                            case 72:    //��
                                temp = ((temp + 1) < 3) ? (temp + 1) : 3;
                                break;
                            }
                        }
                        else if (input2_4 == '\r') {
                            break;
                        }
                    }
                    if (temp == 1) {
                        search_by_year_print();
                    }
                    else if (temp == 2) {
                        search_by_month_print();
                    }
                    else
                        search_by_date_print();
                    //ͳһ��������
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳���Ŀ�鿴�밴Backspace���ý��潫��2min���Զ��رգ�");
                    char input2_4_1 = _getch();
                    if (input2_4_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 4: {
                    break;
                }
                }
                if (selection2 == 4) {
                    break;
                }
            }
            break;
        }
        case 3: {
            int temp = 1;

            while (true) {
                system("cls");
                fmt::print("��ѡ������鿴�ı������ͣ�");
                fmt::print("{}����\n", way[temp-1]);
                char input3 = _getch();
                if (input3 == -32) {
                    input3 = _getch();
                    switch (input3) {
                    case 80:    //��
                        temp = ((temp - 1) > 1) ? (temp - 1) : 1;
                        break;
                    case 72:    //��
                        temp = ((temp + 1) < 3) ? (temp + 1) : 3;
                        break;
                    }
                }
                else if (input3 == '\r') {
                    break;
                }
            }
            if (temp == 1) {
                std::vector<double> temp_vector = sum_io_daily();
                std::cout << std::endl << "���ղ鿴�޷�Ϊ�������м�ֵ�ı���ֻ��Ϊ���ṩһЩ����������" << std::endl;
                analyse_daily(temp_vector);
            }
            else if (temp == 2) {
                std::vector<std::vector<double>> temp_vector = sum_all_monthly();
                analyse_summary(temp_vector);
            }
            else {
                std::vector<std::vector<double>> temp_vector = sum_all_yearly();
                analyse_summary(temp_vector);
            }
            fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳�����鿴�밴Backspace���ý��潫��2min���Զ��رգ�");
            char input3_1 = _getch();
            if (input3_1 == 8)
                break;

            std::this_thread::sleep_for(std::chrono::seconds(120));
            break;
        }
        case 4: {
            create_plan();
            fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "�˳��밴Backspace���ý��潫��2min���Զ��رգ�");
            char input4 = _getch();
            if (input4 == 8)
                break;

            std::this_thread::sleep_for(std::chrono::seconds(120));
            break;
        }
        case 5:
            break;
        }
        if (selection == 5)
            break;
    }
    plan_storage(p_conn);      //�������˳���෴����֤��������󴢴�          
    ledger_storage(l_conn);
    account_storage(a_conn);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
