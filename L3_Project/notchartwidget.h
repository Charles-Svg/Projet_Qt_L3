#ifndef NOTCHARTWIDGET_H
#define NOTCHARTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPen>
#include <cmath>
#include <QDebug>
#include <QFont>

class NotChartWidget : public QWidget
{
    Q_OBJECT

public:
    NotChartWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void drawChart(QList<QList<float>>const & donnees,bool grille);
    void FreshPixmap();

    QColor AxesColor();
    QColor Pen1Color();
    QColor Pen2Color();
    QColor Pen3Color();

    QColor Background();

    void setXmax(float i){Xmax=std::ceil(i); }
    void setXmin(float i){Xmin=std::floor(i); }
    void setYmax(float i){Ymax=std::ceil(i); }
    void setYmin(float i){Ymin=std::floor(i); }

    void SaveFile(QString const & filename);


public slots:

    void setWidth(int i);
    void setHeight(int i);
    void setMargeX(int i){MargeX=i;}
    void setMargeY(int i){MargeY=i;}

    void setAxesColor(QColor const & C);
    void setPen1Color(QColor const & C);
    void setPen2Color(QColor const & C);
    void setPen3Color(QColor const & C);

    void setBackgroundColor(QColor const &C);

    void setFont(QFont const & F);
    void setTypeDessin(int index);

    void SetPasX(int i){PasX=i;}
    void SetPasY(int i){PasY=i;}

signals:
     void AxesColorChanged(QColor const & C);
     void Pen1ColorChanged(QColor const & C);
     void Pen2ColorChanged(QColor const & C);
     void Pen3ColorChanged(QColor const & C);
     void backgroundColorChanged(QColor const &C);
     void fontChanged(QFont const & F);


private:

    QPen _AxesPen;
    QPen _Pen1;
    QPen _Pen2;
    QPen _Pen3;

    QPixmap*  _chart;

    QColor _background;

    QFont _font;

    int Xmax;
    int Xmin;
    int Ymax;
    int Ymin;

    int MargeX;
    int MargeY;

    int typeDessin; //0 pour point 1 pour ligne

    //pour la marge
    int hauteur(){return this->height()-MargeY*2;}
    int largeur(){return this->width()-MargeX*2;}

    int PasX;
    int PasY;


};

#endif // NOTCHARTWIDGET_H
