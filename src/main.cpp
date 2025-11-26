#include <iostream>
#include "../include/Book.h"
#include "../include/Basket.h"
#include "../include/UserInput.h"
#include "user/user.h"
#include "showBooks/showBooks.h"
#include "productcard/productcard.h"
#include "Basket/basket.h"

vector<Book> books;
vector<Basket> basket;

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
            showDetailedBooksMenu(books);
            break;
        case 2:
            showBasket(basket, books);
            break;
        case 3:
            ProductCardModule(books);
            break;
        default:
            cout << "Неправильний вибір!\n";
    }
}

int main() {
    SeedBooks(books);
    showUserMenu();
    while (true) {
        showServiceMenu();
    }
}