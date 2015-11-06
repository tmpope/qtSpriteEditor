#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
#include "canvaswidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = new CanvasWidget(this);

    setCentralWidget(canvas);
    
    //connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}


std::string MainWindow::Save(){
    //get the file contents from the sprite.
    QString QfileName = QFileDialog::getSaveFileName(
                this, tr("Save Project"), "C://",
                "Sprite Sheet Project(*.ssp;;Text File(*.txt");
    
    if(QfileName.isNull())
    {
        QMessageBox::critical(this, tr("File Save Failed"), tr("File Saving Failed!"));
    }
    std::string file = QfileName.toStdString();
    
    //file = sprite.toString();
    return file;
}

Sprite MainWindow::Load(){
    QString QfileName = QFileDialog::getOpenFileName(
                this, tr("Open Project"), "C://",
                "Sprite Sheet Project(*.ssp);;Text Files(*.txt)");
    
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
    
    // kind of a test of sorts...
//    QMessageBox::information(this, tr("Filename Opened"), file);
    //call the sprite method here with file.
}
