#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

/*    QTranslator translator;
    if(translator.load(QApplication::applicationDirPath()+"/L3_Project_en_FR.qm")) {
         a.installTranslator(&translator);
     } */
    MainWindow w;
    w.show();
    return a.exec();
}
