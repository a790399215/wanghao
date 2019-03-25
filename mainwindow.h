#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_File_SystemButton_clicked();            //文件系统打开槽函数

private:
    Ui::MainWindow *ui;
    FileManager *file_system = NULL;                       //文件系统指针

};

#endif // MAINWINDOW_H
