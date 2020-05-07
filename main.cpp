#include <QApplication>
#include <mainWindow.h>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    mainWindow w;

    w.show();

    return a.exec();
}

//todo:
//step back/step forward
//separacja tools od window :/
//wlasny point(lib na przyszlosc)

//done:
//linie pomocnicze, cpy,
