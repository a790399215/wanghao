#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <vector>
#include <QFile>
#include "file_ui.h"

using namespace std;


/***************************************************************************
 * TODO:定义FCB用于存储文件的属性，存储在FCB文件中
 * 每个FCB都与一个文件相对应，在对文件进行相应操作时，应及时更新对应文件的FCB参数
 ****************************************************************************/
class FCB : public QObject
{
    Q_OBJECT

public:
    explicit FCB(QObject *parent = 0);
    ~FCB(){}
private:
    string name;            //文件名
    int start_loc;          //文件数据在磁盘中的起始块
    int size;               //文件占用块大小
    int right;              //文件操作权限,0可读可写，1只读，缺省为0
    int type;               //文件种类：0代表文件夹，1代表文件
    string time;            //创建时间/最后修改时间
public:
    FCB(string name,int start_loc,int size,int right,int type);
};


/***************************************************************************
 * TODO:定义文件对象，表示一个数据文件的示例
 *
 ****************************************************************************/
class FILEs : public QObject
{
    Q_OBJECT

public:
    explicit FILEs(QObject *parent = 0);
    ~FILEs(){}
private:
    string file_name;       //文件名
    string file_path;       //文件路径

public:
    Files(string name, string path);
    string Get_Filename()   //获取文件名
    {
        return file_name;
    }
    string Get_Filepath()   //获取文件路径
    {
        return file_path;
    }

};



/***************************************************************************
 * TODO:定义文件目录节点类，表示文件结构组织
 *
 ****************************************************************************/
class Directory_Node : public QObject
{
    Q_OBJECT

public:
    explicit Directory_Node(QObject *parent = 0);
    ~Directory_Node(){}
public:
    Directory_Node(string filepath,int blocknum);

    string filepath;              //路径名
    int blocknum;                 //路径指向物理块号(可以是下一级目录，也可以是文件)
};

class Directory : public QObject
{
    Q_OBJECT

public:
    explicit Directory(QObject *parent = 0);
    Directory();
    ~Directory(){}
private:
    int father_node;                          //上一级目录块号
    int child_num = 0;
    Directory_Node* child[10];                //最多有10个子目录，初始化为NULL
public:
    int Get_FatherNode()                      //获取上一级目录块号
    {
        return father_node;
    }
    void Set_FatherNode(int num)              //设置上一级的目录块号
    {
        father_node = num;
    }
    Directory_Node* Get_Directory(int loc)    //获取第loc个目录项指针
    {
        return child[loc];
    }
};



/***************************************************************************
 * TODO:定义文件系统对象，对磁盘文件进行管理，并具有一系列操作功能
 *
 ****************************************************************************/
class FileManager : public QObject
{
    Q_OBJECT

public:
    ~FileManager(){}
private:

    vector<FILE*> opened_files;                     //当前打开的文件
    string current_path;                            //文件系统当前路径
    const string home_path = "C:\\";                //根目录
    string bit_map;

signals:
    void Path_Error();                              //输入路径错误信号
private slots:
    string Get_Inputpath(string inputpath);         //返回string为当前路径，证明路径错误
public:
    const int DIRECTORY_LOC = 0;                    //文件的目录部分在磁盘的第一块
    const int BITS_MAP = 1;                         //位图在磁盘的第二块
    const int FILES_START = 2;                      //文件从磁盘的第三块开始
    const int BLOCK_SIZE = 1024;                    //每个物理块大小为1024KB
    const int BLOCK_COUNT = 1000;                   //共有1000个物理块
    const int DISK_SIZE = 1048576;                  //硬盘总空间大小
    FileManager();

    //文件系统界面指针
    File_Ui *file_system_ui = NULL;

    //获取文件系统当前所在路径
    string Get_Currentpath()
    {
        return current_path;
    }
    void Set_Currentpath(string path)
    {
        current_path = path;
    }
    //获取文件系统根路径
    string Get_Homepath()
    {
        return home_path;
    }

    //获取序号最小的空闲块序号
    int Get_AvailableBlock();

    //判断路径是否正确
    bool If_PathCorrect(string inputpath);

    //打开文件操作
    Open_File(string filepath);

    //删除FCB
    Delete_FCB(string filename);
    //删除文件操作
    Delete_File(string filename,string filepath);
    //删除树中节点
    Delete_FileNode(string filename);

    //新建FCB
    Create_FCB(string filename);
    //新建文件操作
    Create_File(string filename,string filepath);
    //新建树中节点
    Create_FileNode(string filename,string filepath);

    //关闭文件操作
    Close_File(string filename);
    //根据文件名查找文件
    Find_Filebyname(string filename);
    //判断文件还是文件夹
    bool if_FileorFolder();

    //移动文件
    Move_File(string oldpath,string newpath);
    //移动文件节点
    Move_FileNode(string oldpath,string newpath);

    //读磁盘某一块操作
    string Read_DiskBlock(int linenum);
    //写磁盘操作
    bool Write_DiskBlock();

    //读FCB操作
    vector<FCB> Read_FCB();
    //写FCB操作
    Write_FCB(vector<FCB> fcbs);

    //复制文件
    Copy_File();
    //剪切文件
    Cut_File();
    //粘贴文件
    Paste_File();
};

#endif // FILEMANAGER_H
