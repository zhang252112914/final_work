#pragma once
#include<vector>

class Ledger;
class Account;
//��֧�Ļ���ģ��
std::vector<double> sum_io_daily();    //���ջ�����֧����֧�������������͵ı���,��Ϊû��̫�����壩

std::vector<std::vector<double>> sum_all_monthly();    //���»�����֧

std::vector<std::vector<double>> sum_all_yearly();    //���������֧