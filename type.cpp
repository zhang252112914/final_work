#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "type.h"

// ���캯��
Type::Type() : predefined_type({ "ҽ��", "ʳƷ", "ס��", "��ͨ", "����", "����", "Ͷ��", "�罻", "����", "����" }) {}

// ��������
Type::~Type() {}

// �û�����Զ����������ĺ�����һ��ֻ�����һ����
void Type::add_userdefined_type(const std::string& s) {
    userdefined_type.insert(s);
}

// չ������Ԫ�أ�������ʼ�趨���û��Զ��壩
void Type::show_alltype() {
    int n = sizeof(predefined_type) / sizeof(std::string);
    int a = 1;
    for (const auto& type : predefined_type) {
        std::cout << a << "." << type << " ";
        a++;  // ����������Χfor�����ʵ�ֶ��Ѷ������ı���
    }
    int b = 11;
    for (const auto& type : userdefined_type) {
        std::cout << b << "." << type << " ";
        b++;
    }
    std::cout << std::endl;
}

// ��ȡ�û�ѡ����������ͣ���Ҫ����Ϊ��Ŀ�ṩ֧��
std::string Type::select_type() {
    std::cout << "��ѡ�������������ͣ�" << std::endl;
    int n;
    int startindex = userdefined_type.size();
    std::cin >> n;
    std::cin.get();
    if (n <= 10) {
        return predefined_type[n - 1];
    }
    else {
        auto it = userdefined_type.begin();
        std::advance(it, n - startindex - 1);
        return *it;
    }
}

bool Type::operator==(const Type& t) const {
    return type == t.type;
}
