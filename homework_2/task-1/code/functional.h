#ifndef __functional__
#define __functional__

//------------------------------------------------------------------------------
// functional.h - содержит описание функционального ЯП
//------------------------------------------------------------------------------

#include <fstream>
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// функциональный ЯП
class functional : public language {
public:
    // имя, ограничимся лимитом для упрощения архитектуры
    char name[MAX_NAME_LEN];
    // год создания языка
    int releaseYear;
    // популярность в процентах (TIOBE)
    double tiobeRating;
    // типизация: статическая, динамическая
    enum typing { STATIC, DYNAMIC };
    typing t;
    // поддержка «ленивых» вычислений
    bool supportLazyCalculations;

    // Ввод параметров функционального ЯП из файла
    virtual void In(std::ifstream& ifst);

    // Случайный ввод параметров функционального ЯП
    virtual void InRnd();

    // Вывод параметров функционального ЯП в форматируемый поток
    virtual void Out(std::ofstream& ofst);

    // Вычисление частного от деления года создания на количество
    // символов в названии (действительное число)
    virtual double YearDividedByNameLength();
};

#endif //__functional__