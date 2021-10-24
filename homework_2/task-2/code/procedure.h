#ifndef __procedure__
#define __procedure__

//------------------------------------------------------------------------------
// procedure.h - содержит описание функционального ЯП
//------------------------------------------------------------------------------

#include <fstream>
#include "constants.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// процедурный ЯП
struct procedure {
    // имя, ограничимся лимитом для упрощения архитектуры
    char name[MAX_NAME_LEN];
    // год создания языка
    int releaseYear;
    // популярность в процентах (TIOBE)
    double tiobeRating;
    // флаг поддержки абстрактных типов данных
    bool supportAbstractTypes;
};

// Ввод параметров процедурного ЯП из файла
void In(procedure &p, std::ifstream &ifst);

// Случайный ввод параметров процедурного ЯП
void InRnd(procedure &p);

// Вывод параметров процедурного ЯП в форматируемый поток
void Out(procedure &p, std::ofstream &ofst);

// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(procedure &p);

#endif //__procedure__
