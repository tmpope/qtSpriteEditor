#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::string file;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief saveSprite
     *
     * Save a sprite to a file.
     */
    void saveSprite();

    /**
     * @brief loadSprite
     *
     * Load a sprite to a file.
     */
    void loadSprite();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
