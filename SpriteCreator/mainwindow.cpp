#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = "";
    
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Save()
{
    canvas->Save();
//    QFileDialog dialog(this);
//    dialog.setDefaultSuffix(".ssp");
//    QString QfileName = dialog.getSaveFileName(
//                this, tr("Save Project"), "C://",
//                "Sprite Sheet Project(*.ssp);;Text File(*.txt)");

//    QFile outputFile(QfileName);
//    outputFile.open(QIODevice::WriteOnly);
//    if(!outputFile.isOpen()){
//        QMessageBox::critical(this, tr("File Load Failed"), tr("Failed to write"));
//    }

//    // this chunk saves the Sprite into a .ssp or .txt file.
//    QTextStream outStream(&outputFile);
//    std::cout << "before canvas->getSprite() from mainWindow" << std::endl;
//    //Sprite sprite = canvas->getSprite();        //this is where the problem is...
//    std::cout << "Sprite address: "<< &canvas->getSprite() << std::endl;
//    std::string s = canvas->getSprite().SpritetoString().c_str();
//    fflush(stdout);
//    std::cout << "Made it this far" << std::endl;
//    std::cout << s << std::endl;
//    outStream << s.c_str();
//    outputFile.close();

//    file = QfileName.toStdString();
//    if(QfileName.isNull())
//    {
//        QMessageBox::critical(this, tr("File Save Failed"), tr("File is Null"));
//    }

//    QMessageBox::information(this, tr("File"), tr("File Saved"));
//    std::cout << file << std::endl;

//    return file;
}

void MainWindow::Load()
{
    QString QfileName = QFileDialog::getOpenFileName(
                this, tr("Open Project"), "C://", "(*.ssp *.txt)");

    std::cout << QfileName.toStdString() << std::endl;
    //this chunk of code gets our file, and makes sure it has the correct extension.
    QFile inputFile(QfileName);
    file = QfileName.toStdString();
    std::string ext = "";
    if(file.find_last_of(".") !=  std::string::npos)
    {
        ext = file.substr(file.find_last_of(".") + 1);
    }
    if(ext != "ssp" && ext != "txt")
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("Extension Failed! 2"));
    }
    else
    {
        QMessageBox::information(this, tr("File Load"), tr("File Loaded!"));
    }

    //here we read the file and put it into std::string for the new Sprite.
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("File Read"), tr("File Read fail!"));
    }
    QString fileText = "";
    QTextStream inText(&inputFile);

    while(!(inText.atEnd()))
    {
        fileText.append(inText.readLine());
        fileText.append("\n");
    }
    inputFile.close();

    std::string spriteText = fileText.toStdString();
    std::cout << spriteText << std::endl;
    Sprite* sprite = new Sprite(spriteText);
    std::cout << sprite->SpritetoString() << std::endl;
}
