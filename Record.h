#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>
using namespace std;
struct Record {
    string surname;
    string birthdate;
    string phone;

    // �������� ������ ��� �������� ������
    friend ostream& operator<<(ostream& os, const Record& record) {
        os << "�������: " << record.surname << ", ���� ��������: " << record.birthdate << ", �������: " << record.phone;
        return os;
    }
};
#endif