#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include "analyse.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

double in_to_out_rate(std::vector<std::vector<double>> all_sum) {
    double result = all_sum.at(0).at(0) / all_sum.at(0).at(1);
    return result;
}

double storage_rate(std::vector<std::vector<double>> all_sum) {
    double result1 = all_sum.at(1).at(9) / all_sum.at(0).at(1);
    double result2 = all_sum.at(0).at(2) / all_sum.at(0).at(0);
    double result = result1 > result2 ? result1 : result2;
    return result;
}

double ROI(std::vector<std::vector<double>> all_sum) {
    if (all_sum.at(3).at(0) != 0) {
        return 0;
    }
    else {
        return (all_sum.at(3).at(0) / all_sum.at(3).at(1));
    }
}

double EG(std::vector<std::vector<double>> all_sum) {
    double eg = all_sum.at(1).at(1) / all_sum.at(0).at(0);
    return eg;
}

double CSI(std::vector<std::vector<double>> all_sum) {
    double csi = (all_sum.at(1).at(0) + all_sum.at(1).at(1) + all_sum.at(1).at(2) + all_sum.at(1).at(3)) / all_sum.at(0).at(0);
    return csi;
}

void analyse_daily(std::vector<double> all_sum) {
    fmt::print("�����칲֧����");
    fmt::print(fg(fmt::color::cyan), "{:.f2}\n", all_sum[0]);
    fmt::print("�����룺");
    fmt::print(fg(fmt::color::cyan), "{}\n", all_sum[1]);
    fmt::print("����֧Ϊ��");
    fmt::print(fg(fmt::color::cyan), "{}", all_sum[2]);
}

void analyse_summary(std::vector<std::vector<double>> all_sum) {
    std::ostringstream summary;

    double inOutRate = in_to_out_rate(all_sum);
    double storRate = storage_rate(all_sum);
    double roi = ROI(all_sum);
    double eg = EG(all_sum);
    double csi = CSI(all_sum);
    double a = all_sum.at(1).at(0), b = all_sum.at(1).at(1),c = all_sum.at(1).at(2),d= all_sum.at(1).at(3),e = all_sum.at(1).at(4),
        f = all_sum.at(1).at(5), g = all_sum.at(1).at(6), h = all_sum.at(1).at(7), i = all_sum.at(1).at(8),j = all_sum.at(1).at(9);
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold, "�������ѽṹ���£�\n");
    fmt::print("ҽ�ƣ�");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", a);
    fmt::print("ʳƷ��");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", b);
    fmt::print("ס����");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", c);
    fmt::print("��ͨ��");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", d);
    fmt::print("���֣�");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", e);
    fmt::print("���ʣ�");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", f);
    fmt::print("Ͷ�ʣ�");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", g);
    fmt::print("�罻��");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", h);
    fmt::print("���");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", i);
    fmt::print("������");
    fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", j);

    // �ۺ���֧�Ⱥʹ����ʷ���
    summary << "������֧��Ϊ��" << inOutRate << "��������Ϊ��" << storRate << "��";
    if (inOutRate > 1.2 && storRate >= 0.3) {
        summary << "���Ĳ���״���ǳ�����������Զ����֧�������кܺõĴ���ϰ�ߡ�";
    }
    else if (inOutRate > 1 && storRate >= 0.2) {
        summary << "���Ĳ���״�����ã��������֧��������ϰ�ߺ���";
    }
    else if (inOutRate > 0.8 && storRate >= 0.1) {
        summary << "���Ĳ���״���пɣ�����֧ƽ��ʹ���ռ����ޣ�����ע�����Ѻʹ��";
    }
    else {
        summary << "����֧�����ܳ�����ӽ����룬�Ҵ����ʽϵͣ���Ҫ��ע��֧�������ߴ��";
    }
    summary << std::endl;
    // Ͷ�ʻر��ʷ���
    summary << "Ͷ�ʻر���Ϊ��" << roi << "��";
    if (roi > 0.1) {
        summary << "����Ͷ��Ч�����������Կ��Ǽ������ֻ��Ż����в��ԡ�";
    }
    else if (roi > 0) {
        summary << "����Ͷ����һ�����棬��Ч�����Ǻ�������������Ҫ�������ԡ�";
    }
    else {
        summary << "����Ͷ��Ŀǰδ����Ԥ�����棬�������������͵���Ͷ�ʲ��ԡ�";
    }

    summary << std::endl;
    // ��������������ϰ�߷���
    summary << "�����ϵ��Ϊ��" << eg << "�����ѽṹָ��Ϊ��" << csi << "��";
    if (eg < 0.3 && csi < 0.4) {
        summary << "�������������ܸߣ�������������ռ�ȵͣ�ӵ�нϴ���������ѿռ䡣";
    }
    else if (eg < 0.4 && csi < 0.5) {
        summary << "���������������ã��к���Ļ����������Ѻ��������ѿռ䡣";
    }
    else if (eg < 0.5 && csi < 0.6) {
        summary << "�������������пɣ���������������ռ�Ƚϸߣ������ע�Ż����ѡ�";
    }
    else {
        summary << "���Ļ�����������ռ�ȸߣ��������ѿռ����ޣ���Ҫ��ע�͵����ճ���֧��";
    }

    // ��ӡ�ܽ�
    std::string su = summary.str();
    fmt::print(fg(fmt::color::yellow), "{}\n",su);
    double overall_score = inOutRate + storRate + roi + eg + csi;
    overall_score /= 5; // ȡƽ��ֵ
    fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "�ۺ�������\n");
    if (overall_score > 0.8) {
        fmt::print(fg(fmt::color::cyan),"����״�����㣬������Ͷ���봢�����ȡ�������ɹ������������Ƚ��Ĳ���滮��\n");
    }
    else if (overall_score > 0.5) {
        fmt::print(fg(fmt::color::orange), "����״�����ã�������һЩ�Ľ��Ŀռ䣬�����עͶ��ս�Ժ�����֧��ƽ�⡣\n");
    }
    else {
        fmt::print(fg(fmt::color::red), "����״���ϲ�ص��ע��֧ƽ��ʹ���ƶ����ǵ�Ͷ�ʼƻ��Ը������徭��״����\n");
    }
}
