#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QByteArray>
#include <QTextStream>
#include <stdio.h>
#include <QString>
#include <QTextCursor>
#include <QTimer>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void my_test_slot();
    void timer_read_slots();
private:
    Ui::Widget *ui;
    QPushButton *my_test_button;
    QFile *my_file;
    QFile *service_file;
    QLabel *warn_info_label;
    QPlainTextEdit *return_edit;
    QString str1;
    QLineEdit *send_edit;
    QTimer *timer_read_client;
};

#endif // WIDGET_H
