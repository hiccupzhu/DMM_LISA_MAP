#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineRaw->setText("|80|0|6|0|0|0|3|0|");
    ui->labelSpec->setText("|8:SYS_ADDR|1:Rsv|3:SYS_SIZE|2:SDRC_INTL|2:SDRC_ADDRSPC|6:Rsv|2:SDRC_MAP|8:SDRC_ADDR|");

    connect(ui->pushButtonDown, SIGNAL(clicked()), this, SLOT(btnDownClick()));
    connect(ui->pushButtonUp, SIGNAL(clicked()), this, SLOT(btnUpClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnDownClick()
{
    int nums[8];
    unsigned int ret = 0;
    QString raw = ui->lineRaw->text();
    QStringList raws = raw.split("|");

    qDebug() << "raws.size()=" << raws.size();
    raws.removeLast();
    raws.removeFirst();
    for(int i = 0; i < raws.size(); i++){
        qDebug() << "  " << raws[i];
        nums[i] = raws[i].toInt(NULL, 16);
    }

    ret |= ((nums[0] & 0xFF) << 24);
    ret |= ((nums[1] & 0x1) << 23);
    ret |= ((nums[2] & 0x7) << 20);
    ret |= ((nums[3] & 0x3) << 18);
    ret |= ((nums[4] & 0x3) << 16);
    ret |= ((nums[5] & 0x1F) << 10);
    ret |= ((nums[6] & 0x3) << 8);
    ret |= ((nums[7] & 0xFF));

    QString sv;
    sv.sprintf("0x%08X", ret);

    ui->lineValue->setText(sv);
}

void MainWindow::btnUpClick()
{
    QString sv;
    int nums[8];
    unsigned int ret = 0;

    sv = ui->lineValue->text();
    ret = sv.toUInt(NULL, 16);

    qDebug("0x%08X", ret);

    nums[0] = (ret >> 24) & 0xFF;
    nums[1] = (ret >> 23) & 0x1;
    nums[2] = (ret >> 20) & 0x7;
    nums[3] = (ret >> 18) & 0x3;
    nums[4] = (ret >> 16) & 0x3;
    nums[5] = (ret >> 10) & 0x1F;
    nums[6] = (ret >> 8) & 0x3;
    nums[7] = ret & 0xFF;

    QString raw;
    raw.sprintf("|%X|%X|%X|%X|%X|%X|%X|%X|",
                nums[0], nums[1], nums[2], nums[3],
                nums[4], nums[5], nums[6], nums[7]);

    ui->lineRaw->setText(raw);
}
