#pragma once
#include"summary.h"
#include"ledger.h"
#include"type.h"
#include"date.h"
//�����ĺ���ϵ��
//��֧�ȣ�����û��͸֧����
double in_to_out_rate(std::vector<std::vector<double>> all_sum);
//�����ʣ���Ӧ�Է��յ�����
double storage_rate(std::vector<std::vector<double>> all_sum);

//return on investment��Ͷ�ʻر���
double ROI(std::vector<std::vector<double>> all_sum);

//���������ĺ���ϵ��
//�����ϵ��
double EG(std::vector<std::vector<double>> all_sum);
//���ѽṹָ��    ��Ҫ��֧ռ��֧���ı���
double CSI(std::vector<std::vector<double>> all_sum);

void analyse_daily(std::vector<double> all_sum);
void analyse_summary(std::vector<std::vector<double>> all_sum);
