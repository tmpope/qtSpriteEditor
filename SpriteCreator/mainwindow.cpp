#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = new CanvasWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
