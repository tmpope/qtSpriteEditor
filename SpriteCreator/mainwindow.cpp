#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = new CanvasWidget(12, 12);
//    canvas->setSpriteDimensions(12, 12);
    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canvas;
}

std::string MainWindow::Save(Sprite sprite){

    std::string ret = sprite.toString();
    return ret;
}

Sprite MainWindow::Load(std::string file){
    const int BUFSIZE = 1024;
    char buffer[BUFSIZE] = {0};
    OPENFILENAME openBox = {0};
    openBox.lStructSize = sizeof( ofns );
    openBox.lpstrFile = buffer;
    openBox.nMaxFile = BUFSIZE;
    openBox.lpstrTitle = file.c_str();
    GetOpenFileName(&openBox);
    std::string = buffer;
    Sprite s = new Sprite(buffer);
    return s;
}
