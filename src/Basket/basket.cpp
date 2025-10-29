#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;

// Функція для виведення списку книжок у кошику
void showCart(string titles[], double prices[], int quantities[], int count) {
    if (count == 0) {
        cout << "Кошик порожній.\n";
        return;
    }

    double total = 0.0;
    cout << "=== Вміст кошика ===\n";
    cout << "№\tНазва книги\t\tЦіна\tКількість\tСума\n";
    cout << "-----------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        double sum = prices[i] * quantities[i];
        total += sum;
        cout << i + 1 << "\t" << titles[i] << "\t\t" 
             << prices[i] << "\t" << quantities[i] 
             << "\t\t" << sum << "\n";
    }

    cout << "-----------------------------------------------\n";
    cout << "Загальна сума: " << total << " грн\n";
}

// Додати книгу до кошика
void addToCart(string titles[], double prices[], int quantities[], int &count) {
    if (count >= MAX_BOOKS) {
        cout << "Кошик переповнений!\n";
        return;
    }

    cout << "Введіть назву книги: ";
    cin.ignore();
    getline(cin, titles[count]);

    cout << "Введіть ціну: ";
    cin >> prices[count];

    cout << "Введіть кількість: ";
    cin >> quantities[count];

    count++;
    cout << "Книгу додано до кошика!\n";
}

void showBasket() {
    string titles[MAX_BOOKS];
    double prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int count = 0;
    int choice;

    do {
        cout << "\n=== Меню книжкового магазину ===\n";
        cout << "1. Додати книгу до кошика\n";
        cout << "2. Переглянути кошик\n";
        cout << "3. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addToCart(titles, prices, quantities, count);
                break;
            case 2:
                showCart(titles, prices, quantities, count);
                break;
            case 3:
                cout << "Дякуємо за покупку!\n";
                break;
            default:
                cout << "Неправильний вибір!\n";
        }
    } while (choice != 3);
}