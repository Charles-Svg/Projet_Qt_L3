#include "notchartwidget.h"
#include <QPainter>
#include <QDebug>


void NotChartWidget::setWidth( int i) {this->setMinimumWidth(i);_chart=new QPixmap(_chart->scaled(i,this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));}
void NotChartWidget::setHeight(int i) {this->setMinimumHeight(i);_chart=new QPixmap(_chart->scaled(this->width(),i,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));}


QColor NotChartWidget::AxesColor()
{return _AxesPen.color();}

QColor NotChartWidget::Pen1Color()
{return _Pen1.color();}

QColor NotChartWidget::Pen2Color()
{return _Pen2.color();}

QColor NotChartWidget::Pen3Color()
{return _Pen3.color();}


QColor NotChartWidget::Background()
{return _background;}


void NotChartWidget::setAxesColor( QColor const & C)
{
    _AxesPen.setColor(C);
    emit AxesColorChanged(C);
}

void NotChartWidget::setPen1Color(QColor const & C)
{
    _Pen1.setColor(C);
    emit Pen1ColorChanged(C);
}

void NotChartWidget::setPen2Color(QColor const & C)
{
    _Pen2.setColor(C);
    emit Pen2ColorChanged(C);
}

void NotChartWidget::setPen3Color(QColor const & C)
{
    _Pen3.setColor(C);
    emit Pen3ColorChanged(C);
}

void NotChartWidget::setBackgroundColor(QColor const &C)
{
    _background=C;
    emit backgroundColorChanged(C);
}



void NotChartWidget::setFont(QFont const & F)
{
    _font=F;
    emit fontChanged(F);
}




void NotChartWidget::FreshPixmap()
{
    //un fonction pour clear le pixmap
    _chart=new QPixmap(this->width(),this->height());
    _chart->fill(_background);

}

//------------construction de l'objet NotChartWidget---------------//

NotChartWidget::NotChartWidget(QWidget *parent)
    : QWidget(parent),
      _AxesPen(QBrush(QColorConstants::DarkCyan),2),
    _Pen1(QBrush(QColorConstants::DarkMagenta),5),_Pen2(QBrush(QColorConstants::DarkGreen),5),_Pen3(QBrush(QColorConstants::DarkBlue),5),
    _background(QColorConstants::White),
    MargeX(20),MargeY(20),
    _font("Arial",8)

{

    setMinimumSize(820,620);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    FreshPixmap();


}

//-----------------gestion du dessin sur la pixmap-----------------//
void NotChartWidget::paintEvent(QPaintEvent *)
{
    //dessine sur le Widget
    QPainter painter(this);
    painter.drawPixmap(0,0,*_chart);
}


void NotChartWidget::drawChart(QList<QList<float>>const & donnees,bool grille) // passer le type de données à dessiner
{
    FreshPixmap();
    //voir pour le setPen$


    QPainter painter(_chart);
    QImage img(":/img/watermark");
    QPoint imgpoint(_chart->width()-img.width(),0);
    painter.drawImage(imgpoint,img);




    //dessine sur la Pixmap

    //grille sur les X
    int lesx=std::abs(Xmin)+std::abs(Xmax);


    //grille sur les Y
    int lesy= std::abs(Ymin)+std::abs(Ymax);

  if(grille)
  {
      QPen* pen=new QPen(QBrush(QColorConstants::LightGray),1);
      painter.setPen(*pen);

            for(int i=0;i<lesx;i++)
            {
                int point=(i*largeur())/lesx;
                painter.drawLine(point ,0,point ,hauteur());

            }


            for(int i=0;i<lesy;i++)
            {
                int point=(i*(hauteur())/lesy);
                painter.drawLine(0,point,largeur(),point);

            }
  }


    //dessine les axes
    painter.setPen(_AxesPen);

    //line verticale qui s'adapte en fonction des données
    int axesXpoint=(std::abs(Xmin)*largeur())/lesx;

    painter.drawLine(axesXpoint,0,axesXpoint,hauteur());


    painter.drawLine(0,hauteur()/2,largeur(),hauteur()/2);



    //set le PEn et la font du painter

    QPen* pen=new QPen(QBrush(QColorConstants::Black),2);
    painter.setPen(*pen);

    _font.setPixelSize(20);
    painter.setFont(_font);


    //dessine les chffres sur X et Y

    for(int i=0; i<=lesx;i++)
    {
      int point=(i*largeur())/lesx;
      painter.drawText(QPoint(point,hauteur()/2),QString::number(i+Xmin));

    }

    for(int i=0; i<=lesy;i++)
    {
      int point=(i*hauteur())/lesy;
      if(Ymax-i!=0)
      painter.drawText(QPoint(axesXpoint,point),QString::number(Ymax-i));

    }



    //dessine les points

    painter.setPen(_Pen1);
    for(int i=0;i<donnees.size();i++)
    {


        //reformatte les x
         float x=donnees.at(i).at(0);
        if(x<0)
             x=std::abs(Xmin)-(std::abs(donnees.at(i).at(0)));

        else
             x=std::abs(Xmin)+(std::abs(donnees.at(i).at(0)));

        x=(x/lesx)*largeur();

        for(int j=1;j<donnees.at(i).size();j++)
        {
            //reformatte les y
           float y =donnees.at(i).at(j);
           if(y<0)
               y=std::abs(Ymin)-std::abs(donnees.at(i).at(j));
           else
               y=std::abs(Ymin)+std::abs(donnees.at(i).at(j));

           y=(y/lesy)*hauteur();

           switch (j%3) {

           case 1:
               painter.setPen(_Pen1);
               break;

           case 2:
               painter.setPen(_Pen2);
               break;
           case 0:
               painter.setPen(_Pen3);
               break;

           }
           painter.drawPoint(x,hauteur()-y);

        }

    }




}
