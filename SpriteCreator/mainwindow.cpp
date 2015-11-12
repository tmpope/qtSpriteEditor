#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "sprite.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include <QTimer>
#include <QColorDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::string file = "";

    colorDialog = new QColorDialog();

    playbackTimer = new QTimer();
    playbackTimer->setInterval(1000 / ui->fpsSlider->value());
    playbackTimer->start();

    playbackFrame = 0;

    ui->frameSelectorSlider->setRange(0, 0);

    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveSprite()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadSprite()));

    connect(ui->fpsSlider, SIGNAL(sliderMoved(int)), this, SLOT(setFramesPerSecond()));
    connect(playbackTimer, SIGNAL(timeout()), this, SLOT(updatePlaybackWidget()));
    connect(ui->colorSelectorButton, SIGNAL(clicked(bool)), this, SLOT(showColorDialog()));

    connect(ui->frameSelectorSlider, SIGNAL(sliderMoved(int)), this, SLOT(showSelectedFrame()));

    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorDialogColorSelected()));

    connect(ui->penButton, SIGNAL(clicked(bool)), this, SLOT(penToolSelected()));
    connect(ui->eyeDropperButton, SIGNAL(clicked(bool)), this, SLOT(eyeDropperSelected()));
    connect(ui->paintBucketButton, SIGNAL(clicked(bool)), this, SLOT(paintBucketSelected()));
    connect(ui->cloneFrameButton, SIGNAL(clicked(bool)), this, SLOT(cloneFrame()));

    connect(ui->actionNewFrame, SIGNAL(triggered(bool)), this, SLOT(newFrame()));
    connect(ui->actionExport, SIGNAL(triggered(bool)), this, SLOT(exportGif()));
    connect(ui->actionNewSprite, SIGNAL(triggered(bool)), this, SLOT(newSprite()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete playbackTimer;
    delete colorDialog;
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


void MainWindow::updatePlaybackWidget()
{
    if(++playbackFrame >= ui->canvas->getSprite()->getFrameCount())
        playbackFrame = 0;

    Sprite* sprite = ui->canvas->getSprite();

    QPixmap pixmap(sprite->getWidth(), sprite->getHeight());
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);

    for(int xPos = 0; xPos < sprite->getWidth(); xPos++)
    {
        for(int yPos = 0; yPos < sprite->getHeight(); yPos++)
        {
            QRect rect(xPos, yPos, 1, 1);
            struct Sprite::color pixelColor = sprite->getPixel(xPos, yPos, playbackFrame);
            QColor color(pixelColor.r, pixelColor.g, pixelColor.b);
            painter.setPen(color);
            painter.fillRect(rect, color);
        }
    }

    ui->playbackLabel->setPixmap(pixmap);
}

void MainWindow::setFramesPerSecond()
{
    if(ui->fpsSlider->value() == 0)
        playbackTimer->setInterval(0);
    else
        playbackTimer->setInterval(1000 / ui->fpsSlider->value());
    std::cout << "Set the fps: " << ui->fpsSlider->value() << std::endl;
}

void MainWindow::showColorDialog(){
    // Get a selected color from the user
    std::cout << "Showing color dialog." << std::endl;
    colorDialog->show();
}

void MainWindow::colorDialogColorSelected()
{
    colorDialog->hide();

    // Get the selected color
    QColor selectedColor = colorDialog->selectedColor();
    int *r = new int(0);
    int *g = new int(0);
    int *b = new int(0);
    int *a = new int(0);

    selectedColor.getRgb(r, g, b, a);

    ui->canvas->setCurrentColor(*r, *g, *b, *a);
}


void MainWindow::penToolSelected()
{
    ui->canvas->setCurrentTool(CanvasWidget::PENCIL);
}


void MainWindow::eyeDropperSelected()
{
    ui->canvas->setCurrentTool(CanvasWidget::EYE_DROPPER);
}


void MainWindow::paintBucketSelected()
{
    ui->canvas->setCurrentTool(CanvasWidget::BUCKET);
}

void MainWindow::exportGif()
{
    // TODO: Test this please Taylor!!!
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
    QString QfileName = dialog.getSaveFileName( this, tr("Save Project"), "C://", "GIF File(*.gif)");

    ui->canvas->save(QfileName.toStdString());

    file = QfileName.toStdString();
    QMessageBox::information(this, tr("File"), tr("File Saved"));

//    ui->canvas->getSprite()->exportToGif(file, ui->fpsSlider->value());
}

void MainWindow::importGif()
{
    // TODO: Test this please Taylor!!!
    QString QfileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "C://", "Sprite Sheet Project(*.ssp);;Text Files(*.txt)");
    std::cout << "File name: " << QfileName.toStdString() << std::endl;
    QFile inputFile(QfileName);

    file = QfileName.toStdString();

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

//    ui->canvas->loadSpriteFromGif(file, true);
}

void MainWindow::newFrame()
{
    ui->canvas->getSprite()->addFrame();
    ui->frameSelectorSlider->setRange(0, ui->canvas->getSprite()->getFrameCount() - 1);
}

void MainWindow::newSprite()
{
    int width = QInputDialog::getInt(this, "Width Please", "Please provide a width:", 1, 1, 64, 1);
    int height = QInputDialog::getInt(this, "Height Please", "Please provide a height:", 1, 1, 64, 1);

    ui->canvas->createNewSprite(width, height);
}

void MainWindow::cloneFrame()
{
    ui->canvas->getSprite()->cloneFrame(canvas->getCurrentFrame());
    ui->frameSelectorSlider->setRange(0, ui->canvas->getSprite()->getFrameCount() - 1);
}

void MainWindow::toggleOnionSkin()
{

}

void MainWindow::showSelectedFrame()
{
    int currentFrame = ui->frameSelectorSlider->value();
    ui->canvas->setCurrentFrame(currentFrame);
}










