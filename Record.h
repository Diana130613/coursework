#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>
using namespace std;
struct Record {
    string surname;
    string birthdate;
    string phone;

    // Оператор вывода для удобства печати
    friend ostream& operator<<(ostream& os, const Record& record) {
        os << "Фамилия: " << record.surname << ", Дата рождения: " << record.birthdate << ", Телефон: " << record.phone;
        return os;
    }
};
#endif