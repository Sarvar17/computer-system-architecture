#ifndef __language__
#define __language__

//------------------------------------------------------------------------------
// programming_language.h - содержит описание обобщающего языка программирования (ЯП),
//------------------------------------------------------------------------------

#include <iostream>

#include "procedure.h"
#include "oop.h"
#include "functional.h"

//------------------------------------------------------------------------------
// структура, обобщающая все имеющиеся ЯП
struct language {
    // значения ключей для каждого из видов ЯП
    enum key {PROCEDURE, OOP, FUNCTIONAL};
    key k; // ключ
    // используемые альтернативы
    union { // используем простейшую реализацию
        procedure p;
        oop o;
        functional f;
    };
};

// Ввод обобщенного ЯП
language *In(std::ifstream &ifdt);

// Случайный ввод обобщенного ЯП
language *InRnd();

// Вывод обобщенного ЯП
void Out(language &s, std::ofstream &ofst);

// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(language &s);

#endif
