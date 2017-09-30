#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> ui;
};

#endif
