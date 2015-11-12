#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "sprite.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file = "";

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveSprite()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadSprite()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveSprite()
{
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
    QString QfileName = dialog.getSaveFileName( this, tr("Save Project"), "C://", "Sprite Sheet Project(*.ssp);;Text File(*.txt)");
    QFile outputFile(QfileName);
    outputFile.open(QIODevice::WriteOnly);
    if(!outputFile.isOpen()){
        QMessageBox::critical(this, tr("File Save Failed"), tr("Failed to write to file."));
    }
    QTextStream outStream(&outputFile);

    // ~ACL: Here's where I did stuff to fix the issue:
    Sprite* sprite = ui->canvas->getSprite();
    std::string s = sprite->toString(); // This totally works for some strange reason.
    outStream << s.c_str();
    outputFile.close();

    file = QfileName.toStdString();
    QMessageBox::information(this, tr("File"), tr("File Saved"));

    if(QfileName.isNull())
    {
        QMessageBox::critical(this, tr("File Save Failed"), tr("File is Null"));
    }
    std::cout << file << std::endl;
}

void MainWindow::loadSprite(){
    QString QfileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "C://", "Sprite Sheet Project(*.ssp);;Text Files(*.txt)");
    std::cout << "File name: " << QfileName.toStdString() << std::endl;
    QFile inputFile(QfileName);

    std::string file = QfileName.toStdString();
    std::string ext = "";
    if(file.find_last_of(".") !=  std::string::npos)
    {
        ext = file.substr(file.find_last_of(".") + 1);
    }

    else
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("An extension could not be found for the file!"));
        return;
    }
//    if(ext != ".ssp" || ext != ".txt")
//    {
//        QMessageBox::critical(this, tr("File Load Failed"), tr("You must select a file with .ssp or .txt extension!"));
//        return;
//    }

    // Here's where things get funky - I hope I'm doing this right.

    std::stringstream ss;

    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        ss << in.readAll().toStdString();
    }

    std::cout << "Here's the file: " << ss.str() << std::endl;

    ui->canvas->loadSpriteFromString(ss.str());
}
















