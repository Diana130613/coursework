#ifndef Notebook_H
#define Notebook_H

#include "Record.h"
#include <map>
#include <regex>
class Notebook {
private:
    multimap<string, Record> records; // Контейнер для хранения записей

public:
    // Добавление записи
    void addRecord(const string& surname, const string& birthdate, const string& phone) {
        if (surname.empty() || birthdate.empty() || phone.empty()) {
            throw invalid_argument("Все поля должны быть заполнены.");
        }
        if (!isValidDate(birthdate)) {
            throw invalid_argument("Дата должна быть в формате ДД-ММ-ГГГГ.");
        }
        Record record = { surname, birthdate, phone };
        records.insert(make_pair(surname, record));
    }

    // Удаление записи по фамилии
    void deleteRecord(const string& surname) {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("Запись не найдена.");
        }
        else {
            records.erase(range.first, range.second);
            cout << "Запись(и) с фамилией " << surname << " удалены." << endl;
        }
    }

    // Поиск записи по фамилии
    void searchBySurname(const string& surname) const {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("Запись не найдена.");
        }
        else {
            for (auto it = range.first; it != range.second; ++it) {
                cout << it->second << endl;
            }
        }
    }

    // Поиск записи по номеру телефона
    void searchByPhone(const string& phone) const {
        for (const auto& pair : records) {
            if (pair.second.phone == phone) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("Запись не найдена.");
    }

    // Поиск записи по дате рождения
    void searchByBirthdate(const string& birthdate) const {
        for (const auto& pair : records) {
            if (pair.second.birthdate == birthdate) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("Запись не найдена.");
    }

    // Печать всех записей
    void printAllRecords() const {
        if (records.empty()) {
            throw runtime_error("Записей нет.");
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