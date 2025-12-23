#include <iostream>
#include <string>
#include "../../include/Basket.h"
using namespace std;

const int MAX_BOOKS = 100;

// Функція для виведення списку книжок у кошику
void showCart(vector<Basket>& basket) {
    int count = basket.size();
    if (count == 0) {
        cout << "Кошик порожній.\n";
        return;
    }

    double total = 0.0;
    cout << "=== Вміст кошика ===\n";
    cout << "№\tНазва книги\t\tЦіна\tКількість\tСума\n";
    cout << "-----------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        double sum = basket[i].book.price * basket[i].quantity;
        total += sum;
        cout << i + 1 << "\t" << basket[i].book.title << "\t\t"
            << basket[i].book.price << "\t" << basket[i].quantity
            << "\t\t" << sum << "\n";
    }

    cout << "-----------------------------------------------\n";
    cout << "Загальна сума: " << total << " грн\n";
}

// Додати книгу до кошика
void addToCart(vector<Basket>& basket, vector<Book>& books) {
    int count = basket.size();
    if (count >= MAX_BOOKS) {
        cout << "Кошик переповнений!\n";
        return;
    }

    cout << "Введіть назву книги: ";
    cin.ignore();
    string title = "";
    getline(cin, title);

    cout << "Введіть кількість книжок: ";
    int qnty;
    cin >> qnty;

    for (auto book : books) {
        if (book.title.find(title) != string::npos) {
            basket.push_back({ book, qnty });
        }
    }
}

void removeFromCart(vector<Basket>& basket) {
    int count = basket.size();
    if (count == 0) {
        cout << "Кошик порожній. Немає що видаляти.\n";
        return;
    }
    showCart(vector<Basket> &basket);

    cout << "Введіть номер книги для видалення: ";
    int index;
    cin >> index;

    if (index < 1 || index > basket.size()) {
        cout << "Невірний номер!\n";
        return;

        basket.erase(basket.begin() + index - 1);

        cout << "Книгу успішно видалено з кошика.\n";
    }

    void showBasket(vector<Basket> &basket, vector<Book> &books) {
        int count = 0;
        int choice;

        do {
            cout << "\n=== Меню книжкового магазину ===\n";
            cout << "1. Додати книгу до кошика\n";
            cout << "2. Переглянути кошик\n";
            cout << "3. Видалити книгу з кошика\n";
            cout << "4. Вихід\n";
            cout << "Ваш вибір: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addToCart(basket, books);
                break;
            case 2:
                showCart(basket);
                break;
            case 3:
                removeFromCart(basket);
                break;
            case 4:
                cout << "Дякуємо за покупку!\n";
                break;
            default:
                cout << "Неправильний вибір!\n";
            }
        } while (choice != 4);
    }