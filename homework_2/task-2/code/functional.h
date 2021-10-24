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
struct functional {
    // имя, ограничимся лимитом для упрощения архитектуры
    char name[MAX_NAME_LEN];
    // год создания языка
    int releaseYear;
    // популярность в процентах (TIOBE)
    double tiobeRating;
    // типизация: статическая, динамическая
    enum typing {STATIC, DYNAMIC};
    typing t;
    // поддержка «ленивых» вычислений
    bool supportLazyCalculations;
};

// Ввод параметров функционального ЯП из файла
void In(functional &f, std::ifstream &ifst);

// Случайный ввод параметров функционального ЯП
void InRnd(functional &f);

// Вывод параметров функционального ЯП в форматируемый поток
void Out(functional &f, std::ofstream &ofst);

// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(functional &f);

#endif //__functional__
