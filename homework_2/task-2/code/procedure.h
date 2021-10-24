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
class procedure : public language {
public:
    // имя, ограничимся лимитом для упрощения архитектуры
    char name[MAX_NAME_LEN];
    // год создания языка
    int releaseYear;
    // популярность в процентах (TIOBE)
    double tiobeRating;
    // флаг поддержки абстрактных типов данных
    bool supportAbstractTypes;

    // Ввод параметров процедурного ЯП из файла
    virtual void In(std::ifstream& ifst);

    // Случайный ввод параметров процедурного ЯП
    virtual procedure* InRnd();

    // Вывод параметров процедурного ЯП в форматируемый поток
    virtual void Out(std::ofstream& ofst);

    // Вычисление частного от деления года создания на количество
    // символов в названии (действительное число)
    virtual double YearDividedByNameLength();
};

#endif //__procedure__