#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include "sprite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Sprite sprite(16,16);
    std::string file = "";
    //canvas = new CanvasWidget(this);

    //setCentralWidget(canvas);
    
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::Save(){
    //get the file contents from the sprite.
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
    QString QfileName = dialog.getSaveFileName(
                this, tr("Save Project"), "C://", 
                "Sprite Sheet Project(*.ssp);;Text File(*.txt)");

    QFile outputFile(QfileName);
    outputFile.open(QIODevice::WriteOnly);
    if(!outputFile.isOpen()){
        QMessageBox::critical(this, tr("File Load Failed"), tr("Failed to write"));
    }

    QTextStream outStream(&outputFile);
    outStream << sprite->toString().c_str();
    outputFile.close();

    file = QfileName.toStdString();
    QMessageBox::information(this, tr("File"), tr("File Saved"));

    if(QfileName.isNull())
    {
        QMessageBox::critical(this, tr("File Save Failed"), tr("File is Null"));
    }
    std::cout << file << std::endl;

    return file;
}

Sprite* MainWindow::Load(){
    QString QfileName = QFileDialog::getOpenFileName(
                this, tr("Open Project"), "C://", 
                "Sprite Sheet Project(*.ssp);;Text Files(*.txt)");

    QFile outputFile(QfileName);  //this might be necessary.



    std::string file = QfileName.toStdString();
    std::string ext = "";
    if(file.find_last_of(".") !=  std::string::npos)
    {
        ext = file.substr(file.find_last_of(".") + 1);
    }

    else
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("File Loading Failed!"));
    }
    if(ext != ".ssp" || ext != ".txt")
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("File Loading Failed!"));
    }

    //call the sprite method here with file.
    return sprite;
}
