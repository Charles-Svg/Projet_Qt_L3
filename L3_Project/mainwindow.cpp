#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QIcon>
#include <QStyle>
#include <QAction>
#include <QFileDialog>
#include <QSplitter>
#include <QTableWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QtDebug>
#include <QSpinBox>
#include <string>

void MainWindow::AboutQt()
{
    QMessageBox::aboutQt(this,tr("About Qt"));
}

void MainWindow::AboutChart()
{
  /*  InfoDialogPerso * AbChrt = new InfoDialogPerso(this);
    AbChrt->exec();
    */
QMessageBox::about(this,tr("About Charts"),"Cette application à été réalisée par Charles Sauvagnac pour le projet de Développement d'Interface Graphique Avancée de L3 informatique de l'Université Belle Beille à Angers.");
}


void MainWindow::UpdateChart()
{
    _graphe->drawChart(donnees,ui->checkBoxGrille->isChecked());
    _graphe->update();
}



//-----------------gestion de la lecture et ecriture des données du fichier csv-----------------//

void MainWindow::openFile()
{
QString fileName=QFileDialog::getOpenFileName(this,tr("Load a data file"),"~","*csv");
emit FileSelected(fileName);
}

void MainWindow::FileProcess(QString const & file)
{
    //la verification de l'existence du fichier est faite au moment d'ouvrir les données
    _file=file;
   // trouver un moyen de cut la dernière partie du filepath

    setWindowTitle(this->_titre+"["+_file+"]");
    ReadData();
    Draw->setEnabled(1);
    Save->setEnabled(1);

}


void MainWindow::ReadData()
{
      //lecture csv du Tp3
        ui->tableWidget->clear();
        donnees.clear();
        if(QFile::exists(_file))
        {
            QFile data(_file);
            if(data.exists() && data.open(QIODevice::ReadOnly)) {
              QTextStream in(&data);

              int row=-1;
              bool first=1;
              float minX=1000; float minY=1000;
              float maxX=-1000; float maxY=-1000; // permets de les definir en même temps que la lectures des données pour dessiner le graphe


              while(!in.atEnd()) {
                  QString ligne = in.readLine();
                  QStringList data = ligne.split(',');
                  if(first)
                  {

                    for(int i=0;i<data.size();i++)
                    {

                        ui->tableWidget->insertColumn(i);
                        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(data.at(i)));

                    }
                    first=0;
                  }
                  else {
                  ui->tableWidget->insertRow(row);

                  QList<float> Ligne; // pour garder les données en memoire dans la Qlist

                  for(int col=0; col<data.size(); ++col) {
                      ui->tableWidget->setItem(row, col, new QTableWidgetItem(data[col]));
                    if(col==0)
                    {
                        if(data[col].toFloat()<minX) minX=data[col].toFloat();
                        if(data[col].toFloat()>maxX) maxX=data[col].toFloat();
                    }

                    else
                    {
                        if(data[col].toFloat()<minY) minY=data[col].toFloat();
                        if(data[col].toFloat()>maxY) maxY=data[col].toFloat();
                    }

                    Ligne.push_back(data[col].toFloat());
                  }
                  donnees.push_back(Ligne);
                    }
                  ++row;
              }

              data.close();
              _graphe->setXmin(minX); _graphe->setXmax(maxX);
              _graphe->setYmin(minY); _graphe->setYmax(maxY);


          }

        }
}

//---------------------------gestion de la sauvegarde de la pixmap-----------------------------//


 void MainWindow::SaveFile(bool)
 {
    QString fileName= QFileDialog::getSaveFileName(this,tr("Save you File"),"",tr("*.png"));
    if(fileName.isEmpty())
        return;
    else {
        _graphe->SaveFile(fileName);
    }
 }


//-----------------------signaux et slots pour les boutton gerant les couleurs et le font---------------------------------//

void MainWindow::OpenColorDialogAxes(bool)
{
    _AxesDialog->open();
}

void MainWindow::OpenColoDialog1(bool)
{
    _Color1Dialog->open();
}

void MainWindow::OpenColoDialog2(bool)
{
       _Color2Dialog->open();
}

void MainWindow::OpenColoDialog3(bool)
{
       _Color3Dialog->open();
}

