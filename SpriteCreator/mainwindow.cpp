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
    std::string file = "";

    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveSprite()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadSprite()));
    connect(ui->penButton, SIGNAL(clicked(bool)), this, SLOT(ui->canvas->setCurrentTool(PENCIL);));
    connect(ui->eyeDropperButton, SIGNAL(clicked(bool)), this, SLOT(ui->canvas->setCurrentTool(EYE_DROPPER);));
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

    ui->canvas->save(QfileName.toStdString());

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

    FILE* f;
    f = fopen(file.c_str(),"r");
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);
    char* buffer = reinterpret_cast<char*>(malloc(sizeof(char)*filesize));
    fread(buffer, 1, filesize, f);
    std::string str(buffer);
    free(buffer);
    fclose(f);

    ui->canvas->loadSpriteFromString(str);
}
