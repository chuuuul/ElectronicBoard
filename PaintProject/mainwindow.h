#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QFileDialog>
#include <QPdfWriter>
#include <QColorDialog>
#include <QDateTime>
#include <QList>
#include <QPixmap>
#include "canvaswidget.h"

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

private:
    Ui::MainWindow *ui;

    void penColor();


    QList<QImage> qImageList ;
};

#endif // MAINWINDOW_H
