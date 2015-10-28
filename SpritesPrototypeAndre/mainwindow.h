#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include "canvaswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QColorDialog *colorDialog; // Dialog window for a color selector
    QColor currentColor; // The current color we are drawing with

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showColorDialog(); // Shows the color dialog
    void colorDialogColorSelected(); // Shows the selected color

private:
    Ui::MainWindow *ui;
    CanvasWidget *canvas;
};

#endif // MAINWINDOW_H
