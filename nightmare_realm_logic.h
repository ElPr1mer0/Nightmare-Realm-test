#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>

class QPushButton;
class QVBoxLayout;
class NIGHTMARE_REALM_STYLE;
class CELL;

class NIGHTMARE_REALM_LOGIC : public QWidget{
    Q_OBJECT
private:
    const int GAME_POLE_SIZE  = 5; //размер игрового поля 5 на 5
    const int max_color_amount = 5; // кол-во ячеек каждого цвета на поле

    int yellow_amount; // счетчики кол-ва ячеек при заполнении игрового поля
    int orange_amount;
    int red_amount;

    int but_i; // для сохранения координат кнопки
    int but_j;

    bool first_time_clicked = true; // нужно для обработки клика мышки на ячейку игрового поля

    QPushButton **game_pole = nullptr; // массив кнопок на форме GAME_POLE_SIZE на GAME_POLE_SIZE
    QPushButton *win_combination_pole = nullptr; // массив из последовательности трех цветов для победы

    QVBoxLayout *v_page_l = nullptr; // основная компоновка формы (по вертикали)

    CELL **cells_game_pole  =  nullptr; // массив клеток размером GAME_POLE_SIZE на GAME_POLE_SIZE
    CELL *cells_win_combination_pole = nullptr; // победное располажение цветов

    NIGHTMARE_REALM_STYLE *my_style = nullptr; // класс моего стиля компонентов

public:
    NIGHTMARE_REALM_LOGIC(QWidget *parent = nullptr);
    ~NIGHTMARE_REALM_LOGIC();

private:
    bool IsRightTurnCheck(const int &, const int &); // проверка можно ли так ходить
    void StartGame(); // начало игры
    bool IsWin(); // проверка на победу

private slots:
    void CellMovement(); // перемещение ячейки  
};
#endif // WIDGET_H
