#include "mainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),   ui(new Ui::MainWindow)
{
    //showFullScreen();
    ui->setupUi(this);
    ui->penSizeLabel->setText("5");
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)) , this , SLOT( colorSelectGroup_clicked(QAbstractButton*)));
}


MainWindow::~MainWindow()
{
    //delete ui;
}

//################### Color Button ######################
void MainWindow::colorSelectGroup_clicked(QAbstractButton* button)
{
    QString buttonName = button->objectName();
    QColor selectedColor;

    if(buttonName == "color_red")
    {
        selectedColor = Qt::red;
        ui->colorShow->setStyleSheet("background-color : red;");
    }
    else if(buttonName == "color_blue")
    {
        selectedColor = Qt::blue;
        ui->colorShow->setStyleSheet("background-color : blue;");
    }
    else if(buttonName == "color_green")
    {
        selectedColor = Qt::green;
        ui->colorShow->setStyleSheet("background-color : green;");
    }
    else if(buttonName == "color_black")
    {
        selectedColor = Qt::black;
        ui->colorShow->setStyleSheet("background-color : black;");
    }
    else if(buttonName == "color_yellow")
    {
        selectedColor = Qt::yellow;
        ui->colorShow->setStyleSheet("background-color : yellow;");
    }
    else if(buttonName == "color_white")
    {
        selectedColor = Qt::white;
        ui->colorShow->setStyleSheet("background-color : white;");
    }

    ui->canvas->setColor(selectedColor);
}


//################## Size Slide #########################
void MainWindow::on_penSizeSlide_sliderMoved(int position)
{
    ui->penSizeLabel->setText(QString::number(position) );
}
void MainWindow::on_penSizeSlide_valueChanged(int value)
{
    ui->penSizeLabel->setText(QString::number(value) );
    ui->canvas->setPenSize(value);
}
void MainWindow::on_penSizeSlide_sliderReleased()
{
        ui->canvas->setPenSize(ui->penSizeSlide->value());

}

//################## Clear Paint ########################
void MainWindow::on_clearButton_clicked()
{
    ui->canvas->clearAll();
}
