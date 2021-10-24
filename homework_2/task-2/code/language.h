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
// класс, обобщающая все имеющиеся ЯП
class language {
public:
    // Ввод обобщенного ЯП
    static language* In(std::ifstream& ifdt);

    // Случайный ввод обобщенного ЯП
    virtual language* InRnd();

    // Вывод обобщенного ЯП
    virtual void Out(std::ofstream& ofst);

    // Вычисление частного от деления года создания на количество
    // символов в названии (действительное число)
    virtual double YearDividedByNameLength();
};

#endif