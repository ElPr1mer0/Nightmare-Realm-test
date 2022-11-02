#ifndef NIGHTMARE_REALM_STYLE_H
#define NIGHTMARE_REALM_STYLE_H

class QPushButton;
class CELL;
class NIGHTMARE_REALM_LOGIC;
class QVBoxLayout;
class QHBoxLayout;

class NIGHTMARE_REALM_STYLE{
private:
    const int image_width = 100; //размер изображений ячеек
    const int image_height = 90;

public: // методы этого класса нужны только для графического изменения объектов
    void SetGamePoleButtonsStyle(QPushButton **, const int&, CELL **);
    void SetWinCombinationPoleButtonsStyle(QPushButton *, const int&, CELL *);
    void UpdateButtonStyle(QPushButton* , QPushButton*);
    void SetGameWindowStyle(NIGHTMARE_REALM_LOGIC*);
    void SetGameWindowLayoutStyle(QVBoxLayout*);
    void SetHLayoutStyle(QHBoxLayout*);
};

#endif // NIGHTMARE_REALM_STYLE_H
