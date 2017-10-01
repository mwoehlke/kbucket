#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

#include <QUrl>

#include <memory>

class KRecentFilesAction;

namespace KIO { class Job; }

namespace Ui { class MainWindow; }

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

    void setContent(QByteArray const&, QUrl const&);
    void updateTitleBar();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;

    KIO::Job* m_job = nullptr;
    QUrl m_location;
    bool m_modified = false;
    QString m_listName;

    KRecentFilesAction* m_recentFiles;
};

#endif
