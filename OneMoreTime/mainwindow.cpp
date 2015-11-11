#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "sprite.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file = "";

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveSprite()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveSprite()
{
    //get the file contents from the sprite.
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
    QString QfileName = dialog.getSaveFileName( this, tr("Save Project"), "C://", "Sprite Sheet Project(*.ssp);;Text File(*.txt)");
    QFile outputFile(QfileName);
    outputFile.open(QIODevice::WriteOnly);
    if(!outputFile.isOpen()){
        QMessageBox::critical(this, tr("File Load Failed"), tr("Failed to write"));
    }
    QTextStream outStream(&outputFile);
    Sprite* sprite = ui->canvas->getSprite();
    std::string s = sprite->toString();
    std::cout << "Made it this far" << std::endl;
    std::cout << s << std::endl;
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
    // TODO: This
}
