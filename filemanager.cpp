#include "filemanager.h"

FILEs::Files(string path, string name)
{
    file_name = name;
    file_path = path;
}

Directory_Node::Directory_Node(string filepath,int blocknum)
{
    this->filepath = filepath;
    this->blocknum = blocknum;
}

Directory::Directory()
{
    father_node = -1;
    for(int i = 0;i < 10;i++)
    {
        child[i] = NULL;
    }
}

FCB::FCB(string name, int start_loc, int size, int right, int type)
{
    this->name = name;
    this->start_loc = start_loc;
    this->size = size;
    this->right = right;
    this->type = type;
}

FileManager::FileManager()
{
    current_path = "C:\\";
    bit_map = (1000, '0');                    //位图初始化1000个0
    bit_map[0] = 1;
    bit_map[1] = 1;                           //注意减一对应
}

//判断输入路径是否正确
bool If_PathCorrect(string inputpath)
{
    return false;
}

//获取正确的文件路径
string FileManager::Get_Inputpath(string inputpath)
{
    if(If_PathCorrect(inputpath))
    {
        emit Path_Error();
        return "";
    }

}

bool FileManager::If_PathCorrect(string inputpath)
{
    return true;
}

//读取磁盘的某一块
string FileManager::Read_DiskBlock(int linenum)
{
    int i = 0;
    QFile file("Disk.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    while(!file.atEnd() && i < linenum)      //还没有到指定行
    {
        file.readLine();                     //读掉一行
        i++;                                 //向下一行
    }
    if(i == linenum)                         //读到正确行数
    {
        QByteArray line = file.readLine();
        return line.toStdString();
    }
    else                                    //读取行数超过磁盘最大块数，错误
        return "";
}


//获取序号最小的空闲块
int FileManager::Get_AvailableBlock()
{
    int length = bit_map.length();
    int i;
    for(i = 2;i < length;i++)
    {
        if(bit_map[i] == 0)
            break;
    }
    return i;
}
