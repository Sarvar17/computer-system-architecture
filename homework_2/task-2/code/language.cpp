//------------------------------------------------------------------------------
// language.cpp - содержит процедуры связанные с обработкой обобщенного ЯП
// и создания одной из альтернатив (ООП/функциональный/процедурный)
//------------------------------------------------------------------------------
#include <cstring>
#include "language.h"

//------------------------------------------------------------------------------
// Ввод параметров обобщенного ЯП из файла
language* In(std::ifstream &ifst) {
    language *lang;
    char type[MAX_NAME_LEN];
    ifst >> type;
    if (!strcmp(type, "procedure")) {
        lang = new language;
        lang->k = language::PROCEDURE;
        In(lang->p, ifst);
    } else if (!strcmp(type, "functional")) {
        lang = new language;
        lang->k = language::FUNCTIONAL;
        In(lang->f, ifst);
    } else if (!strcmp(type, "oop")) {
        lang = new language;
        lang->k = language::OOP;
        In(lang->o, ifst);
    } else {
        std::cout << "ERROR: Wrong language type " << type;
        exit(1);
    }
    return lang;
}

// Случайный ввод обобщенного ЯП
language *InRnd() {
    language *lang;
    auto type = rand() % 3;
    if (type == 0) {
        lang = new language;
        lang->k = language::PROCEDURE;
        InRnd(lang->p);
    } else if (type == 2) {
        lang = new language;
        lang->k = language::FUNCTIONAL;
        InRnd(lang->f);
    } else {
        lang = new language;
        lang->k = language::OOP;
        InRnd(lang->o);
    }
    return lang;
}

//------------------------------------------------------------------------------
// Вывод параметров текущего ЯП в поток
void Out(language &lang, std::ofstream &ofst) {
    switch (lang.k) {
        case language::PROCEDURE:
            Out(lang.p, ofst);
            break;
        case language::FUNCTIONAL:
            Out(lang.f, ofst);
            break;
        case language::OOP:
            Out(lang.o, ofst);
            break;
        default:
            ofst << "Incorrect language type!\n";
    }
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(language &lang) {
    switch (lang.k) {
        case language::PROCEDURE:
            return YearDividedByNameLength(lang.p);
        case language::FUNCTIONAL:
            return YearDividedByNameLength(lang.f);
        case language::OOP:
            return YearDividedByNameLength(lang.o);
        default:
            return 0;
    }
}
