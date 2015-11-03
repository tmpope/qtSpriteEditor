#include "mainwindow.h"
#include "ui_mainwindow.h"

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
