#include "file_ui.h"
#include "ui_file_ui.h"

File_Ui::File_Ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File_Ui)
{
    ui->setupUi(this);
    current_path = "C:\\";
    ui->InputPath_lineEdit->setText(QString::fromStdString(current_path));
}

File_Ui::~File_Ui()
{
    delete ui;
}

void File_Ui::on_New_FileButton_clicked()
{
    //获取输入的路径文本
    emit Get_Inputpath(ui->InputPath_lineEdit->text().toStdString());
}

void File_Ui::on_Open_FileButton_clicked()
{
    emit Get_Inputpath(ui->InputPath_lineEdit->text().toStdString());
}

void File_Ui::Path_Error()
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->information(NULL, QString("Error"), QString("输入路径有误，请重新输入！"));
    ui->InputPath_lineEdit->clear();
    ui->InputPath_lineEdit->setText(QString::fromStdString(current_path));
}
