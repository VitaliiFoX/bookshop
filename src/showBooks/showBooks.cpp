#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "../../include/Book.h"
using namespace std;

/*
    Use case: "Перегляд книжок"
    База на масивах (без STL-контейнерів), як у твоїх прикладах.
    Модулі: меню каталогу, перегляд/пошук/фільтр/сортування + спрощена реєстрація.
*/

// ---------------------- Константи та структури ----------------------

const int MAX_BOOKS = 1000;            // Макс. кількість книжок
const int MAX_USERS = 100;            // Макс. кількість користувачів

// ---------------------- "База даних" ----------------------

int bookCount = 0;                    // Поточна к-ть книжок

// ---------------------- Прототипи ----------------------

void SeedBooks();                                                         // Заповнити каталог демо-даними
void ShowBooksMenu();                                                      // Показати меню
void ViewAllBooks(vector<Book> &books);                                                      // Перегляд усього каталогу
void SearchBooks(vector<Book> &books);                                                       // Пошук по назві/автору
void PrintBook(const Book& b, int index);                              // Друк 1 книжки
void showDetailedBooksMenu(vector<Book> &books);


// ---------------------- main ----------------------

void showDetailedBooksMenu(vector<Book> &books) {
    setlocale(LC_CTYPE, "ukr");                                           // Українська локаль (консоль)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);                                                        // Підготуємо демо-каталог

    while (true)
    {
        ShowBooksMenu();
        int opt;
        cin >> opt;

        switch (opt)
        {
        case 1:
            ViewAllBooks(books);
            break;
        case 2:
            SearchBooks(books);
            break;
        case 0:
            cout << "До побачення!\n";
            return;
        default:
            cout << "Невірна опція!\n";
            break;
        }
    }
}

// ---------------------- Ініціалізація книжок ----------------------

void SeedBooks(vector<Book> &books)
{
    // Можеш вільно міняти/додавати
    books.push_back({"Тіні забутих предків", "Михайло Коцюбинський", "Класика", 1911, 199.0, "так"});
    books.push_back({"Кобзар", "Тарас Шевченко", "Поезія", 1840, 249.0, "так"});
    books.push_back({"Сто років самотності", "Г. Гарсія Маркес", "Роман", 1967, 299.0, "ні"});
    books.push_back({"Майстер і Маргарита", "М. Булгаков", "Роман", 1967, 279.0, "так"});
    books.push_back({"1984", "Джордж Орвелл", "Антиутопія", 1949, 219.0, "так"});
    books.push_back({"Фінансист", "Теодор Драйзер", "Роман", 1912, 189.0, "ні"});
    books.push_back({"Пізнай себе", "Д. Карнегі", "Нон-фікшн", 1956, 259.0, "так"});
    books.push_back({"Чистий код", "Роберт Мартін", "IT", 2008, 849.0, "так"});
    books.push_back({"Алгоритми", "Кормен/Лайзерсон/Рівест/Штайн", "IT", 2009, 999.0, "ні"});
    books.push_back({"Мистецтво війни", "Сунь-цзи", "Філософія", -500, 149.0, "так"}); // приблизний рік
    // bookCount = 10;
}

// ---------------------- Меню ----------------------

void ShowBooksMenu()
{
    cout << "\n================= КАТАЛОГ КНИЖОК =================\n";
    cout << "1) Переглянути всі книжки\n";
    cout << "2) Пошук книжок (назва/автор)\n";
    cout << "0) Вихід\n";
    cout << "Ваш вибір: ";
}

// ---------------------- Перегляд ----------------------

void PrintBook(const Book& b, int index)
{
    cout << "\nКнига #" << index + 1 << ":\n";
    cout << "Назва: " << b.title << "\n";
    cout << "Автор: " << b.author << "\n";
    cout << "Жанр: " << b.genre << "\n";
    cout << "Рік: " << b.year << "\n";
    cout << "Ціна: " << b.price << "\n";
    cout << "Наявність: " << b.availability << "\n";
}

