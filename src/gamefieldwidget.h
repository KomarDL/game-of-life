#pragma once

#include <QWidget>

namespace Ui {
class GameFieldWidget;
}

class GameFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(QWidget *parent = nullptr);
    ~GameFieldWidget();

protected:
    void resizeEvent(QResizeEvent *event) override;

private Q_SLOTS:
    void onCellClicked(const QModelIndex &index);

private:
    Ui::GameFieldWidget *ui;
};
