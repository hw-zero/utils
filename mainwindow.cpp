#include <string.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define BURSIZE 2048

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int hex2dec(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else if ('a' <= c && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if ('A' <= c && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return -1;
    }
}

char dec2hex(short int c)
{
    if (0 <= c && c <= 9)
    {
        return c + '0';
    }
    else if (10 <= c && c <= 15)
    {
        return c + 'A' - 10;
    }
    else
    {
        return -1;
    }
}

void MainWindow::on_urlencode_clicked()
{
    int i = 0;
    const char *url;
    int len = 0;
    QString input;
    char res[BURSIZE];
    int res_len = 0;
//    QString output;

    /* 清空输出文本框 */
    ui->textBrowser->clear();

    /* 获取用户文本框输入 */
    input = ui->textEdit->toPlainText();

    /* 将QString转化为char * */
    std::string str = input.toStdString();
    url = str.c_str();

    /* 获取字符串长度 */
    len = strlen(url);

    for (i = 0; i < len; ++i)
    {
        char c = url[i];
        if (    ('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z') ||
                c == '/' || c == '.')
        {
            res[res_len++] = c;
        }
        else
        {
            int j = (short int)c;
            if (j < 0)
                j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1 * 16;
            res[res_len++] = '%';
            res[res_len++] = dec2hex(i1);
            res[res_len++] = dec2hex(i0);
        }
    }
    res[res_len] = '\0';

//    output = QString(QLatin1String(res));

    /* 将结果输出到文本框 */
//    ui->textBrowser->setText(output);
    ui->textBrowser->setText(QString::fromUtf8(res));
}

void MainWindow::on_urldecode_clicked()
{
    int i = 0;
    const char *url;
    QString input;
    int len = 0;
    char res[BURSIZE];
    int res_len = 0;
//    QString output;

    /* 清空输出文本框 */
    ui->textBrowser->clear();

    /* 获取用户文本框输入 */
    input = ui->textEdit->toPlainText();

    /* 将QString转化为char * */
    std::string str = input.toStdString();
    url = str.c_str();

    /* 获取字符串长度 */
    len = strlen(url);

    for (i = 0; i < len; ++i)
    {
        char c = url[i];
        if (c != '%')
        {
            res[res_len++] = c;
        }
        else
        {
            char c1 = url[++i];
            char c0 = url[++i];
            int num = 0;
            num = hex2dec(c1) * 16 + hex2dec(c0);
            res[res_len++] = num;
        }
    }
    res[res_len] = '\0';

//    output = QString(QLatin1String(res));

    /* 将结果输出到文本框 */
    ui->textBrowser->setText(QString::fromUtf8(res));
}
