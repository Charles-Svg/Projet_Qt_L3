#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIcon>
#include <QStyle>
#include <QAction>
#include <QFileDialog>
#include <QSplitter>
#include <QTableWidget>
#include <QMessageBox>
#include<QTextStream>
#include<QTableWidgetItem>

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

void MainWindow::openFile()
{
QString fileName=QFileDialog::getOpenFileName(this,tr("Load a data file"),"~","*csv");
emit FileSelected(fileName);
}

void MainWindow::FileProcess(QString const & file)
{
    //la verification de l'existence du fichier est faite au moment d'ouvrir les données
    _file=file;
    setWindowTitle(this->windowTitle()+"["+_file+"]");
    ReadData();
    Draw->setEnabled(1);
    Save->setEnabled(1);

}

void MainWindow::ReadData()
{
      //lecture csv du Tp3
        if(QFile::exists(_file))
        {
            QFile data(_file);
          // On ouvre le fichier en lecture seule
          if(data.exists() && data.open(QIODevice::ReadOnly)) {
              QTextStream in(&data);

              int row=-1;
              bool first=1;
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
                  for(int col=0; col<data.size(); ++col) {
                      ui->tableWidget->setItem(row, col, new QTableWidgetItem(data[col]));
                  }
                    }
                  ++row;
              }

              data.close();
          }
        }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Hello wolrd "));

    ui->splitter->setStyleSheet("border : 1px solid black");


    //--------------------Barre de Menu--------------------//

    this->setWindowIcon(QIcon(":/img/icon.svg"));

    //-----Menu1-----//

    QAction * Open =new QAction(this->style()->standardIcon(QStyle::SP_FileIcon),tr("Open file"));
    Open->setShortcut(QKeySequence::Open);
    connect(Open,&QAction::triggered,this,&MainWindow::openFile);

    QAction * Quit =new QAction(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton),tr("Quit"));
    Quit->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(Quit,&QAction::triggered,this,&MainWindow::close);

    ui->Menu1->addAction(Open); ui->Menu1->addAction(Quit);


    //-----Menu2-----//
    this->Draw= new QAction(tr("Draw the chart"));

    this->Save=new QAction(tr("Save the graph as..."));
    Save->setShortcut(QKeySequence("Ctrl+Shift+S"));

    Draw->setEnabled(0); Save->setEnabled(0);

    ui->Menu2->addAction(Draw); ui->Menu2->addAction(Save);

    //-----Menu3-----//
    ui->Menu3->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxQuestion));
    QAction * AbQt = new QAction(this->style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("About Qt"));
    QObject::connect(AbQt,&QAction::triggered,this,&MainWindow::AboutQt);


    QAction *AbChart = new QAction(this->style()->standardIcon(QStyle::SP_MessageBoxInformation),tr("About Charts"));
    connect(AbChart,&QAction::triggered,this,&MainWindow::AboutChart);

    ui->Menu3->addAction(AbQt); ui->Menu3->addAction(AbChart);

    connect(this,&MainWindow::FileSelected,this,&MainWindow::FileProcess);


    //-----table des données-----//






}

MainWindow::~MainWindow()
{
    delete ui;
}

