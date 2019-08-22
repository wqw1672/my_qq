#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //加入文本编码解决汉字乱码问题
    QTextCodec *codec = QTextCodec::codecForName("System");    //获取系统编码
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    Widget w;
    w.show();

    return a.exec();
}
