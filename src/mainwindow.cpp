#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QColorDialog *colorDialog = new QColorDialog(this);
//    colorDialog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gridLayout->addWidget(colorDialog, 0, 1);
    colorDialog->setWindowFlags(Qt::SubWindow);
    /* a few options that we must set for it to work nicely */
    colorDialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);
}

MainWindow::~MainWindow()
{
    delete ui;
}

