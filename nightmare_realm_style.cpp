#include "nightmare_realm_style.h"
#include "nightmare_realm_logic.h"
#include "cell.h"
#include <QtWidgets>

/// Функии данного класса не описываю, они нужны только для создания граф интерфейса, вы сказали вам это не важно



void NIGHTMARE_REALM_STYLE::SetGamePoleButtonsStyle(QPushButton **game_pole, const int &GAME_POLE_SIZE, CELL **cells_game_pole){


    for(int i=0; i<GAME_POLE_SIZE; ++i)
        for(int j=0; j<GAME_POLE_SIZE; ++j){
            game_pole[i][j].setMaximumSize(image_width,image_height);
            game_pole[i][j].setMinimumSize(image_width,image_height);

            if(cells_game_pole[i][j].status == cleared){
               game_pole[i][j].setStyleSheet("QPushButton{"
                                             "    background-image: url(:/img/image/cleared.png)"
                                            "}"
                                             );
            }
            else if(cells_game_pole[i][j].status == blocked){
                game_pole[i][j].setStyleSheet("QPushButton{"
                                             "    background-image: url(:/img/image/blocked.png)"
                                             "}"
                                              );
            }
            else if(cells_game_pole[i][j].status == yellow){
                game_pole[i][j].setStyleSheet("QPushButton{"
                                                 "    background-image: url(:/img/image/yellow.png)"
                                                 "}"
                                              "QPushButton::focus{"
                                              "    border: 3px solid #333;"
                                              "    border-color: rgb(250, 230, 56);"
                                              "    background-image: none "
                                              "}"
                                              "QPushButton::hover{"
                                              "    border: 2px solid #333;"
                                              "    border-color: rgb(0, 0, 0);"
                                              "}"
                                              );
            }
            else if(cells_game_pole[i][j].status == orange){
                game_pole[i][j].setStyleSheet("QPushButton{"
                                                 "    background-image: url(:/img/image/orange.png)"
                                                 "}"
                                              "QPushButton::focus{"
                                              "    border: 3px solid #333;"
                                              "    border-color: rgb(250, 130, 4);"
                                              "    background-image: none "
                                              "}"
                                              "QPushButton::hover{"
                                              "    border: 2px solid #333;"
                                              "    border-color: rgb(0, 0, 0);"
                                              "}"
                                              );
            }
            else if(cells_game_pole[i][j].status == red){
                game_pole[i][j].setStyleSheet("QPushButton{"
                                                 "    background-image: url(:/img/image/red.png)"
                                                 "}"
                                              "QPushButton::focus{"
                                              "    border: 3px solid #333;"
                                              "    border-color: rgb(255, 0, 0);"
                                              "    background-image: none "
                                              "}"
                                              "QPushButton::hover{"
                                              "    border: 2px solid #333;"
                                              "    border-color: rgb(0, 0, 0);"
                                              "}"
                                              );
            }
        }
}





void NIGHTMARE_REALM_STYLE::SetWinCombinationPoleButtonsStyle(QPushButton *win_combination_pole, const int &GAME_POLE_SIZE, CELL *cells_win_combination_pole){
    for(int i=0; i<GAME_POLE_SIZE; ++i){
        win_combination_pole[i].setMaximumSize(image_width,image_height);
        win_combination_pole[i].setMinimumSize(image_width,image_height);

        if(cells_win_combination_pole[i].status == yellow){
            win_combination_pole[i].setStyleSheet("QPushButton{"
                                                  "    background-image: url(:/img/image/yellow.png);"
                                                  "}"
                                                  );

        }
        else if(cells_win_combination_pole[i].status == orange){
            win_combination_pole[i].setStyleSheet("QPushButton{"
                                                  "    background-image: url(:/img/image/orange.png);"
                                                  "}"
                                                  );
        }
        else if(cells_win_combination_pole[i].status == red){
            win_combination_pole[i].setStyleSheet("QPushButton{"
                                                  "    background-image: url(:/img/image/red.png);"
                                                  "}"
                                                  );
        }
        else{
            win_combination_pole[i].setFlat(true);
        }
        win_combination_pole[i].setEnabled(false);
    }
}





void NIGHTMARE_REALM_STYLE::UpdateButtonStyle(QPushButton* but1,QPushButton* but2){
    QPushButton *buf = new QPushButton;
    buf->setStyleSheet(but1->styleSheet());
    but1->setStyleSheet(but2->styleSheet());
    but2->setStyleSheet(buf->styleSheet());
    delete buf;
}






void NIGHTMARE_REALM_STYLE::SetGameWindowStyle(NIGHTMARE_REALM_LOGIC *game_window){
    game_window->setStyleSheet("QWidget{"
                               "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), "
                               "    stop:0.164773 rgba(87, 95, 77, 255), stop:0.403409 rgba(103, 32, 32, 255), stop:0.602273 rgba(154, 76, 76, 255), "
                               "    stop:0.818182 rgba(193, 143, 54, 255), stop:1 rgba(255, 137, 137, 255));"
                               "}"
                               );

    game_window->setWindowTitle("Nightmare Realm");
    game_window->setFixedSize(QSize(600,600));
}





void NIGHTMARE_REALM_STYLE::SetGameWindowLayoutStyle(QVBoxLayout *v_page_l){
    v_page_l->setSpacing(0);
    v_page_l->setSizeConstraint(QLayout::SetMinAndMaxSize);
}






void NIGHTMARE_REALM_STYLE::SetHLayoutStyle(QHBoxLayout *layout){
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}


