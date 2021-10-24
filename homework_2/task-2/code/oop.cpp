//------------------------------------------------------------------------------
// oop.cpp - содержит функции обработки для объектно-ориентированных ЯП
//-----------------------------------------------------------------------------

#include <cstring>
#include "oop.h"
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void In(oop &o, std::ifstream &ifst) {
    int inheritance;
    ifst >> o.name >> o.tiobeRating >> o.releaseYear >> inheritance;
    if (inheritance == 0) {
        o.inhType = oop::inheritance::SINGLE;
    } else if (inheritance == 1) {
        o.inhType = oop::inheritance::MULTIPLE;
    } else {
        o.inhType = oop::inheritance::INTERFACE;
    }
}

// Случайный ввод параметров объектно-ориентированного ЯП
void InRnd(oop &o) {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        o.name[i] = char('a' + Random());
    }
    o.name[MAX_NAME_LEN - 1] = '\0';
    o.tiobeRating = Random() + Random() / 100.0;
    o.releaseYear = MIN_YEAR + Random();
    int inheritance = Random() % 3;
    if (inheritance == 0) {
        o.inhType = oop::inheritance::SINGLE;
    } else if (inheritance == 1) {
        o.inhType = oop::inheritance::MULTIPLE;
    } else {
        o.inhType = oop::inheritance::INTERFACE;
    }
}

//------------------------------------------------------------------------------
// Вывод параметров объектно-ориентированного ЯП в форматируемый поток
void Out(oop &o, std::ofstream &ofst) {
    ofst << "It is Object-oriented language: name = "
         << o.name << " (" << o.tiobeRating << "% | " << o.releaseYear <<
         "), inheritance = " <<
         (o.inhType == 0 ? "SINGLE" : (o.inhType == 1 ? "MULTIPLE" : "INTERFACE")) <<
         ". year / name.size() = " << YearDividedByNameLength(o) << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(oop &o) {
    return o.releaseYear / double(strlen(o.name));
}
