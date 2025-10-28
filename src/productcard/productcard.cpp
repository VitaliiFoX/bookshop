#include <iostream>
#include <string>


using namespace std;

void ProductCardModule(int &amount, string name[], string description[], double price[], string availability[]);
void CreateProductCard(int &amount, string name[], string description[], double price[], string availability[]);
void CheckProductCard(int &amount, string name[], string description[], double price[], string availability[]);
void RunApplication();

int main()
{
    setlocale(LC_CTYPE, "ukr");
    RunApplication();
    return 0;
}

void RunApplication()
{
    string name[50];
    string description[50];
    double price[50];
    string availability[50];
    int amount = 0;

    ProductCardModule(amount, name, description, price, availability);
}

void ProductCardModule(int &amount, string name[], string description[], double price[], string availability[])
{
    int option;
    do
    {
        cout << "\nВиберіть потрібний варіант\n";
        cout << "1) Створити картку товару\n";
        cout << "2) Переглянути картку товару\n";
        cout << "Оберіть опцію: ";
        cin >> option;

        switch (option)
        {
        case 1:
            CreateProductCard(amount, name, description, price, availability);
            break;
        case 2:
            CheckProductCard(amount, name, description, price, availability);
            break;
        default:
            cout << "Невідома опція.\n";
            break;
        }
    } while (option != 3);
}

void CreateProductCard(int &amount, string name[], string description[], double price[], string availability[])
{
    cout << "\n-- Створення картки --\n";

    cout << "Напишіть назву книги: ";
    getline(cin >> ws, name[amount]); 

    cout << "Напишіть опис книги: ";
    getline(cin >> ws, description[amount]);

    cout << "Введіть ціну книги: ";
    cin >> price[amount];

    cout << "Вкажіть наявність книги (Так/Ні): ";
    getline(cin >> ws, availability[amount]);

    cout << "Номер книги : " << amount + 1 << "\n";
    amount++;

    cout << "\nКартка товару створена успішно!\n";
}

void CheckProductCard(int &amount, string name[], string description[], double price[], string availability[])
{
    if (amount == 0) {
        cout << "Немає карток для перегляду.\n";
        return;
    }

    cout << "Перегляд картки \n";
    cout << "Напишіть номер книги (1 - " << amount << "): ";
    int bookNumber;
    cin >> bookNumber;

    int idx = bookNumber - 1;
    if (idx < 0 || idx >= amount) 
    {
        cout << "Картка з таким номером не існує.\n";
        return;
    }

    cout << "Назва книги: " << name[idx] << endl;
    cout << "Опис книги: " << description[idx] << endl;
    cout << "Ціна книги: " << price[idx] << endl;
    cout << "Чи наявна книга: " << availability[idx] << endl;
}
