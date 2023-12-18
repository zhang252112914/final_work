#pragma once
#include"summary.h"
#include"ledger.h"
#include<map>
#include<string>
#include"date.h"
#include"data_in_out.h"
//ע�⣺��Ӧ��ledgerȫ��in_or_outȫΪ0����

class Plan {
private:
    double plan_out_sum;
    std::map<std::string, double> plan_out_type;
public:
    friend void plan_storage(MYSQL* conn);
    Plan();
    Plan(double plan_out_sum, std::map<std::string, double> plan_out_type);
    double get_plan_out_sum();                            //�����ӿ�
    std::map<std::string, double> get_plan_out_type();
    void plan_print();
    void monitor();       //�ƻ��ļ��ϵͳ
};

extern std::vector<Plan> plan_collection;  //����plan��Ե��ǵ�ǰ���·ݣ����ֻҪ������������plan������ȡ������
void create_plan();
