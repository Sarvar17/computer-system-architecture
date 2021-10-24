//------------------------------------------------------------------------------
// oop.cpp - содержит функции обработки для объектно-ориентированных ЯП
//------------------------------------------------------------------------------

#include "oop.h"
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void oop::In(std::ifstream& ifst) {
    int inheritance;
    ifst >> this->name >> this->tiobeRating >> this->releaseYear >> inheritance;
    if (inheritance == 0) {
        this->inhType = oop::inheritance::SINGLE;
    }
    else if (inheritance == 1) {
        this->inhType = oop::inheritance::MULTIPLE;
    }
    else {
        this->inhType = oop::inheritance::INTERFACE;
    }
}

// Случайный ввод параметров объектно-ориентированного ЯП
void oop::InRnd() {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        this->name[i] = char('a' + Random());
    }
    this->name[MAX_NAME_LEN - 1] = '\0';
    this->tiobeRating = Random() + Random() / 100.0;
    this->releaseYear = MIN_YEAR + Random();
    int inheritance = Random() % 3;
    if (inheritance == 0) {
        this->inhType = oop::inheritance::SINGLE;
    }
    else if (inheritance == 1) {
        this->inhType = oop::inheritance::MULTIPLE;
    }
    else {
        this->inhType = oop::inheritance::INTERFACE;
    }
}

//------------------------------------------------------------------------------
// Вывод параметров объектно-ориентированного ЯП в форматируемый поток
void oop::Out(std::ofstream & ofst) {
    ofst << "It is Object-oriented language: name = "
        << this->name << " (" << this->tiobeRating << "% | " << this->releaseYear <<
        "), inheritance = " <<
        (this->inhType == 0 ? "SINGLE" : (o.inhType == 1 ? "MULTIPLE" : "INTERFACE")) <<
        ". year / name.size() = " << this->YearDividedByNameLength() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double oop::YearDividedByNameLength() {
    return this->releaseYear / double(strlen(this->name));
}