#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <KActionCollection>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KStandardAction>
#include <KTextEdit>

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    KXmlGuiWindow{parent},
    m_ui{new Ui::MainWindow}
{
    m_ui->setupUi(this);

    auto* const ac = actionCollection();
    KStandardAction::open(this, qOverload<>(&MainWindow::open), ac);
    KStandardAction::save(this, &MainWindow::save, ac);
    KStandardAction::saveAs(this, qOverload<>(&MainWindow::saveAs), ac);
    KStandardAction::quit(qApp, &QApplication::quit, ac);

    m_recentFiles = KStandardAction::openRecent(
        this, qOverload<QUrl const&>(&MainWindow::open), ac);

    setupGUI();
    readConfig();
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
void MainWindow::readConfig()
{
    auto const config = KSharedConfig::openConfig();

    auto const cg = KConfigGroup{config, "MainWindow"};
    m_ui->centralWidget->restoreState(
        cg.readEntry("Splitter", QByteArray{}));

    m_recentFiles->loadEntries(config->group("Recent Files"));
}

//-----------------------------------------------------------------------------
void MainWindow::writeConfig()
{
    auto const config = KSharedConfig::openConfig();

    auto cg = KConfigGroup{config, "MainWindow"};
    cg.writeEntry("Splitter", m_ui->centralWidget->saveState());

    m_recentFiles->saveEntries(KConfigGroup{config, "Recent Files"});

    config->sync();
}

//-----------------------------------------------------------------------------
bool MainWindow::queryClose()
{
    // TODO

    writeConfig();
    return true;
}

//-----------------------------------------------------------------------------
void MainWindow::open()
{
    // TODO
}

//-----------------------------------------------------------------------------
void MainWindow::open(QUrl const& url)
{
    // TODO
}

//-----------------------------------------------------------------------------
void MainWindow::save()
{
    saveAs(m_location);
}

//-----------------------------------------------------------------------------
void MainWindow::saveAs()
{
    // TODO
}

//-----------------------------------------------------------------------------
void MainWindow::saveAs(QUrl const&)
{
    // TODO
}
