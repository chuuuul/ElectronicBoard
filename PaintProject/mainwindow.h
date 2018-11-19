#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QPainter>
#include <QMainWindow>
#include <QAbstractButton>
#include <QFileDialog>
#include <QPdfWriter>
#include <QColorDialog>
#include <QDateTime>
#include <QList>
#include <QPixmap>
#include <QStringListModel>


#include "ui_mainwindow.h"
#include "networkCourseInfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartDrawing();


private slots:
    void colorSelectGroup_clicked(QAbstractButton* button);     // color
    void on_penSizeSlide_sliderMoved(int position);             // slider
    void on_penSizeSlide_sliderReleased();
    void on_penSizeSlide_valueChanged(int value);
    void on_clearButton_clicked();                              // clear
    void on_saveButton_clicked();
    void on_makePdfButton_clicked();

    void saveFile();
    void saveImage(QImage saveImage, const QString &fileName);
    void on_customColor_clicked();

    void makePDF();


    void on_undoButton_clicked();
    void on_redoButton_clicked();
    void on_StartButton_clicked();


    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadFinished(QNetworkReply *reply);  // Upload finish slot
    void loadJson();

    void httpRequest(QNetworkReply *p_reply);

    void on_departmentComboBox_currentTextChanged(const QString &arg1);
    void on_professorComboBox_currentTextChanged(const QString &arg1);
    void on_uploadProgressBar_valueChanged(int value);



private:
    Ui::MainWindow *ui;


    // Course Info Combox
    QStringList departmentList;
    QStringList professorList;
    QStringList courseList;

    QStringListModel *departmentModel;
    QStringListModel *professorModel;
    QStringListModel *courseModel;


    // redo undo
    QList<QImage> qImageList;


    // Download Json
    NetworkCourseInfo *netJson;
    QJsonDocument jsonDoc;

    QString departString;
    QString profString;
    QString courseString;

    QString courseInfoString;


    QJsonDocument readJson();

    // associate upload file
    QNetworkAccessManager *ftp_manager;
    QFile *ftp_file;

    // make folder Request
    QNetworkAccessManager *http_manager;


    void uploadFrameVisible(bool visible);

    void allComboBoxInit();
    void toggleSetVisible(bool canVisible);
    void penColor();

    void makeDepartComboBox();
    void makeProfComboBox();
    void makeCourseComboBox();

    void makeDepartList();
    void makeProfList();
    void makeCourseList();

    void startUploadPDF(QString m_folderName, QString m_fileName);
    void startDownloadPDF();


    void httpConnect(QString urlString);
};

#endif // MAINWINDOW_H
