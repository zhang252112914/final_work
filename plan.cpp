#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include "plan.h"
#include <map>
#include <string>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <iterator>

std::vector<Plan> plan_collection = {};

void create_plan() {
    Plan plan;
    plan_collection.push_back(plan);
}

Plan::Plan() {
    std::cout << "���������¸��µļƻ�֧���ܶ ";
    std::cin >> plan_out_sum;

    std::cout << "��Խ�����һ���µĸ���֧������Ű��ţ� " << std::endl;
    std::string str = "ҽ��";
    double temp;
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "ʳƷ";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "ס��";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "��ͨ";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "����";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "Ͷ��";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "�罻";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "����";
    std::cout << str << "�� ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    std::cout << "����δ���滮������ϣ����ǽ��ڱ����ڶ��������ѽ��мල������" << std::endl;
}

Plan::Plan(double plan_out_sum, std::map<std::string, double> plan_out_type) : plan_out_sum(plan_out_sum), plan_out_type(plan_out_type) {}
//ר���ں����ݿ⽻����ʱ�����

double Plan::get_plan_out_sum() {
    return plan_out_sum;
}

std::map<std::string, double> Plan::get_plan_out_type() {
    return plan_out_type;
}

void Plan::plan_print() {
    std::cout << "�ƻ���֧����" << plan_out_sum << "��" << std::endl;
    std::cout << "�ƻ�֧�����ͣ�" << std::endl;
    auto it = plan_out_type.begin();
    for (int i = 0; it != plan_out_type.end(); it++) {
        std::cout << std::setw(5) << std::left << it->first << ":  " << std::setw(10) << std::left << std::fixed << std::setprecision(2) << it->second << std::setw(5) << std::left << "��" << std::endl;
        i++;
        if (i == 4) {
            std::cout << std::endl;
        }
    }
}

void Plan::monitor() {      //ÿ����һ����Ŀ�ͻᴥ��һ�μ�⣬�жϵ�ǰ״̬��ƻ�
    auto monitor_it = (Book.end() - 1);
    Date monitor_date = (*monitor_it)->date;    //ѡȡ���µ����ڶ�Ӧ���·ݽ��м��
    monitor_date.day_reset(1);
    std::vector<double> type_arr(8, 0);
    std::vector<std::string> name_arr{ "ҽ��", "ʳƷ", "ס��", "��ͨ", "����", "Ͷ��", "�罻", "����" };
    double out_sum = 0;
    for (auto it = Book.rbegin(); it != Book.rend(); it++) {
        if ((*it)->date == monitor_date && !((*it)->in_or_out)) {
            out_sum += (*it)->transaction_amount;
            if ((*it)->sle_type == "ҽ��") {
                type_arr[0] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "ʳƷ") {
                type_arr[1] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "ס��") {
                type_arr[2] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "��ͨ") {
                type_arr[3] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "����") {
                type_arr[4] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "Ͷ��") {
                type_arr[5] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "�罻") {
                type_arr[6] += (*it)->transaction_amount;
            }
            else {
                type_arr[7] += (*it)->transaction_amount;
            }
            if (it != Book.rend() && (it + 1) != Book.rend() && (*(it + 1))->date != monitor_date) { //���������Խ�磨���������������������鷳������֪�������ˣ�
                break;
            }

        }
    }
    if (out_sum > this->plan_out_sum) {
        fmt::print(fg(fmt::color::red), "�ƻ�֧�����꣬��ע�⣡\n");
        std::cout << "�ƻ�֧����" << this->plan_out_sum << "��" << std::endl;
        std::cout << "ʵ��֧���� ";
        fmt::print(fg(fmt::color::red), "{}", out_sum);
        std::cout << "��" << std::endl;
        std::cout << "���ƻ�֧���� ";
        double after = out_sum - this->plan_out_sum;
        fmt::print(fg(fmt::color::red), "{}", after);
        std::cout << "��" << std::endl;
    }
    else {
        std::cout << "�ƻ�֧��δ����,����Ԥ�㣺 " << this->plan_out_sum - out_sum << "��" << std::endl;
    }
    for (int i = 0; i < 8; i++) {
        if (type_arr[i] > plan_out_type[name_arr[i]]) {
            fmt::print(fg(fmt::color::red), "{}֧�����꣬��ע�⣡\n", name_arr[i]);
            std::cout << "�ƻ�֧����" << plan_out_type[name_arr[i]] << "��" << std::endl;
            std::cout << "ʵ��֧����" << type_arr[i] << "��" << std::endl;
            std::cout << "���ƻ�֧���� " << type_arr[i] - plan_out_type[name_arr[i]] << "��" << std::endl;
        }
        else {
            std::cout << name_arr[i] << "֧��δ����,����Ԥ�㣺 " << plan_out_type[name_arr[i]] - type_arr[i] << "��" << std::endl;
        }
    }
}
