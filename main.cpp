#include "Record.h"
#include "Notebook.h"

int main() {
    setlocale(LC_ALL, "ru");

    Notebook notebook;
    int choice;
    string surname, birthdate, phone;

    do {
        cout << "1. Добавить запись\n";
        cout << "2. Удалить запись\n";
        cout << "3. Поиск по фамилии\n";
        cout << "4. Поиск по телефону\n";
        cout << "5. Поиск по дате рождения\n";
        cout << "6. Показать все записи\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Введите фамилию: ";
                cin >> surname;
                cout << "Введите дату рождения (ДД-ММ-ГГГГ): ";
                cin >> birthdate;
                cout << "Введите телефон: ";
                cin >> phone;
                notebook.addRecord(surname, birthdate, phone);
                break;

            case 2:
                cout << "Введите фамилию для удаления: ";
                cin >> surname;
                notebook.deleteRecord(surname);
                break;

            case 3:
                cout << "Введите фамилию для поиска: ";
                cin >> surname;
                notebook.searchBySurname(surname);
                break;

            case 4:
                cout << "Введите телефон для поиска: ";
                cin >> phone;
                notebook.searchByPhone(phone);
                break;

            case 5:
                cout << "Введите дату рождения для поиска (ДД-ММ-ГГГГ): ";
                cin >> birthdate;
                notebook.searchByBirthdate(birthdate);
                break;

            case 6:
                notebook.printAllRecords();
                break;

            case 0:
                cout << "Выход...\n";
                break;

            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}