void ViewAllBooks(vector<Book> &books)
{
    bookCount = books.size();
    if (bookCount == 0)
    {
        cout << "Каталог порожній!\n";
        return;
    }

    cout << "\n--- Увесь каталог (" << bookCount << ") ---\n";
    for (int i = 0; i < bookCount; ++i)
    {
        PrintBook(books[i], i);
    }
    cout << "\nКінець списку.\n";
}

static const pair<string, string> uk_pairs[] = {
    {"А", "а"}, {"Б", "б"}, {"В", "в"}, {"Г", "г"}, {"Ґ", "ґ"},
    {"Д", "д"}, {"Е", "е"}, {"Є", "є"}, {"Ж", "ж"}, {"З", "з"},
    {"И", "и"}, {"І", "і"}, {"Ї", "ї"}, {"Й", "й"}, {"К", "к"},
    {"Л", "л"}, {"М", "м"}, {"Н", "н"}, {"О", "о"}, {"П", "п"},
    {"Р", "р"}, {"С", "с"}, {"Т", "т"}, {"У", "у"}, {"Ф", "ф"},
    {"Х", "х"}, {"Ц", "ц"}, {"Ч", "ч"}, {"Ш", "ш"}, {"Щ", "щ"},
    {"Ь", "ь"}, {"Ю", "ю"}, {"Я", "я"}
};

string toLowerStr(const string& s)
{
    string out;
    size_t i = 0;

    while (i < s.size())
    {
        unsigned char c = s[i];

        // ---------- 1) LATIN ASCII ----------
        if (c < 128)
        {
            out += tolower(c);
            i++;
        }
        else
        {
            // ---------- 2) UTF-8 Ukrainian letter (2 bytes) ----------
            // Беремо повний мультибайтовий символ
            string utf8char;

            if ((c & 0xE0) == 0xC0 && i + 1 < s.size())
            {
                utf8char = s.substr(i, 2);
                i += 2;
            }
            else
            {
                // fallback: просто копіюємо
                out += s[i];
                i++;
                continue;
            }

            // Шукаємо відповідність у таблиці великих літер
            bool matched = false;
            for (auto& p : uk_pairs)
            {
                if (utf8char == p.first)
                {
                    out += p.second;
                    matched = true;
                    break;
                }
            }

            if (!matched)
            {
                // Якщо літера вже мала або неукраїнська — просто копіюємо
                out += utf8char;
            }
        }
    }

    return out;
}

// ---------------------- Пошук ----------------------

void SearchBooks(vector<Book> &books)
{
    bookCount = books.size();
    if (bookCount == 0)
    {
        cout << "Каталог порожній!\n";
        return;
    }

    cout << "Пошук за:\n";
    cout << "1) Назвою\n";
    cout << "2) Автором\n";
    cout << "Ваш вибір: ";
    int opt;
    cin >> opt;

    string q;
    if (opt == 1)
    {
        cout << "Введіть частину назви: ";
        cin >> q;
        cout << "\nРезультати пошуку:\n";
        int hits = 0;
        for (int i = 0; i < bookCount; ++i)
        {
            if (toLowerStr(books[i].title).find(toLowerStr(q)) != string::npos)
            {
                PrintBook(books[i], i);
                ++hits;
            }
        }
        if (hits == 0) cout << "Нічого не знайдено.\n";
    }
    else if (opt == 2)
    {
        cout << "Введіть частину імені автора: ";
        cin >> q;
        cout << "\nРезультати пошуку:\n";
        int hits = 0;
        for (int i = 0; i < bookCount; ++i)
        {
        if (toLowerStr(books[i].author).find(toLowerStr(q)) != string::npos)
            {
                PrintBook(books[i], i);
                ++hits;
            }
        }
        if (hits == 0) cout << "Нічого не знайдено.\n";
    }
    else
    {
        cout << "Невірна опція!\n";
    }
}
