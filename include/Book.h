#pragma once
#include <string>

struct Book
{
    std::string title;                     // Назва
    std::string author;                    // Автор
    std::string genre;                     // Жанр
    int year;                         // Рік видання
    double price;                     // Ціна
    std::string availability;              // Наявність: "так"/"ні"
};