void MainWindow::OpenBackgroundDialog(bool)
{
    _backgroundDialog->open();
}

void MainWindow::OpenFontDialog(bool)
{
    _fontDialog->open();
}

void MainWindow::UpdatePen1Button(QColor const & C)
{
    QString qs= "background-color: %1;";
    QString AxesColor=qs.arg(C.name());
    ui->pushButtonColor1->setStyleSheet(AxesColor);
}

void MainWindow::UpdatePen2Button(QColor const & C)
{
    QString qs= "background-color: %1;";
    QString AxesColor=qs.arg(C.name());
    ui->pushButtonColor2->setStyleSheet(AxesColor);
}

void MainWindow::UpdatePen3Button(QColor const & C)
{
    QString qs= "background-color: %1;";
    QString AxesColor=qs.arg(C.name());
    ui->pushButtonColor3->setStyleSheet(AxesColor);
}


void  MainWindow::UpdateAxesButton(QColor const & C)
{
    QString qs= "background-color: %1;";
    QString AxesColor=qs.arg(C.name());
    ui->pushButtonAxeColor->setStyleSheet(AxesColor);
}

void MainWindow::UpdateBackgroundButton(QColor const & C)
{

    QString qs= "background-color: %1;";
    QString AxesColor=qs.arg(C.name());
    ui->pushButtonBackgroundColor->setStyleSheet(AxesColor);
}


void MainWindow::UpdateFont(QFont const & F)
{
    QString str=F.family()+","+QString::number(F.pointSize());
    ui->pushButtonPolice->setText(str);
}


