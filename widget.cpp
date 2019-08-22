#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //ui->setupUi(this);
    this->setFixedSize(400,300);
    this->setWindowTitle(QString::fromLocal8Bit("客户端"));
    this->move(50,50);
    this->my_test_button=new QPushButton(this);
    this->my_test_button->resize(100,40);
    this->my_test_button->move(this->width()-120,this->height()-100);
    this->my_test_button->setText(QString::fromLocal8Bit("发送服务器"));
    connect(this->my_test_button,SIGNAL(clicked()),this,SLOT(my_test_slot()));
    this->my_test_button->setStyleSheet(QString::fromUtf8("QPushButton\n"
                                                          "{\n"
                                                          "    font-family:Microsoft Yahei;\n"
                                                          "    font:14pt;\n"
                                                          "    color:white;\n"
                                                          "    background-color:rgb(156,156,156);\n"
                                                          "    border-radius:5px;\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:hover\n"
                                                          "{\n"
                                                          "    background-color:rgb(196,196,196);\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:pressed\n"
                                                          "{\n"
                                                          "    background-color:rgb(176,176,176);\n"
                                                          "    padding-left:3px;\n"
                                                          "    padding-top:3px;\n"
                                                        "}"));
    //左下角提醒打开文件信息
    this->warn_info_label=new QLabel(this);
    this->warn_info_label->resize(200,30);
    this->warn_info_label->move(10,this->height()-30);
    //信息显示窗口
    this->return_edit=new QPlainTextEdit(this);
    this->return_edit->resize(350,180);
    this->return_edit->move((this->width()-350)/2,5);
    //发送编辑框
    this->send_edit=new QLineEdit(this);
    this->send_edit->resize(250,40);
    this->send_edit->move(20,this->height()-100);
    //定时读取客户端文件内容
    this->timer_read_client=new QTimer(this);
    connect(this->timer_read_client,SIGNAL(timeout()),this,SLOT(timer_read_slots()));
    this->timer_read_client->start(100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::my_test_slot()
{
    //qDebug()<<QString::fromLocal8Bit("这是个测试按钮");
    this->service_file=new QFile("/tmp/service.txt");
    //打开只写文档，换行写入
    if(this->service_file->open(QIODevice::WriteOnly | QIODevice::Text /*| QIODevice::Append*/ ))
    {
        QString str3=this->send_edit->text();
        //判断一下，输入框是否为空
        if(str3 != NULL)
        {
            //追加文本
            this->return_edit->appendPlainText(QString::fromLocal8Bit("正在写入服务端"));
            this->return_edit->appendPlainText(str3);
            //定位到文件末尾
            QTextStream my_in(this->service_file);
            //my_in.seek(this->service_file->size());
            my_in << str3 << endl;
            this->return_edit->appendPlainText(QString::fromLocal8Bit("写入完成"));
            this->service_file->close();
        }
        else
        {
            this->return_edit->appendPlainText(QString::fromLocal8Bit("输入框不能为空！"));
        }
    }
}

//定时读取客户端内容
void Widget::timer_read_slots()
{
    //文件操作
    this->my_file=new QFile("/tmp/client.txt");
    //以只读的形式打开文本文档
    if(this->my_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        //return;
        //qDebug()<<QString::fromLocal8Bit("打开文件啦");
        this->warn_info_label->setText(QString::fromLocal8Bit("链接服务器成功"));
        //回到文件头
        this->my_file->seek(0);
        this->str1="";
        //按行读取文件
        while(!this->my_file->atEnd())
        {
            QByteArray line=this->my_file->readLine();
            QString str2(QString::fromLocal8Bit(line));
            str1 =str1+str2;
            //qDebug()<<str2;
            this->return_edit->appendPlainText(QString::fromLocal8Bit("接收服务器数据"));
            this->return_edit->appendPlainText(str1);
        }
        //清空文件内容
        this->my_file->resize(0);
        //关闭文件
        this->my_file->close();
    }
    else
    {
        qDebug()<<QString::fromLocal8Bit("没有找到文件");
        this->warn_info_label->setText(QString::fromLocal8Bit("链接服务器失败"));
    }
}
