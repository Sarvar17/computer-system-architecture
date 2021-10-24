//------------------------------------------------------------------------------
// procedure.cpp - содержит функции обработки для процедурных ЯП
//------------------------------------------------------------------------------
#include <cstring>
#include "procedure.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void In(procedure &p, std::ifstream &ifst) {
    ifst >> p.name >> p.tiobeRating >> p.releaseYear >> p.supportAbstractTypes;
}

// Случайный ввод параметров процедурного ЯП
void InRnd(procedure &p) {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        p.name[i] = char('a' + Random());
    }
    p.name[MAX_NAME_LEN - 1] = '\0';
    p.tiobeRating = Random() + Random() / 100.0;
    p.releaseYear = MIN_YEAR + Random();
    p.supportAbstractTypes = Random() % 2;
}

//------------------------------------------------------------------------------
// Вывод параметров процедурного ЯП в форматируемый поток
void Out(procedure &p, std::ofstream &ofst) {
    ofst << "It is Procedure language: name = "
         << p.name << " (" << p.tiobeRating << "% | " << p.releaseYear <<
         "), abstract types support = " <<
         (p.supportAbstractTypes ? "true" : "false") <<
         ". year / name.size() = " << YearDividedByNameLength(p) << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(procedure &p) {
    return p.releaseYear / double(strlen(p.name));
}
