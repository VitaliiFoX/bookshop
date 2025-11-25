#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ===== Структура для введення даних =====
struct UserInput {
    string email;
    string password;
};

// Максимальна кількість користувачів
const int MAX_USERS = 100;
const int MAX_ORDERS = 10;

// "База даних" користувачів
string userEmailDatabase[MAX_USERS] = {"admin@gmail.com", "test@ukr.net"};
string userPasswordDatabase[MAX_USERS] = {"admin123", "123456"};

// Історія замовлень
string orderHistory[MAX_USERS][MAX_ORDERS];
int orderCount[MAX_USERS] = {0, 2};

int currentUserCount = 2;

// ===== ФУНКЦІЯ ОЧИЩЕННЯ ПРОБІЛІВ =====
string trim(const string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// ===== Ввід користувача =====
UserInput getInput() {
    UserInput input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n   Реєстрація нового користувача    \n";
    cout << "Введіть ваш e-mail: ";
    getline(cin, input.email);
    input.email = trim(input.email);

    cout << "Введіть ваш пароль (мін. 6 символів): ";
    getline(cin, input.password);

    return input;
}

// ===== Реєстрація =====
int processRegistration(UserInput data) {
    if (data.email.find('@') == string::npos) return 1;
    if (data.password.length() < 6) return 2;

    for (int i = 0; i < currentUserCount; ++i)
        if (userEmailDatabase[i] == data.email) return 3;

    if (currentUserCount >= MAX_USERS) return 4;

    userEmailDatabase[currentUserCount] = data.email;
    userPasswordDatabase[currentUserCount] = data.password;
    currentUserCount++;
    return 0;
}

// ===== Вивід результату =====
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

// ===== ЛОГІН З TRIM =====
int login() {
    string email, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n    Вхід у систему    \n";
    cout << "E-mail: ";
    getline(cin, email);
    email = trim(email);

    cout << "Пароль: ";
    getline(cin, password);
    password = trim(password);

    for (int i = 0; i < currentUserCount; ++i) {
        if (userEmailDatabase[i] == email && userPasswordDatabase[i] == password)
            return i;
    }
    return -1;
}

// ===== Особистий кабінет =====
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

// ===== Меню =====
void showUserMenu() {
    int option;
    do {
        cout << "\n======= МЕНЮ =======\n";
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
                personalCabinet(userIndex);
            else
                cout << " Невірний e-mail або пароль!\n";
        }
    } while (option != 0);
}

// ===== main() =====
int main() {
    showUserMenu();
    return 0;
}
