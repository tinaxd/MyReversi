#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include "reversiboard.h"

class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);

    void setBoard(ReversiBoard *m_board);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    ReversiBoard *m_board;

    int cellLength = 70;

signals:

public slots:
    void requestRedraw();
};

#endif // BOARDVIEW_H
