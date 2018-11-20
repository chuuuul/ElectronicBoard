#include "mainwindow.h"
#include <QTextCodec>
#include <QTranslator>


#define kor(a) QString::fromUtf8(a)
#define comboBoxInitText QString::fromUtf8("선택해주세요")
#define jsonServerURL "http://7ed7cf0d.ngrok.io/smartBoardStart"
#define httpMakeDirURL "http://7ed7cf0d.ngrok.io/makeDir/"
#define httpEndLectureURL "http://7ed7cf0d.ngrok.io/smartBoardEnd/"
#define ftpServer "ftp://chul.duckdns.org/ftp/lecture/"

//#define httpMakeDirURL "http://c2266780.ngrok.io/smartBoardStart/makeDir/"  // 기존서버
//#define jsonServerURL "http://c2266780.ngrok.io/smartBoardStart"




//##############################################
//############# Uploading ######################
//##############################################

void MainWindow::startUploadPDF(QString m_folderName, QString m_fileName)
{
    ftp_file = new QFile(m_fileName);

    QFileInfo fileInfo(*ftp_file);

    QString path = m_folderName.append("/").append( fileInfo.fileName() );

    QUrl url(QString(ftpServer) + path );


    url.setUserName("ftpftp");
    url.setPassword("ftpftp");
    url.setPort(21);


    if (ftp_file->open(QIODevice::ReadOnly))
    {
        uploadFrameVisible(true);

        QNetworkReply *reply = ftp_manager->put(QNetworkRequest(url), ftp_file);
        // And connect to the progress upload signal
        connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::uploadProgress);
    }

}

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),   ui(new Ui::MainWindow)
{
    int initpenSize = 5;

    /*** Release Mode ***/
    //showFullScreen();
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    /********************/

    // Setting Download
    QUrl jsonUrl(jsonServerURL);
    netJson = new NetworkCourseInfo(jsonUrl,this);
    connect(netJson, SIGNAL(jsonDownload() ),SLOT(loadJson()));


    // Setting Painter and Widget
    ui->setupUi(this);
    ui->penSizeLabel->setText(QString::number(initpenSize));
    ui->penSizeSlide->setValue(initpenSize);
    ui->colorShow->setStyleSheet("background-color : black; border: 1px solid;");
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)) , this , SLOT( colorSelectGroup_clicked(QAbstractButton*)));
    toggleSetVisible(true);

    // Setting UploadPDF
    uploadFrameVisible(false);

    // init Course , info list, models
    departmentModel = new QStringListModel();
    professorModel = new QStringListModel();
    courseModel = new QStringListModel();


    ftp_manager = new QNetworkAccessManager(this);
    connect(ftp_manager, &QNetworkAccessManager::finished, this, &MainWindow::uploadFinished);
}

void MainWindow::httpConnect(QString urlString)
{
    http_manager = new QNetworkAccessManager(this);

    QUrl requestURL = urlString.append(departString + "&" + profString + "&" + courseString);
    connect(http_manager, SIGNAL(finished(QNetworkReply*)) , this , SLOT(httpRequest(QNetworkReply*) ));
    QNetworkRequest networkRequest ( requestURL );
    http_manager->get( networkRequest );
}

void MainWindow::httpRequest(QNetworkReply *p_reply)
{
    p_reply->deleteLater();
}

/*
// To test
QJsonDocument MainWindow::readJson()
{
    QString settings;
    QFile file;
    file.setFileName("D:/tmp.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();

    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    //qDebug()<< QString(sd.toJson(QJsonDocument::Compact)) ;        //display Json text
    return sd;
}
*/

void MainWindow::loadJson()
{
    allComboBoxInit();
    jsonDoc = QJsonDocument::fromJson( netJson->getJsonArray() );
    //qDebug()<< QString(jsonDoc.toJson(QJsonDocument::Compact)) ;        //display Json text
    makeDepartList();
    makeDepartComboBox();

}



//##############################################
//############# Uploading ######################
//##############################################


void MainWindow::uploadFinished(QNetworkReply *reply)
{
    if (!reply->error())
   {
       ftp_file->close();
       ftp_file->deleteLater();  // delete object of file
       reply->deleteLater();   // delete object of reply
    }
}

void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    ui->uploadProgressBar->setValue(100 * bytesSent/bytesTotal);

}

void MainWindow::on_uploadProgressBar_valueChanged(int value)
{
    if ( value >= 100 )
    {
        ui->uploadText->setText("Upload Complete");
    }
    else
    {
        ui->uploadText->setText("Uploading...");
    }
}



void MainWindow::uploadFrameVisible(bool visible)
{
    ui->uploadProgressBar->setVisible(visible);
    ui->uploadText->setVisible(visible);

    if (visible == true)
    {
        ui->uploadProgressBar->setValue(0);
        ui->uploadText->setText("Uploading...");
    }
}




MainWindow::~MainWindow()
{
    //delete ui;
}

//######################### Combo Box ####################################

void MainWindow::allComboBoxInit()
{
    departmentList.clear();
    professorList.clear();
    courseList.clear();

    departmentList.append(comboBoxInitText);
    professorList.append(comboBoxInitText);
    courseList.append(comboBoxInitText);

    makeCourseComboBox();
    makeDepartComboBox();
    makeProfComboBox();


    ui->departmentComboBox->setCurrentIndex(0);
    ui->professorComboBox->setCurrentIndex(0);
    ui->courseComboBox->setCurrentIndex(0);

}

