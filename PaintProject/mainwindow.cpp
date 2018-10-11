#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),   ui(new Ui::MainWindow)
{
    int initpenSize = 5;
    //showFullScreen();
    ui->setupUi(this);
    ui->penSizeLabel->setText(QString::number(initpenSize));
    ui->penSizeSlide->setValue(initpenSize);
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)) , this , SLOT( colorSelectGroup_clicked(QAbstractButton*)));
}


void MainWindow::makePDF()
{
    QString path = QDir::currentPath().append("/").append( QDate::currentDate().toString("yyyyMMdd") ).append("/");
    QString filename = path.append("TmpPdf.pdf");
    QPdfWriter pdfWriter(filename);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);

    QPainter painter(&pdfWriter);

    for ( int i = 0 ; i < qImageList.length() ; i++)
    {
        painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*8.3,pdfWriter.logicalDpiY()*11.7), QPixmap::fromImage(qImageList[i]));
        if ( i != qImageList.length()-1 ) pdfWriter.newPage();
    }

    painter.end();

}


void MainWindow::saveFile()
{

    // to save Path
    QString path = QDir::currentPath().append("/").append( QDate::currentDate().toString("yyyyMMdd") ).append("/");
    QDir dir(path);

    if(!dir.exists())
        dir.mkdir(path);


    // To make FileName
    QString format = "yyyyMMddHHmmss";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString DateTimeString = currentDateTime.toString(format);
    const QString fileName = path.append( DateTimeString ).append(".png");

    // To save Image
    QImage image = ui->canvas->getImage();

    // Add to List
    qImageList.append(image);

    CanvasWidget::isSave = true;

    saveImage(image,fileName);
}


void MainWindow::saveImage(QImage image, const QString &fileName)
{

    image.save(fileName);
    //        undoStack->clear();

}

void MainWindow::penColor()
{
    const QColor newColor = QColorDialog::getColor(ui->canvas->getColor());
    if (newColor.isValid()) {
        ui->canvas->setColor(newColor);
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->colorShow->setStyleSheet(qss);
    }
}




MainWindow::~MainWindow()
{
    //delete ui;
}
// #################### Button Click #############
void MainWindow::on_makePdfButton_clicked()
{
    if (CanvasWidget::isSave == false )      // When end the lecture auto save
        saveFile();
    if (qImageList.isEmpty() == true)       // no image no makePDF
        return;
    makePDF();
}

void MainWindow::on_saveButton_clicked()
{
    if (CanvasWidget::isSave == true )      // if already save then don't save Image
        return;
    saveFile();
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

void MainWindow::on_customColor_clicked()
{
    penColor();
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
    // want to save when click "All clear" -> saveFile();
    ui->canvas->clearAll();
}

void MainWindow::on_undoButton_clicked()
{
    if (ui->canvas->undoStack.count() > 1  )
    {
        ui->canvas->redoStack.push(ui->canvas->undoStack.pop());
        ui->canvas->setImage( ui->canvas->undoStack.top() );
    }
    else
        return;
}

void MainWindow::on_redoButton_clicked()
{
        if (ui->canvas->redoStack.count() > 1  )
        {
            ui->canvas->setImage( ui->canvas->redoStack.top() );
            ui->canvas->undoStack.push(ui->canvas->redoStack.pop());
        }
        else
            return;
}
