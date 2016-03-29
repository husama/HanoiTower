#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("HanoiTower");
    mainPanel = new hanoiPanel();
    setFixedHeight(720);
    setFixedWidth(1280);
    setCentralWidget(mainPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
