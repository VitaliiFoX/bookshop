#include <iostream>
#include <string>
#include <limits> // для cin.ignore()
#include "../../include/UserInput.h"

using namespace std;

// Максимальна кількість користувачів
const int MAX_USERS = 100;
const int MAX_ORDERS = 10; // максимум замовлень для кожного користувача

// "База даних" e-mail користувачів
string userEmailDatabase[MAX_USERS] = {"admin@gmail.com", "test@ukr.net"};
string userPasswordDatabase[MAX_USERS] = {"admin123", "123456"}; // паролі

// Історія замовлень кожного користувача
string orderHistory[MAX_USERS][MAX_ORDERS];
int orderCount[MAX_USERS] = {0, 2}; 

// Поточна кількість користувачів
int currentUserCount = 2;

// Ввід даних користувача
UserInput getInput() {
    UserInput input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n   Реєстрація нового користувача    \n";
    cout << "Введіть ваш e-mail: ";
    getline(cin, input.email);
    cout << "Введіть ваш пароль (мін. 6 символів): ";
    getline(cin, input.password);
    return input;
}

// Реєстрація користувача
int processRegistration(UserInput data) {
    if (data.email.find('@') == string::npos) return 1; // неправильний e-mail
    if (data.password.length() < 6) return 2;           // короткий пароль

    for (int i = 0; i < currentUserCount; ++i)
        if (userEmailDatabase[i] == data.email) return 3; 

    if (currentUserCount >= MAX_USERS) return 4; // переповнення

    // Додаємо користувача
    userEmailDatabase[currentUserCount] = data.email;
    userPasswordDatabase[currentUserCount] = data.password;
    currentUserCount++;
    return 0; // успіх
}

// Вивід результату реєстрації
void printResult(int code) {
    if (code == 0)
        cout << "\n Реєстрація успішна!\n";
    else {
        cout << "\n Помилка реєстрації:\n";
        switch (code) {
            case 1: cout << "Некоректний e-mail.\n"; break;
            case 2: cout << "Пароль занадто короткий.\n"; break;
            case 3: cout << "Такий користувач вже існує.\n"; break;
            case 4: cout << "База користувачів переповнена.\n"; break;
        }
    }
}

// Вхід у систему
int login() {
    string email, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n    Вхід у систему    \n";
    cout << "E-mail: ";
    getline(cin, email);
    cout << "Пароль: ";
    getline(cin, password);

    for (int i = 0; i < currentUserCount; ++i) {
        if (userEmailDatabase[i] == email && userPasswordDatabase[i] == password)
            return i; // повертаємо індекс користувача
    }
    return -1; // не знайдено
}

// Особистий кабінет (лише перегляд історії)
void personalCabinet(int userIndex) {
    cout << "\n   👤 Особистий кабінет    \n";
    cout << "Ваш e-mail: " << userEmailDatabase[userIndex] << "\n";

    cout << "Історія замовлень:\n";
    if (orderCount[userIndex] == 0)
        cout << "  (Немає замовлень)\n";
    else {
        for (int i = 0; i < orderCount[userIndex]; ++i)
            cout << "  • " << orderHistory[userIndex][i] << "\n";
    }
}

// Меню
void showUserMenu() {
    int option;
    do {
        cout << "\n       МЕНЮ       \n";
        cout << "1. Зареєструвати нового користувача\n";
        cout << "2. Увійти в особистий кабінет\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> option;

        if (option == 1) {
            UserInput data = getInput();
            int status = processRegistration(data);
            printResult(status);
        } 
        else if (option == 2) {
            int userIndex = login();
            if (userIndex != -1)
            {
                personalCabinet(userIndex);
                break;
            }
            else
                cout << " Невірний e-mail або пароль!\n";
        }
    } while (option != 0);
}



