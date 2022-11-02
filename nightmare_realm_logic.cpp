#include "nightmare_realm_logic.h"
#include "nightmare_realm_style.h"
#include "cell.h"

#include <QtWidgets>
#include <random>
#include <ctime>



//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::NIGHTMARE_REALM_LOGIC//////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// Конструктор выделяет память для будущих объектов (игровое поле + поле побед-
/// ной комбинации) и запускает начало игры
NIGHTMARE_REALM_LOGIC::NIGHTMARE_REALM_LOGIC(QWidget *parent): QWidget(parent){
    my_style = new NIGHTMARE_REALM_STYLE;

    v_page_l = new QVBoxLayout(this); // вертикальный лоят для выравнивания компонентов по вертикали
    my_style->SetGameWindowLayoutStyle(v_page_l);

    QHBoxLayout *h_win_combination_l = new QHBoxLayout(); // компоновщик для массива кнопок победного расположения цветов
    win_combination_pole = new QPushButton [GAME_POLE_SIZE]; // верхняя панель расположенных трех цветов, по которым нужно заполнить столбцы этим же цветом для победы
    for(int i=0; i<GAME_POLE_SIZE;++i)
        h_win_combination_l->addWidget(&win_combination_pole[i]);

    v_page_l->addLayout(h_win_combination_l);
    my_style->SetHLayoutStyle(h_win_combination_l);

    cells_win_combination_pole = new CELL [GAME_POLE_SIZE]; // выделяем память на массив клеток победного поля цветов


    game_pole = new QPushButton *[GAME_POLE_SIZE]; // выделяем память на игровое поле кнопок
    for(int i=0; i<GAME_POLE_SIZE;++i) game_pole[i] = new QPushButton[GAME_POLE_SIZE];

    for(int i=0; i<GAME_POLE_SIZE;++i){
        QHBoxLayout * h_game_pole_l = new QHBoxLayout;

        for(int j=0; j<GAME_POLE_SIZE;++j) h_game_pole_l->addWidget(&game_pole[i][j]); //создаем таблицу кнопок на форме

        v_page_l->addLayout(h_game_pole_l);
    }

    cells_game_pole = new CELL *[GAME_POLE_SIZE]; //выделяем память на массив клеток соответствующему массиву кнопок игрового поля
    for(int i=0; i<GAME_POLE_SIZE;++i) cells_game_pole[i] = new CELL[GAME_POLE_SIZE];

    for(int i=0; i<GAME_POLE_SIZE;++i)
        for(int j=0; j<GAME_POLE_SIZE;++j) connect(&game_pole[i][j],SIGNAL(clicked()),this,SLOT(CellMovement()));

    StartGame();
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::NIGHTMARE_REALM_LOGIC//////////////////////////////
//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::~NIGHTMARE_REALM_LOGIC/////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// освобождает память
NIGHTMARE_REALM_LOGIC::~NIGHTMARE_REALM_LOGIC(){
    delete [] cells_win_combination_pole; //после завершения програмы удаляем наши объекты (так как наш объект удаляется при завершении программы это не так важно)

    for(int i=0; i<GAME_POLE_SIZE;++i)
        delete [] cells_game_pole[i];

    delete [] cells_game_pole;

    delete my_style; // удаляем объект стиля
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::~NIGHTMARE_REALM_LOGIC/////////////////////////////
//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::StartGame//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// Функция задает начало игры, заполняя созданные нами ранее пустые массивы
/// (игровое поле + поле победной комбинации)
void NIGHTMARE_REALM_LOGIC::StartGame(){

    std::srand(time(NULL));

    yellow_amount = 0; // обнуляем счетчики
    orange_amount = 0;
    red_amount = 0;

    for(int i=0; i<GAME_POLE_SIZE;++i){ // заполнения массива клеток победного по цвету
        if(i%2 == 0){
            cells_win_combination_pole[i].status =(cell_status)(rand() % (1+red-yellow)+yellow);

            for(int j=0; j<i;j+=2){ // этот цикл нужен для того, чтобы убрать повторы цветов (должно быть три разных цвета)
                    while(cells_win_combination_pole[i].status == cells_win_combination_pole[j].status){
                        cells_win_combination_pole[i].status = (cell_status)(rand() % (1+red-yellow)+yellow); // (1+red-yellow)+yellow) диапазон значений желтый, оранжевый и красный
                        j=0;
                    }
            }
            cells_win_combination_pole[i].cell_i = 0;
            cells_win_combination_pole[i].cell_j = i;
        }
        else cells_win_combination_pole[i].status = cleared;
    }


    for(int i=0; i<GAME_POLE_SIZE; ++i)
        for(int j=0; j<GAME_POLE_SIZE; ++j){ //заполняю игровое поле клетками (согласно картинке)
            if(j%2 == 0){
                cells_game_pole[i][j].status = (cell_status)(rand() % (1+red-yellow)+yellow); // если столбик четный, то заполняю цветом
                if(cells_game_pole[i][j].status == yellow && yellow_amount<max_color_amount) yellow_amount++; //это нужно, чтобы заполнить массив определенным кол-вом
                else if (cells_game_pole[i][j].status == orange && orange_amount<max_color_amount) orange_amount++;// нужных нам цветов
                else if (cells_game_pole[i][j].status == red && red_amount<max_color_amount) red_amount++;
                else --j;
            }
            else if(i%2 == 0) cells_game_pole[i][j].status = blocked; // иначе если строка четная, то заполняю блоком
            else cells_game_pole[i][j].status = cleared; // иначе это пустая клетка

            cells_game_pole[i][j].cell_i = i; // сохраняем координаты клетки
            cells_game_pole[i][j].cell_j = j;
        }

    my_style->SetGamePoleButtonsStyle(game_pole, GAME_POLE_SIZE, cells_game_pole);
    my_style->SetWinCombinationPoleButtonsStyle(win_combination_pole, GAME_POLE_SIZE, cells_win_combination_pole);
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::StartGame//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::CellMovement///.///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// Функция осуществляет обработки хода игрока, вызывает проверку хода и в слу-
/// чаи его правильности, меняет ячейки местами, так же вызывает функции провер-
/// ки на победу
void NIGHTMARE_REALM_LOGIC::CellMovement(){

    if(first_time_clicked){
        for(int i=0; i<GAME_POLE_SIZE;++i)
            for(int j=0; j<GAME_POLE_SIZE;++j)
                if(&game_pole[i][j] == sender()){
                    if(cells_game_pole[i][j].status == cleared || cells_game_pole[i][j].status == blocked ) return; // если клетка пустая или заблокирована, не обрабатываем
                    but_i  = i; // нашли нашу кнопку, сохраняем ее координаты
                    but_j = j;
                    first_time_clicked = false; // запоминаем, что мы выбрали объект, который будем перетаскивать
                    game_pole[i][j].setFlat(true);
                    return; // выходим из функции, дальше искать нет смысла
                }
    }
    else{
        for(int i=0; i<GAME_POLE_SIZE;++i)
            for(int j=0; j<GAME_POLE_SIZE;++j)
                if(&game_pole[i][j] == sender()){
                    if(IsRightTurnCheck(i,j)){ // если так ходить можно
                        std::swap(cells_game_pole[i][j].status, cells_game_pole[but_i][but_j].status); // меняем статус ячеек
                        std::swap(cells_game_pole[i][j].cell_i, cells_game_pole[but_i][but_j].cell_i); // меняем координаты ячеек
                        std::swap(cells_game_pole[i][j].cell_j, cells_game_pole[but_i][but_j].cell_j);

                        my_style->UpdateButtonStyle(&game_pole[i][j],&game_pole[but_i][but_j]);

                        if(IsWin()){
                            game_pole[but_i][but_j].setFlat(false);
                            return; // выходим из функции, дальше искать нет смысла; // проверка на победу
                        }
                    }
                        game_pole[but_i][but_j].setFlat(false);
                        return; // выходим из функции, дальше искать нет смысла
                }
    }
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::CellMovement///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::IsRightTurnCheck///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// Функция нужна для проверки хода, т е можно ли так ходить, как походил игрок
bool NIGHTMARE_REALM_LOGIC::IsRightTurnCheck(const int &but_i, const int &but_j){   
    first_time_clicked = true;
    if(but_i == this->but_i && but_j == this->but_j) return false; // если два раза нажали на одну кнопку
    if(cells_game_pole[but_i][but_j].status != cleared) return false; // если клетка не свободна, значит сюда ходить нельзя
    if((but_i>this->but_i+1||but_j>this->but_j+1)||(but_i<this->but_i-1||but_j<this->but_j-1)) return false;
    if(but_i!=this->but_i && but_j!=this->but_j) return false; // проверка на то, что можно передвигать только на одну клетку по гор. или верт
    return true; // если все норм, значит так ходить можно
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::IsRightTurnCheck///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::IsWin//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// Функия проверяет состояния игры на победу для выхода из игры или чтобы на-
/// чать сначала.
bool NIGHTMARE_REALM_LOGIC::IsWin(){

    for(int i=0; i<GAME_POLE_SIZE; i+=2)
        for(int j=0; j<GAME_POLE_SIZE; ++j)
            if(cells_game_pole[j][i].status != cells_win_combination_pole[i].status) return false; //если хоть один статус ячейки игрового поля не совпадет со
                                                                                      // статусом ячейки победного поля, то выходим

    QWidget *mes_window = new QWidget; // нужно для вывода сообщения
    QMessageBox *message = new QMessageBox(mes_window);
    QMessageBox::StandardButton reply = message->question(mes_window,"Победа!", "Уровень пройден! Желаете начать сначала?",
                                                              QMessageBox::Yes | QMessageBox::No);
    delete message;
    delete mes_window;
    if (reply ==QMessageBox::Yes) StartGame();
    else close();

    return true; //победа
}
//////////////////////////////////////////////////////////////////////////////
/// NIGHTMARE_REALM_LOGIC::IsWin//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
