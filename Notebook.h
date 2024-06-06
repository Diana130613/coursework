#ifndef Notebook_H
#define Notebook_H
#include "Record.h"
#include <map>
#include <regex>
#include <fstream>
#include <sstream>

class Notebook {
private:
    multimap<string, Record> records; // Контейнер для хранения записей
    const string filename = "notebook.txt"; // Имя файла для хранения записей

public:
    // Конструктор, загружающий записи из файла
    Notebook() {
        loadFromFile();
    }

    // Деструктор, сохраняющий записи в файл
    ~Notebook() {
        saveToFile();
    }

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
        saveToFile();
    }

    // Удаление записи по фамилии
    void deleteRecord(const string& surname) {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("Запись не найдена.");
        }
        else {
            records.erase(range.first, range.second);
            saveToFile();
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

    // Сохранение всех записей в файл
    void saveToFile() const {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Не удалось открыть файл для записи.");
        }
        for (const auto& pair : records) {
            outFile << pair.second.surname << "," << pair.second.birthdate << "," << pair.second.phone << endl;
        }
    }

    // Загрузка всех записей из файла
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            // Файл может отсутствовать при первом запуске программы, это не ошибка
            return;
        }
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            Record record;
            if (iss >> record) {
                records.insert(make_pair(record.surname, record));
            }
        }
    }
};
#endif
