#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = new CanvasWidget(this);

    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//std::string MainWindow::Save(Sprite sprite){

////    std::string ret = sprite.toString();
////    return ret;
//}

//Sprite MainWindow::Load(std::string file){
//    //TODO get this working
////    const int BUFSIZE = 1024;
////    char buffer[BUFSIZE] = {0};
////    OPENFILENAME openBox = {0};
////    openBox.lStructSize = sizeof( ofns );
////    openBox.lpstrFile = buffer;
////    openBox.nMaxFile = BUFSIZE;
////    openBox.lpstrTitle = file.c_str();
////    GetOpenFileName(&openBox);
////    std::string = buffer;
////    Sprite s = new Sprite(buffer);
////    return s;
//}
