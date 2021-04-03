#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

signals:
    void FileSelected(QString const & file);

private:
    Ui::MainWindow *ui;
    QString _file;
    QAction *Draw;
    QAction *Save;
    void ReadData();
};
#endif // MAINWINDOW_H
