#include "MainWindow.h"
#include "ui_MainWindow.h"

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    KXmlGuiWindow{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
    setupGUI();
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}
