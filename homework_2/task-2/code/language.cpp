//------------------------------------------------------------------------------
// language.cpp - содержит процедуры связанные с обработкой обобщенного ЯП
// и создания одной из альтернатив (ООП/функциональный/процедурный)
//------------------------------------------------------------------------------

#include "language.h"

//------------------------------------------------------------------------------
// Ввод параметров обобщенного ЯП из файла
language* language::In(std::ifstream& ifst) {
    char type[MAX_NAME_LEN];
    ifst >> type;
    language* lang;

    if (!strcmp(type, "procedure")) {
        dynamic_cast<procedure>(lang).In(ifst);
    }
    else if (!strcmp(type, "functional")) {
        dynamic_cast<functional>(lang).In(ifst);
    }
    else if (!strcmp(type, "oop")) {
        dynamic_cast<oop>(lang).In(ifst);
    }
    else {
        std::cout << "ERROR: Wrong language type " << type;
        exit(1);
    }

    return lang;
}

// Случайный ввод обобщенного ЯП
language* language::InRnd() {
    auto type = rand() % 3;
    language* lang;
    if (type == 0) {
        dynamic_cast<procedure>(lang).InRnd();
        return &lang;
    }
    else if (type == 2) {
        dynamic_cast<functional>(lang).InRnd();
    }
    else {
        dynamic_cast<oop>(lang).InRnd();
    }

    retutn lang;
}

//------------------------------------------------------------------------------
// Вывод параметров текущего ЯП в поток
void language::Out(std::ofstream& ofst) {
    if (dynamic_cast<procedure>(this) != nullptr) {
        dynamic_cast<procedure>(this).Out(ofst);
    }
    else if (dynamic_cast<functional>(this) != nullptr) {
        dynamic_cast<functional>(this).Out(ofst);
    }
    else {
        dynamic_cast<oop>(this).Out(ofst);
    }
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double language::YearDividedByNameLength() {
    if (dynamic_cast<procedure>(this) != nullptr) {
        return dynamic_cast<procedure>(this).YearDividedByNameLength();
    }
    else if (dynamic_cast<functional>(this) != nullptr) {
        return dynamic_cast<functional>(this).YearDividedByNameLength();
    }
    else {
        return dynamic_cast<oop>(this).YearDividedByNameLength();
    }
}