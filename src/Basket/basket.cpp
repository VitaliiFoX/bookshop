#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "../../include/Basket.h"

using namespace std;

const int MAX_BOOKS = 100;

// Функція для виведення списку книжок у кошику
void showCart(vector<Basket>& basket) {
    int count = (int)basket.size();
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

        cout << i + 1 << "\t"
             << basket[i].book.title << "\t\t"
             << basket[i].book.price << "\t"
             << basket[i].quantity << "\t\t"
             << sum << "\n";
    }

    cout << "-----------------------------------------------\n";
    cout << "Загальна сума: " << total << " грн\n";
}

// Додати книгу до кошика
void addToCart(vector<Basket>& basket, vector<Book>& books) {
    int count = (int)basket.size();
    if (count >= MAX_BOOKS) {
        cout << "Кошик переповнений!\n";
        return;
    }

    cout << "Введіть назву книги: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка перед getline
    string title;
    getline(cin, title);

    cout << "Введіть кількість книжок: ";
    int qnty;
    cin >> qnty;

    if (qnty <= 0) {
        cout << "Кількість має бути > 0.\n";
        return;
    }

    bool found = false;

    for (const auto& book : books) {
        if (book.title.find(title) != string::npos) {
            // якщо така книга вже є у кошику — збільшити кількість
            bool merged = false;
            for (auto& item : basket) {
                if (item.book.title == book.title) {
                    item.quantity += qnty;
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                if ((int)basket.size() >= MAX_BOOKS) {
                    cout << "Кошик переповнений!\n";
                    return;
                }
                basket.push_back(Basket{book, qnty});
            }

            found = true;
            break; // додали перший збіг і виходимо
        }
    }

    if (!found) {
        cout << "Книгу не знайдено.\n";
    } else {
        cout << "Додано до кошика.\n";
    }
}

void removeFromCart(vector<Basket>& basket) {
    int count = (int)basket.size();
    if (count == 0) {
        cout << "Кошик порожній. Немає що видаляти.\n";
        return;
    }

    showCart(basket);

    cout << "Введіть номер книги для видалення: ";
    int index;
    cin >> index;

    if (index < 1 || index > (int)basket.size()) {
        cout << "Невірний номер!\n";
        return;
    }

    basket.erase(basket.begin() + (index - 1));
    cout << "Книгу успішно видалено з кошика.\n";
}

void showBasket(vector<Basket>& basket, vector<Book>& books) {
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
