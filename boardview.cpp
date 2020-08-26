#include "boardview.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

BoardView::BoardView(QWidget *parent) : QWidget(parent)
{

}

void BoardView::setBoard(ReversiBoard *board)
{
    m_board = board;
    connect(m_board, &ReversiBoard::changed, this, &BoardView::requestRedraw);
}

void BoardView::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    if (!m_board) return;

    painter.fillRect(0, 0, 8 * cellLength, 8 * cellLength, QBrush(Qt::gray));

    painter.setPen(QPen(Qt::black));

    for (int row=0; row<=8; row++) {
        painter.drawLine(QLine{QPoint{0, row * cellLength}, QPoint{8 * cellLength, row * cellLength}});
    }
    for (int col=0; col<=8; col++) {
        painter.drawLine(QLine{QPoint{col * cellLength, 0}, QPoint{col * cellLength, 8 * cellLength}});
    }

    for (int i=0; i<64; i++) {
        const auto row = i / 8;
        const auto col = i % 8;
        QPoint center{col * cellLength + cellLength / 2, row * cellLength + cellLength / 2};

        const auto radius = static_cast<int>(cellLength * 0.4);

        switch (m_board->get(i)) {
        case DISK_NONE:
            continue;
        case DISK_BLACK:
            painter.setBrush(QBrush(Qt::black));
            break;
        case DISK_WHITE:
            painter.setBrush(QBrush(Qt::white));
            break;
        }

        painter.drawEllipse(center, radius, radius);
    }
}

void BoardView::requestRedraw()
{
    update();
}
