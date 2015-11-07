#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CanvasWidget *canvas;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    std::string Save();
    Sprite* Load();

private:
    Ui::MainWindow *ui;
    Sprite* sprite;
    std::string file;
};

#endif // MAINWINDOW_H
