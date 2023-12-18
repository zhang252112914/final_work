#pragma once
#include<vector>
#include<string>
#include<fstream>
#include"date.h"
#include"summary.h"           //��Ԫ����
//�˴����˻�������ȫ��Ч�������˻������䴴����Ŀ���ǰ����û������֧;��
//������ֱ����������˻�չ���������Բ�������Ϣ(��������п��������ÿ�)�Ȳ���Ԫ�أ���������ز��֣�����û��ҪдһЩ�ظ��Ķ�����
class Ledger;

class Account {
    std::string name;     //�˻������֣�����֧������
    std::string holder;
    std::string number;   //��Ϊ�Ѽǣ����Բ�������������бȽ�
    double money;
public:
    friend std::vector<double> sum_io_daily();
    friend std::vector<std::vector<double>> sum_all_monthly();
    friend std::vector<std::vector<double>> sum_all_yearly();
    friend class Ledger;

    Account(std::string n, std::string h, std::string num, double m);
    std::string get_name();
    std::string get_holder();
    std::string get_number();
    double get_money();
    void set_name(std::string n);            //--------��Ҫ�����û��Լ��޸����ݣ���Ϊ���ܻ�����޷�������Ŀ�����ݸı�
    void set_holder(std::string h);
    void set_number(std::string n);
    void set_money(double m);               //------------------------------------------------------------------ 
    void withdraw(int sum);
    void deposit(int sum);
    void account_show();
    void warning();
    ~Account();
    bool operator == (Account& a);
    bool operator ==(std::string& a);
};

//һ����˻����������������ʵ��������ʲô΢����Ǯ�����п���
//����ͨ���˻�����û��ʲô����
//��ͷ�����費��Ҫ�麯����Ҫ�����ټ�
void create_account();

extern std::vector<Account*> all_subaccount;