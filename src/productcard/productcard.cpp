// ===== main.cpp =====
#include <iostream>
#include <string>
#include <vector>
#include "../../include/Book.h"

using namespace std;

void ProductCardModule(vector<Book>& books);
void CreateProductCard(vector<Book>& books);
void CheckProductCard(const vector<Book>& books);
void EditProductCard(vector<Book>& books);   // ← додано
void RunApplication();

void RunApplication() {
    vector<Book> books;
    ProductCardModule(books);
}

void ProductCardModule(vector<Book>& books) {
    int option;
    do {
        cout << "\nВиберіть потрібний варіант\n";
        cout << "1) Створити картку товару\n";
        cout << "2) Переглянути картку товару\n";
        cout << "3) Редагувати картку товару\n";  // ← нова опція
        cout << "4) Вихід\n";
        cout << "Оберіть опцію: ";

        if (!(cin >> option)) {
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Невірне введення.\n";
            continue;
        }

        switch (option) {
            case 1:
                CreateProductCard(books);
                break;
            case 2:
                CheckProductCard(books);
                break;
            case 3:
                EditProductCard(books);
                break;
            case 4:
                cout << "Вихід...\n";
                break;
            default:
                cout << "Невідома опція.\n";
                break;
        }
    } while (option != 4);
}

void CreateProductCard(vector<Book>& books) {
    cout << "\n-- Створення картки --\n";
    Book b;

    cout << "Напишіть назву книги: ";
    getline(cin >> ws, b.title);

    cout << "Напишіть автора: ";
    getline(cin, b.author);

    cout << "Вкажіть жанр: ";
    getline(cin, b.genre);

    cout << "Введіть рік видання: ";
    while (!(cin >> b.year)) {
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введіть ціле число для року: ";
    }

    cout << "Введіть ціну книги: ";
    while (!(cin >> b.price)) {
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введіть число для ціни: ";
    }

    cout << "Вкажіть наявність (так/ні): ";
    getline(cin >> ws, b.availability);

    books.push_back(b);
    cout << "\nКартка товару створена успішно! Номер книги: " << books.size() << "\n";
}

void CheckProductCard(const vector<Book>& books) {
    if (books.empty()) {
        cout << "Немає карток для перегляду.\n";
        return;
    }

    cout << "Перегляд картки \n";
    cout << "Напишіть номер книги (1 - " << books.size() << "): ";
    int bookNumber;
    if (!(cin >> bookNumber)) {
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Невірне введення.\n";
        return;
    }

    int idx = bookNumber - 1;
    if (idx < 0 || idx >= static_cast<int>(books.size())) {
        cout << "Картка з таким номером не існує.\n";
        return;
    }

    const Book& b = books[idx];
    cout << "Назва: "        << b.title        << '\n'
         << "Автор: "        << b.author       << '\n'
         << "Жанр: "         << b.genre        << '\n'
         << "Рік: "          << b.year         << '\n'
         << "Ціна: "         << b.price        << '\n'
         << "Наявність: "    << b.availability << '\n';
}

void EditProductCard(vector<Book>& books) {
    if (books.empty()) {
        cout << "Немає карток для редагування.\n";
        return;
    }

    cout << "\n-- Редагування картки --\n";
    cout << "Введіть номер книги (1 - " << books.size() << "): ";

    int bookNumber;
    if (!(cin >> bookNumber)) {
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Невірне введення.\n";
        return;
    }

    int idx = bookNumber - 1;
    if (idx < 0 || idx >= static_cast<int>(books.size())) {
        cout << "Картка з таким номером не існує.\n";
        return;
    }

    Book& b = books[idx];

    cout << "\nПоточні дані:\n";
    cout << "1) Назва: "     << b.title        << '\n';
    cout << "2) Автор: "     << b.author       << '\n';
    cout << "3) Жанр: "      << b.genre        << '\n';
    cout << "4) Рік: "       << b.year         << '\n';
    cout << "5) Ціна: "      << b.price        << '\n';
    cout << "6) Наявність: " << b.availability << '\n';

    cout << "\nЩо бажаєте змінити? ";
    int option;
    cin >> option;
    cin.ignore();

    switch (option) {
        case 1:
            cout << "Нова назва: ";
            getline(cin, b.title);
            break;
        case 2:
            cout << "Новий автор: ";
            getline(cin, b.author);
            break;
        case 3:
            cout << "Новий жанр: ";
            getline(cin, b.genre);
            break;
        case 4:
            cout << "Новий рік: ";
            while (!(cin >> b.year)) {
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введіть число: ";
            }
            break;
        case 5:
            cout << "Нова ціна: ";
            while (!(cin >> b.price)) {
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введіть число: ";
            }
            break;
        case 6:
            cout << "Нова наявність (так/ні): ";
            getline(cin >> ws, b.availability);
            break;
        default:
            cout << "Невідома опція.\n";
            return;
    }

    cout << "\nКартку успішно змінено!\n";
}

void EditProductCard(int &amount, string name[], string description[], double price[], string availability[])
{
    if (amount == 0) {
        cout << "Немає карток для редагування.\n";
        return;
    }

    cout << "\n-- Редагування картки товару --\n";
    cout << "Введіть номер книги (1 - " << amount << "): ";

    int bookNumber;
    cin >> bookNumber;

    int idx = bookNumber - 1;
    if (idx < 0 || idx >= amount)
    {
        cout << "Картка з таким номером не існує.\n";
        return;
    }

    cout << "\nПоточні дані:\n";
    cout << "1) Назва: " << name[idx] << endl;
    cout << "2) Опис: " << description[idx] << endl;
    cout << "3) Ціна: " << price[idx] << endl;
    cout << "4) Наявність: " << availability[idx] << endl;

    cout << "\nЩо бажаєте змінити?\n";
    cout << "1 - Назву\n";
    cout << "2 - Опис\n";
    cout << "3 - Ціну\n";
    cout << "4 - Наявність\n";
    cout << "Оберіть опцію: ";

    int option;
    cin >> option;

    cin.ignore(); // очищення буфера

    switch (option)
    {
    case 1:
        cout << "Нова назва: ";
        getline(cin, name[idx]);
        break;
    case 2:
        cout << "Новий опис: ";
        getline(cin, description[idx]);
        break;
    case 3:
        cout << "Нова ціна: ";
        cin >> price[idx];
        break;
    case 4:
        cout << "Нова наявність (Так/Ні): ";
        getline(cin, availability[idx]);
        break;
    default:
        cout << "Невідома опція.\n";
        return;
    }

    cout << "\nКартку успішно змінено!\n";
}