void MainWindow::toggleSetVisible(bool canVisible)
{
        ui->infoView->setVisible(canVisible);
        ui->StartButton->setVisible(canVisible);
        ui->canvasMask->setVisible(canVisible);
}


void MainWindow::makeDepartList()
{
    foreach ( QJsonValue var, jsonDoc.array() )
    {
        departmentList.append( var.toObject().value("major").toString() );
    }
}

void MainWindow::makeProfList()
{
    foreach ( QJsonValue var, jsonDoc.array() )
    {
        if (var.toObject().value("major") == ui->departmentComboBox->currentText() )
        {
            professorList.append(var.toObject().value("profName").toString());
            //qDebug()<< var.toObject().value("profName").toString() ;
        }
    }
}

void MainWindow::makeCourseList()
{
    foreach ( QJsonValue var, jsonDoc.array() )
    {
        if (var.toObject().value("major") == ui->departmentComboBox->currentText()
                &&var.toObject().value("profName") == ui->professorComboBox->currentText() )
        {
            courseList.append(var.toObject().value("lectureName").toString());
        }
    }
}

void MainWindow::makeDepartComboBox()
{
    departmentModel -> setStringList(departmentList);
    ui->departmentComboBox->setModel(departmentModel);
    ui->departmentComboBox->setCurrentIndex(0);
}

void MainWindow::makeProfComboBox()
{
    professorModel -> setStringList(professorList);
    ui->professorComboBox->setModel(professorModel);
    ui->professorComboBox->setCurrentIndex(0);
}

void MainWindow::makeCourseComboBox()
{
    courseModel->setStringList(courseList);
    ui->courseComboBox->setModel(courseModel);
    ui->courseComboBox->setCurrentIndex(0);
}


// ############################   PDF / SaveFile   ####################################
void MainWindow::makePDF()
{
    QString path = QDir::currentPath().append("/").append( courseInfoString ).append("/");
    //QString filename = path.append(courseInfoString).append(QDate::currentDate().toString("_MM월dd일")).append(QTime::currentTime().toString("hh시mmss")).append(".pdf");
    QString filename = path.append(courseInfoString).append(QDate::currentDate().toString("_MMdd")).append(QTime::currentTime().toString("hhmm")).append(".pdf");



    QPdfWriter pdfWriter(filename);

    //pdfWriter.setPageSize(QPagedPaintDevice::A4);

    QPainter painter(&pdfWriter);

    for ( int i = 0 ; i < qImageList.length() ; i++)
    {
        painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*8.3f,pdfWriter.logicalDpiY()*11.7f), QPixmap::fromImage(qImageList[i]));
        if ( i != qImageList.length()-1 ) pdfWriter.newPage();
    }

    painter.end();

    // Upload FTP folder
    startUploadPDF(courseInfoString,filename);

    ui->canvas->clearAll();
}


void MainWindow::saveFile()
{

    // to save Path
    QString path = QDir::currentPath().append("/").append( courseInfoString ).append("/");
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


//############################# Drawing ##################################
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


// #################### Button Click #############
void MainWindow::on_StartButton_clicked()
{
    if ( ui->courseComboBox->currentText() != comboBoxInitText && ui->courseComboBox->currentText() != nullptr )
    {


        StartDrawing();

        uploadFrameVisible(false);
        toggleSetVisible(false);

        departString = ui->departmentComboBox->currentText();
        profString = ui->professorComboBox->currentText();
        courseString = ui->courseComboBox->currentText();


        courseInfoString = QString("%1_%2_%3").arg(departString).arg(profString).arg(courseString);

        //comboBox Clear
        professorList.clear();
        courseList.clear();

        professorList.append(comboBoxInitText);
        courseList.append(comboBoxInitText);

        makeProfComboBox();
        makeCourseComboBox();


        ui->departmentComboBox->setCurrentIndex(0);
        ui->professorComboBox->setCurrentIndex(0);
        ui->courseComboBox->setCurrentIndex(0);

        httpConnect(httpMakeDirURL);
    }

}




void MainWindow::on_makePdfButton_clicked()
{
    if (CanvasWidget::isSave == false )      // When end the lecture auto save ( Save "pdf save button" )
    {
        saveFile();
        CanvasWidget::isSave = true;
    }

    if (qImageList.isEmpty() == true)       // If (no image)  no makePDF
        return;
    makePDF();

    httpConnect(httpEndLectureURL);     //####
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


//################### Undo #####################
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
//################### Redo #####################
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


//################### ComboBox #####################
void MainWindow::on_departmentComboBox_currentTextChanged(const QString &arg1)
{

    professorList.clear();
    courseList.clear();

    professorList.append(comboBoxInitText);
    courseList.append(comboBoxInitText);

    if (arg1 != comboBoxInitText)
        makeProfList();

    makeProfComboBox();
    makeCourseComboBox();

}

void MainWindow::on_professorComboBox_currentTextChanged(const QString &arg1)
{
    courseList.clear();
    courseList.append(comboBoxInitText);

    if (arg1 != comboBoxInitText)
        makeCourseList();

    makeCourseComboBox();

}

