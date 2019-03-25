#ifndef FILE_UI_H
#define FILE_UI_H

#include <QWidget>
#include <iostream>
#include <QMessageBox>
#include <QDebug>
using namespace std;

namespace Ui {
class File_Ui;
}

class File_Ui : public QWidget
{
    Q_OBJECT

public:
    explicit File_Ui(QWidget *parent = 0);
    ~File_Ui();

signals:
    void Get_Inputpath(string);                 //获取界面输入的路径
private slots:
    void on_New_FileButton_clicked();

    void on_Open_FileButton_clicked();

    void Path_Error();                          //用户输入的路径错误

private:
    Ui::File_Ui *ui;
    string current_path;
    string home_path = "C:\\";
};

#endif // FILE_UI_H
