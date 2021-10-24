//------------------------------------------------------------------------------
// functional.cpp - содержит функции обработки для процедурных ЯП
//------------------------------------------------------------------------------

#include "functional.h"
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void functional::In(std::ifstream& ifst) {
    ifst >> this->name >> this->tiobeRating >> this->releaseYear;
    bool isDynamicTyping, supportLazyCalculations;
    ifst >> isDynamicTyping >> supportLazyCalculations;
    this->t = isDynamicTyping ? functional::typing::DYNAMIC : functional::typing::STATIC;
    this->supportLazyCalculations = supportLazyCalculations;
}

// Случайный ввод параметров процедурного ЯП
void functional::InRnd() {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        this->name[i] = char('a' + Random());
    }
    this->name[MAX_NAME_LEN - 1] = '\0';
    this->tiobeRating = Random() + Random() / 100.0;
    this->releaseYear = MIN_YEAR + Random();
    this->t = Random() % 2 ? functional::typing::DYNAMIC : functional::typing::STATIC;
    this->supportLazyCalculations = Random() % 2;
}

//------------------------------------------------------------------------------
// Вывод параметров процедурного ЯП в форматируемый поток
void functional::Out(std::ofstream& ofst) {
    ofst << "It is Functional language: name = "
        << this->name << " (" << this->tiobeRating << "% | " << this->releaseYear <<
        "), typing = " <<
        (this->t ? "DYNAMIC" : "STATIC") <<
        ", lazy calculations = " << (this->supportLazyCalculations ? "true" : "false") <<
        ". year / name.size() = " << this->YearDividedByNameLength() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double functional::YearDividedByNameLength() {
    return this->releaseYear / double(strlen(this->name));
}