#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Instantiate some variables
    colorDialog = new QColorDialog(this);
//    canvas = new CanvasWidget(this);

//    setCentralWidget(canvas);


    // Connect dem sockets
    connect(ui->selectColorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorDialogColorSelected()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete colorDialog;
}

/*
 * The slots - we're playing the slots
 */

/* Shows the color dialog window */
void MainWindow::showColorDialog(){
    // Get a selected color from the user
    colorDialog->show();
}

/* Fires when the color dialog window closes with a color selected */
void MainWindow::colorDialogColorSelected(){
    colorDialog->hide();

    // Get the selected color
    currentColor = colorDialog->selectedColor();

    // Get the palette and put the currentColor into that palette
    QPalette palette = ui->currentColorWidget->palette();
    palette.setColor(ui->currentColorWidget->backgroundRole(), currentColor);
    palette.setColor(ui->currentColorWidget->foregroundRole(), currentColor);
    ui->currentColorWidget->setPalette(palette);
    ui->currentColorWidget->setAutoFillBackground(true);
}
