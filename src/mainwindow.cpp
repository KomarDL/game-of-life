#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_startGamePushButton(new QPushButton(this)),
      m_stopGamePushButton(new QPushButton(this)),
      m_clearFieldPushButton(new QPushButton(this)),
      m_gameField(new GameField(this)),
      m_colorDialog(new QColorDialog(this)),
      m_gameLogic(new GameLogic(this))
{
    ui->setupUi(this);
    setupUi();

    connect(m_startGamePushButton, &QPushButton::clicked, this,
            &MainWindow::startGame);
    connect(m_stopGamePushButton, &QPushButton::clicked, this,
            &MainWindow::stopGame);
    connect(m_clearFieldPushButton, &QPushButton::clicked, this,
            &MainWindow::clearField);

    connect(m_colorDialog, &QColorDialog::currentColorChanged, m_gameField,
            &GameField::setCellBrushColor);
    connect(m_gameField, &GameField::fieldSizeChanged, m_gameLogic, &GameLogic::fieldWasChanged);
    connect(m_gameLogic, &GameLogic::updateUi, m_gameField, QOverload<>::of(&QWidget::update));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    m_gameLogic->startGame(m_gameField->field());
}

void MainWindow::stopGame()
{
    m_gameLogic->stopGame();
}

void MainWindow::clearField()
{
    m_gameField->clearField();
}

void MainWindow::setupUi()
{
    ui->gridLayout->addWidget(m_gameField, 0, 0, 4, 1);
    ui->gridLayout->addWidget(m_startGamePushButton, 0, 1);
    ui->gridLayout->addWidget(m_stopGamePushButton, 1, 1);
    ui->gridLayout->addWidget(m_clearFieldPushButton, 2, 1);
    ui->gridLayout->addWidget(m_colorDialog, 3, 1);
    // make the color selection dialog a subwindow
    m_colorDialog->setWindowFlags(Qt::SubWindow);
    m_colorDialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);
    // configure size policies
    m_gameField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_startGamePushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_stopGamePushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_clearFieldPushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_colorDialog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    // add text to buttons
    m_startGamePushButton->setText(QStringLiteral("Start game"));
    m_stopGamePushButton->setText(QStringLiteral("Stop game"));
    m_clearFieldPushButton->setText(QStringLiteral("Clear field"));
}
