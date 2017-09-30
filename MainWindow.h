#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

#include <QUrl>

#include <memory>

class KRecentFilesAction;

namespace Ui {
class MainWindow;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void readConfig();
    void writeConfig();

    virtual bool queryClose() override;

protected slots:
    void open();
    void open(QUrl const&);

    void save();
    void saveAs();
    void saveAs(QUrl const&);

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    QUrl m_location;
    bool m_modified = false;

    KRecentFilesAction* m_recentFiles;
};

#endif
