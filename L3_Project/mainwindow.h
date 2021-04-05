#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notchartwidget.h"
#include <vector>
#include <QColorDialog>
#include <QFontDialog>

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

    void OpenColorDialogAxes(bool);
    void OpenColoDialog1(bool);
    void OpenColoDialog2(bool);
    void OpenColoDialog3(bool);
    void OpenBackgroundDialog(bool);
    void OpenFontDialog(bool);

    void UpdateAxesButton(QColor const & C);
    void UpdatePen1Button(QColor const & C);
    void UpdatePen2Button(QColor const & C);
    void UpdatePen3Button(QColor const & C);
    void UpdateBackgroundButton(QColor const & C);

    void UpdateFont(QFont const & F);

signals:
    void FileSelected(QString const & file);

private:

    void ReadData();

    Ui::MainWindow *ui;
    QString _file;
    QAction *Draw;
    QAction *Save;

    QString _titre;
    NotChartWidget* _graphe;
    QList<QList<float>> donnees;

    QColorDialog * _AxesDialog;
    QColorDialog * _Color1Dialog;
    QColorDialog * _Color2Dialog;
    QColorDialog * _Color3Dialog;
    QColorDialog * _backgroundDialog;

    QFontDialog * _fontDialog;

};
#endif // MAINWINDOW_H
