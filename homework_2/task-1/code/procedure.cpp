//------------------------------------------------------------------------------
// procedure.cpp - содержит функции обработки для процедурных ЯП
//------------------------------------------------------------------------------

#include "procedure.h"

//------------------------------------------------------------------------------
// Ввод параметров ЯП из потока
void procedure::In(std::ifstream& ifst) {
    ifst >> this->name >> this->tiobeRating >> this->releaseYear >> this->supportAbstractTypes;
}

// Случайный ввод параметров процедурного ЯП
procedure* procedure::InRnd() {
    for (size_t i = 0; i < MAX_NAME_LEN; ++i) {
        this->name[i] = char('a' + Random());
    }
    this->name[MAX_NAME_LEN - 1] = '\0';
    this->tiobeRating = Random() + Random() / 100.0;
    this->releaseYear = MIN_YEAR + Random();
    this->supportAbstractTypes = Random() % 2;

    return this;
}

//------------------------------------------------------------------------------
// Вывод параметров процедурного ЯП в форматируемый поток
void procedure::Out(std::ofstream& ofst) {
    ofst << "It is Procedure language: name = "
        << this->name << " (" << this->tiobeRating << "% | " << this->releaseYear <<
        "), abstract types support = " <<
        (this->supportAbstractTypes ? "true" : "false") <<
        ". year / name.size() = " << this->YearDividedByNameLength() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double procedure::YearDividedByNameLength() {
    return this->releaseYear / double(strlen(this->name));
}