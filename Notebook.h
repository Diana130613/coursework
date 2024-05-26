#ifndef Notebook_H
#define Notebook_H

#include "Record.h"
#include <map>
#include <regex>
class Notebook {
private:
    multimap<string, Record> records; // ��������� ��� �������� �������

public:
    // ���������� ������
    void addRecord(const string& surname, const string& birthdate, const string& phone) {
        if (surname.empty() || birthdate.empty() || phone.empty()) {
            throw invalid_argument("��� ���� ������ ���� ���������.");
        }
        if (!isValidDate(birthdate)) {
            throw invalid_argument("���� ������ ���� � ������� ��-��-����.");
        }
        Record record = { surname, birthdate, phone };
        records.insert(make_pair(surname, record));
    }

    // �������� ������ �� �������
    void deleteRecord(const string& surname) {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("������ �� �������.");
        }
        else {
            records.erase(range.first, range.second);
            cout << "������(�) � �������� " << surname << " �������." << endl;
        }
    }

    // ����� ������ �� �������
    void searchBySurname(const string& surname) const {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("������ �� �������.");
        }
        else {
            for (auto it = range.first; it != range.second; ++it) {
                cout << it->second << endl;
            }
        }
    }

    // ����� ������ �� ������ ��������
    void searchByPhone(const string& phone) const {
        for (const auto& pair : records) {
            if (pair.second.phone == phone) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("������ �� �������.");
    }

    // ����� ������ �� ���� ��������
    void searchByBirthdate(const string& birthdate) const {
        for (const auto& pair : records) {
            if (pair.second.birthdate == birthdate) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("������ �� �������.");
    }

    // ������ ���� �������
    void printAllRecords() const {
        if (records.empty()) {
            throw runtime_error("������� ���.");
        }
        for (const auto& pair : records) {
            cout << pair.second << endl;
        }
    }

private:
    bool isValidDate(const string& date) const {
        const regex pattern(R"(\d{2}-\d{2}-\d{4})");
        return regex_match(date, pattern);
    }
};
#endif