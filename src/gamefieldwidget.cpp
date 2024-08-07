#include "gamefieldwidget.h"
#include "gamemodel.h"
#include "ui_gamefieldwidget.h"

#include <QResizeEvent>

GameFieldWidget::GameFieldWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameFieldWidget)
{
    ui->setupUi(this);

    auto m = ui->fieldView->selectionModel();
    ui->fieldView->setModel(new GameModel(this));
    delete m;
    ui->fieldView->horizontalHeader()->setVisible(false);
    ui->fieldView->verticalHeader()->setVisible(false);
    ui->fieldView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->fieldView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->fieldView, &QAbstractItemView::clicked, this, &GameFieldWidget::onCellClicked);
}

GameFieldWidget::~GameFieldWidget()
{
    delete ui;
}

void GameFieldWidget::resizeEvent(QResizeEvent *event)
{
    const auto model = ui->fieldView->model();
    const auto fieldSize = ui->fieldView->size();
    const auto columnWidth = fieldSize.width() / model->columnCount();
    const auto rowHeight = fieldSize.height() / model->rowCount();

    for (int i = 0; i < model->columnCount(); ++i) {
        ui->fieldView->setColumnWidth(i, columnWidth);
    }
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->fieldView->setRowHeight(i, rowHeight);
    }

    event->accept();
}

void GameFieldWidget::onCellClicked(const QModelIndex &index)
{
    auto model = ui->fieldView->model();
    model->setData(index, QColor(255, 255, 255), Qt::BackgroundRole);
}
