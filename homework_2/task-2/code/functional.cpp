//------------------------------------------------------------------------------
// functional.cpp - содержит функции обработки для процедурных ЯП
//------------------------------------------------------------------------------
#include <cstring>
#include "functional.h"
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void In(functional &p, std::ifstream &ifst) {
    ifst >> p.name >> p.tiobeRating >> p.releaseYear;
    bool isDynamicTyping, supportLazyCalculations;
    ifst >> isDynamicTyping >> supportLazyCalculations;
    p.t = isDynamicTyping ? functional::typing::DYNAMIC : functional::typing::STATIC;
    p.supportLazyCalculations = supportLazyCalculations;
}

// Случайный ввод параметров процедурного ЯП
void InRnd(functional &f) {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        f.name[i] = char('a' + Random());
    }
    f.name[MAX_NAME_LEN - 1] = '\0';
    f.tiobeRating = Random() + Random() / 100.0;
    f.releaseYear = MIN_YEAR + Random();
    f.t = Random() % 2 ? functional::typing::DYNAMIC : functional::typing::STATIC;
    f.supportLazyCalculations = Random() % 2;
}

//------------------------------------------------------------------------------
// Вывод параметров процедурного ЯП в форматируемый поток
void Out(functional &f, std::ofstream &ofst) {
    ofst << "It is Functional language: name = "
         << f.name << " (" << f.tiobeRating << "% | " << f.releaseYear <<
         "), typing = " <<
         (f.t ? "DYNAMIC" : "STATIC") <<
         ", lazy calculations = " << (f.supportLazyCalculations ? "true" : "false") <<
         ". year / name.size() = " << YearDividedByNameLength(f) << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(functional &f) {
    return f.releaseYear / double(strlen(f.name));
}
