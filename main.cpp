#include "mainWindow.h"
#include <QtWidgets/QApplication>
//#pragma execution_character_set("utf-8")    // ��������������⣬ע�⣡����
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMGPro w;
    w.show();
    return a.exec();
}
