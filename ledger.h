#pragma once
#include<vector>
#include<string>
#include"date.h"        
#include"account.h"
#include"summary.h"
#include"plan.h"

//һ��������Ŀ
class Plan;
class Account;
//�����ˮ���ȣ��������ledger�����࣬������note����note���֣�Ȼ���ټ̳������
class Ledger {
private:
    friend std::vector<double> sum_io_daily();
    friend std::vector<std::vector<double>> sum_all_monthly();
    friend std::vector<std::vector<double>> sum_all_yearly();
    friend class Plan;

    std::string transaction_partners;
    Account* subaccount;              //��ָ��ķ�ʽ��Account���һ��������ledger��ʵ��ͬ������
    bool in_or_out;                  //0 for out,1 for in
    double transaction_amount;
    std::string sle_type;        //����Ǵ������͵�ʵ��
    std::string note;
public:
    Date date;
    //�б�ע�ĳ�ʼ��(��������ν��������Ĭ�ϱ�ע�Ƿ�ᱻ���ǵ�����)
    Ledger(Date d, std::string tp, Account* sa, bool ioo, double ta, std::string st, std::string n);
    void ledger_show();
    std::string get_transaction_partners();
    std::string get_subaccount();
    int get_in_or_out();
    std::string get_sle_type();                //�������ϵͳ��ȡ
    std::string get_note();
    double get_transaction_amount();           //��Ҫ��Ϊ�˷������ͳ��֧����������
    void expense();              //���˵�ӳ�䵽�˻���
    bool operator<(const Ledger& l)const;
};

void create_ledger();

extern std::vector<Ledger*> Book;      //������¼������Ŀ��ָ��
//ָ��û�д����