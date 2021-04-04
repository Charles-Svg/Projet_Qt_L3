#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notchartwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openFile();
    void FileProcess(QString const & file);

public slots:
    void AboutQt();
    void AboutChart();
    void UpdateChart();

signals:
    void FileSelected(QString const & file);

private:
    Ui::MainWindow *ui;
    QString _file;
    QAction *Draw;
    QAction *Save;
    void ReadData();
    QString _titre;
    NotChartWidget* _graphe;
};
#endif // MAINWINDOW_H
