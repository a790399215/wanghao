#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(file_system == NULL)
        file_system = new FileManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_File_SystemButton_clicked()
{
    file_system->file_system_ui = new File_Ui();

    //连接获取输入路径的函数
    connect(file_system->file_system_ui,SIGNAL(Get_Inputpath(string)),file_system,SLOT(Get_Inputpath(string)));
    //错误路径提示信息
    connect(file_system,SIGNAL(Path_Error()),file_system->file_system_ui,SLOT(Path_Error()));

    file_system->file_system_ui->show();
}
