#ifndef NOTCHARTWIDGET_H
#define NOTCHARTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>

class NotChartWidget : public QWidget
{
    Q_OBJECT

public:
    NotChartWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);


private:


    QPixmap _chart;

};

#endif // NOTCHARTWIDGET_H
