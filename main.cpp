#include "nightmare_realm_logic.h"
#include "nightmare_realm_style.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    NIGHTMARE_REALM_LOGIC *window = new NIGHTMARE_REALM_LOGIC;
    NIGHTMARE_REALM_STYLE *my_style = new NIGHTMARE_REALM_STYLE;
    my_style->SetGameWindowStyle(window);
    window->show();
    delete my_style;
    return a.exec();
}