//----------------------Contruction Objet MainWindow--------------------------------//


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_titre(tr("Chart"))
    ,_AxesDialog(new QColorDialog()),_Color1Dialog(new QColorDialog()),_Color2Dialog(new QColorDialog()),_Color3Dialog(new QColorDialog()),_backgroundDialog(new QColorDialog())
    ,_fontDialog(new QFontDialog())
{
    ui->setupUi(this);
    this->setWindowTitle(_titre);




    //--------------Barre de Menu--------------//

    this->setWindowIcon(QIcon(":/img/icon.svg"));

    //-----Menu1-----//


    //open
    QAction * Open =new QAction(this->style()->standardIcon(QStyle::SP_FileIcon),tr("Open file"));
    Open->setShortcut(QKeySequence::Open);
    connect(Open,&QAction::triggered,this,&MainWindow::openFile);
    connect(this,&MainWindow::FileSelected,this,&MainWindow::FileProcess);


    //quit
    QAction * Quit =new QAction(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton),tr("Quit"));
    Quit->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(Quit,&QAction::triggered,this,&MainWindow::close);

    ui->Menu1->addAction(Open); ui->Menu1->addAction(Quit);


    //-----Menu2-----//

    //dessin et sauvegarde
    this->Draw= new QAction(tr("Draw the chart"));

    this->Save=new QAction(tr("Save the graph as..."));
    Save->setShortcut(QKeySequence("Ctrl+Shift+S"));

    Draw->setEnabled(0); Save->setEnabled(0);

    ui->Menu2->addAction(Draw); ui->Menu2->addAction(Save);

    QObject::connect(Draw,&QAction::triggered,this,&MainWindow::UpdateChart);


    //-----Menu3-----//

    //Les AboutQt
    ui->Menu3->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxQuestion));
    QAction * AbQt = new QAction(this->style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("About Qt"));
    QObject::connect(AbQt,&QAction::triggered,this,&MainWindow::AboutQt);


    QAction *AbChart = new QAction(this->style()->standardIcon(QStyle::SP_MessageBoxInformation),tr("About Charts"));
    connect(AbChart,&QAction::triggered,this,&MainWindow::AboutChart);

    ui->Menu3->addAction(AbQt); ui->Menu3->addAction(AbChart);



    //-----Graphe-----//

    _graphe = new NotChartWidget(this);
    ui->ChartLayout->addWidget(_graphe);;


    //splitter settings
     ui->splitter->setSizes(QList<int>({200,200,800}));

    //-----parametres du Graphe-----//

     //initialisation des boutton de couleurs

     QString qs= "background-color: %1;";
     QString AxesColor=qs.arg(_graphe->AxesColor().name());
     ui->pushButtonAxeColor->setStyleSheet(AxesColor);

     QString Pen1Color=qs.arg(_graphe->Pen1Color().name());
     ui->pushButtonColor1->setStyleSheet(Pen1Color);

     QString Pen2Color=qs.arg(_graphe->Pen2Color().name());
     ui->pushButtonColor2->setStyleSheet(Pen2Color);

     QString Pen3Color=qs.arg(_graphe->Pen3Color().name());
     ui->pushButtonColor3->setStyleSheet(Pen3Color);

     QString backgroundColor=qs.arg(_graphe->Background().name());
     ui->pushButtonBackgroundColor->setStyleSheet(backgroundColor);

     QString font="Arial,8";
     ui->pushButtonPolice->setText(font);

    //reglages de la taille du graphe
    ui->spinBoxHauteur->setValue(600);
    ui->spinBoxLargeur->setValue(800);

    QObject::connect(ui->spinBoxHauteur,QOverload<int>::of(&QSpinBox::valueChanged),_graphe,&NotChartWidget::setHeight);
    QObject::connect(ui->spinBoxLargeur,QOverload<int>::of(&QSpinBox::valueChanged),_graphe,&NotChartWidget::setWidth);

    QObject::connect(ui->spinBoxMargeX,QOverload<int>::of(&QSpinBox::valueChanged),_graphe,&NotChartWidget::setMargeX);
    QObject::connect(ui->spinBoxMargeY,QOverload<int>::of(&QSpinBox::valueChanged),_graphe,&NotChartWidget::setMargeY);

    //les Dialogues de couleurs

    //axes
    QObject::connect(ui->pushButtonAxeColor,&QPushButton::clicked,this,&MainWindow::OpenColorDialogAxes);
    QObject::connect(_AxesDialog,&QColorDialog::colorSelected,_graphe,&NotChartWidget::setAxesColor);
    QObject::connect(_graphe,&NotChartWidget::AxesColorChanged,this,&MainWindow::UpdateAxesButton);

    //color1
    QObject::connect(ui->pushButtonColor1,&QPushButton::clicked,this,&MainWindow::OpenColoDialog1);
    QObject::connect(_Color1Dialog,&QColorDialog::colorSelected,_graphe,&NotChartWidget::setPen1Color);
    QObject::connect(_graphe,&NotChartWidget::Pen1ColorChanged,this,&MainWindow::UpdatePen1Button);

    //color2
    QObject::connect(ui->pushButtonColor2,&QPushButton::clicked,this,&MainWindow::OpenColoDialog2);
    QObject::connect(_Color2Dialog,&QColorDialog::colorSelected,_graphe,&NotChartWidget::setPen2Color);
    QObject::connect(_graphe,&NotChartWidget::Pen2ColorChanged,this,&MainWindow::UpdatePen2Button);

    //color3
    QObject::connect(ui->pushButtonColor3,&QPushButton::clicked,this,&MainWindow::OpenColoDialog3);
    QObject::connect(_Color3Dialog,&QColorDialog::colorSelected,_graphe,&NotChartWidget::setPen3Color);
    QObject::connect(_graphe,&NotChartWidget::Pen3ColorChanged,this,&MainWindow::UpdatePen3Button);

    //background
    QObject::connect(ui->pushButtonBackgroundColor,&QPushButton::clicked,this ,&MainWindow::OpenBackgroundDialog);
    QObject::connect(_backgroundDialog,&QColorDialog::colorSelected,_graphe,&NotChartWidget::setBackgroundColor);
    QObject::connect(_graphe,&NotChartWidget::backgroundColorChanged,this,&MainWindow::UpdateBackgroundButton);

    //font
    QObject::connect(ui->pushButtonPolice,&QPushButton::clicked,this,&MainWindow::OpenFontDialog);
    QObject::connect(_fontDialog,&QFontDialog::fontSelected,_graphe,&NotChartWidget::setFont);
    QObject::connect(_graphe,&NotChartWidget::fontChanged,this,&MainWindow::UpdateFont);

    //type de dessin
    QObject::connect(ui->typeDessinComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),_graphe,&NotChartWidget::setTypeDessin);


     //sauvegarde
    QObject::connect(Save,&QAction::triggered,this,&MainWindow::SaveFile);

}

MainWindow::~MainWindow()
{
    delete ui;
}

