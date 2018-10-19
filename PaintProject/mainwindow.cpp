#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),   ui(new Ui::MainWindow)
{
    int initpenSize = 5;


    /*** Release Mode ***/
    //showFullScreen();
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    /********************/

    ui->setupUi(this);
    ui->penSizeLabel->setText(QString::number(initpenSize));
    ui->penSizeSlide->setValue(initpenSize);
    ui->colorShow->setStyleSheet("background-color : black; border: 1px solid;");
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)) , this , SLOT( colorSelectGroup_clicked(QAbstractButton*)));
    toggleSetVisible(true);
}


void MainWindow::makePDF()
{
    QString path = QDir::currentPath().append("/").append( QDate::currentDate().toString("yyyyMMdd") ).append("/");
    QString filename = path.append(QTime::currentTime().toString("hhmmss")).append(".pdf");
    QPdfWriter pdfWriter(filename);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);

    QPainter painter(&pdfWriter);

    for ( int i = 0 ; i < qImageList.length() ; i++)
    {
        painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*8.3f,pdfWriter.logicalDpiY()*11.7f), QPixmap::fromImage(qImageList[i]));
        if ( i != qImageList.length()-1 ) pdfWriter.newPage();
    }

    painter.end();

    ui->canvas->clearAll();

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



    saveImage(image,fileName);
}


void MainWindow::saveImage(QImage image, const QString &fileName)
{

    image.save(fileName);

}

void MainWindow::penColor()
{
    const QColor newColor = QColorDialog::getColor(ui->canvas->getColor());
    if (newColor.isValid()) {
        ui->canvas->setColor(newColor);
        QString qss = QString("background-color: %1; border: 1px solid;").arg(newColor.name());
        ui->colorShow->setStyleSheet(qss);
    }
}


void MainWindow::StartDrawing()
{

    ui->canvas->redoStack.clear();
    ui->canvas->undoStack.clear();
    qImageList.clear();
    ui->canvas->clearAll();

}

void MainWindow::infoComboBoxMake()
{
    QStringList departmentList;
    QStringList professorList;
    QStringList courseList;

    // init models
    departmentModel = new QStringListModel();
    professorModel = new QStringListModel();
    courseModel = new QStringListModel();

    //makeModelList(departmentModel,professorModel,courseModel);


    // Read information from Server

    // Spilt information


    // Make StringList each
    departmentList << "Cats" << "Dogs" << "Birds";
    professorList << "kim" << "park";
    courseList << "DataBase" << "NetworkProgramming";

    // Set QStringList to "setStringList" method
    departmentModel -> setStringList(departmentList);
    professorModel -> setStringList(professorList);
    courseModel -> setStringList(courseList);

    // set ui to using "setModel" method
    //ui->comboBox->setModel(departmentModel);



}


void MainWindow::toggleSetVisible(bool canVisible)
{
        ui->infoView->setVisible(canVisible);
        ui->StartButton->setVisible(canVisible);
        ui->canvasMask->setVisible(canVisible);
}


MainWindow::~MainWindow()
{
    //delete ui;
}
// #################### Button Click #############
void MainWindow::on_StartButton_clicked()
{
    StartDrawing();
    toggleSetVisible(false);
}




void MainWindow::on_makePdfButton_clicked()
{
    if (CanvasWidget::isSave == false )      // When end the lecture auto save ( Save "pdf save button" )
    {
        saveFile();
        CanvasWidget::isSave = true;
    }

    if (qImageList.isEmpty() == true)       // no image no makePDF
        return;
    makePDF();
    toggleSetVisible(true);

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
        ui->colorShow->setStyleSheet("background-color : red; border: 1px solid;");
    }
    else if(buttonName == "color_blue")
    {
        selectedColor = Qt::blue;
        ui->colorShow->setStyleSheet("background-color : blue; border: 1px solid;");
    }
    else if(buttonName == "color_green")
    {
        selectedColor = QColor("#008000");
        ui->colorShow->setStyleSheet("background-color : #008000; border: 1px solid;");
    }
    else if(buttonName == "color_black")
    {
        selectedColor = Qt::black;
        ui->colorShow->setStyleSheet("background-color : black; border: 1px solid;");
    }
    else if(buttonName == "color_yellow")
    {
        selectedColor = Qt::yellow;
        ui->colorShow->setStyleSheet("background-color : yellow; border: 1px solid;");
    }
    else if(buttonName == "color_white")
    {
        selectedColor = Qt::white;
        ui->colorShow->setStyleSheet("background-color : white; border: 1px solid;");
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


//################### Redo / Undo #####################
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

