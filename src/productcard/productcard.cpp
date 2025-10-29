// ===== main.cpp =====
#include <iostream>
#include <string>
#include <vector>
#include "../../include/Book.h"

using namespace std;

void ProductCardModule(vector<Book>& books);
void CreateProductCard(vector<Book>& books);
void CheckProductCard(const vector<Book>& books);
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
        cout << "3) Вихід\n";
        cout << "Оберіть опцію: ";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "Вихід...\n";
                break;
            default:
                cout << "Невідома опція.\n";
                break;
        }
    } while (option != 3);
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введіть ціле число для року: ";
    }

    cout << "Введіть ціну книги: ";
    while (!(cin >> b.price)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
