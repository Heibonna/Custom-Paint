#include <QApplication>
#include "mainWindow.h"

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    mainWindow w;

    w.show();

    return a.exec();
}

//todo:
//step back/step forward
//separacja tools od window         (processing...)
//Point -> usprawnienia i implementacja w kodzie
