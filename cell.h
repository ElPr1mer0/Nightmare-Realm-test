#ifndef CELL_H
#define CELL_H


enum cell_status{ // перечесление возможных состояний ячейки поля
    null = - 1,
    cleared = 0, // клетка пустая
    blocked = 1, // заблокирована
    yellow = 2, // желтая клетка
    orange = 3,// оранжевая клетка
    red = 4 // красная клетка
};


class CELL{
public:
    cell_status status = null; // null - нет клетки
    int cell_i; // координаты клетки
    int cell_j;
};

#endif // CELL_H
