//------------------------------------------------------------------------------
// container.cpp - содержит функции обработки контейнера
//------------------------------------------------------------------------------

#include "container.h"

//------------------------------------------------------------------------------
// Инициализация контейнера
void Init(container &c) {
    c.len = 0;
}

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
void Clear(container &c) {
    for (int i = 0; i < c.len; i++) {
        delete c.cont[i];
    }
    c.len = 0;
}

//------------------------------------------------------------------------------
// Ввод содержимого контейнера из указанного потока
void In(container &c, std::ifstream &ifst) {
    while (!ifst.eof()) {
        if ((c.cont[c.len] = In(ifst)) != 0) {
            c.len++;
        }
    }
}

//------------------------------------------------------------------------------
// Случайный ввод содержимого контейнера
void InRnd(container &c, int size) {
    while (c.len < size) {
        if ((c.cont[c.len] = InRnd()) != nullptr) {
            c.len++;
        }
    }
}

//------------------------------------------------------------------------------
// Вывод содержимого контейнера в указанный поток
void Out(container &c, std::ofstream &ofst) {
    ofst << "Container contains " << c.len << " elements.\n";
    for (int i = 0; i < c.len; i++) {
        ofst << i << ": ";
        Out(*(c.cont[i]), ofst);
    }
}

// Сортировка контейнера методом Straight Selection
void sort(container &c) {
    int i = 0, j, k;
    language *temp;
    while (i < c.len) {
        k = i;
        for (j = i + 1; j < c.len; j++) {
            if (YearDividedByNameLength(*c.cont[j]) > YearDividedByNameLength(*c.cont[k])) {
                k = j;
            }
        }
        temp = c.cont[i];
        c.cont[i] = c.cont[k];
        c.cont[k] = temp;
        i++;
    }
}
