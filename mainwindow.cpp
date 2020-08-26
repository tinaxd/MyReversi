#include "mainwindow.h"
#include "boardview.h"
#include "reversiboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *rb = new ReversiBoard(this);
    auto *bv = new BoardView(this);
    bv->setBoard(rb);
    setCentralWidget(bv);
}

MainWindow::~MainWindow()
{
}

