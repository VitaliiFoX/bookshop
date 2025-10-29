#include <iostream>
#include "user/user.h"
#include "showBooks/showBooks.h"
#include "productcard/productcard.h"
#include "Basket/basket.h"

void showServiceMenu() {
    cout << "\n=== Меню книжкового магазину ===\n";
    cout << "1. Показати книжки\n";
    cout << "2. Показати кошик\n";
    cout << "3. Показати картку товару\n";
    cout << "Ваш вибір: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            showDetailedBooksMenu();
            break;
        case 2:
            showBasket();
            break;
        case 3:
            RunApplication();
            break;
        default:
            cout << "Неправильний вибір!\n";
    }
}

int main() {
    showUserMenu();
    while (true) {
        showServiceMenu();
    }
}