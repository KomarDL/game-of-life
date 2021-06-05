#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , colorDialog(new QColorDialog(this))
{
    ui->setupUi(this);
    // make the color selection dialog a subwindow
    ui->gridLayout->addWidget(colorDialog, 0, 1);
    colorDialog->setWindowFlags(Qt::SubWindow);
    colorDialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    connect(colorDialog, &QColorDialog::currentColorChanged, ui->gameField, &GameField::setCellColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

