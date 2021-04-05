#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QLocale locale;
    if(locale.language()==QLocale::French)
    {

        if(translator.load(QApplication::applicationDirPath()+"/L3_Project_en_FR.qm"))
        {
             a.installTranslator(&translator);
         }

        else
        {
            qDebug()<<"la traduction n'a pas pu charger";
        }

    }

    MainWindow w;
    w.show();
    return a.exec();
}
