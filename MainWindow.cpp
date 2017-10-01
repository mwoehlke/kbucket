#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <KIO/StoredTransferJob>

#include <KActionCollection>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KStandardAction>
#include <KTextEdit>

#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>

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
    auto const& url = QFileDialog::getOpenFileUrl(this, i18n("Open List"), {},
                                                  i18n("JSON Lists (*.json)"));

    if (!url.isEmpty())
        open(url);
}

//-----------------------------------------------------------------------------
void MainWindow::open(QUrl const& url)
{
    m_job = KIO::storedGet(url);

    connect(m_job, &KIO::Job::result, [this, url](KJob* job){
        if (job != m_job)
            return;

        if (job->error())
        {
            KMessageBox::error(this, job->errorString());
            return;
        }

        auto* const storedJob = qobject_cast<KIO::StoredTransferJob*>(job);
        setContent(storedJob->data(), url);

        job->deleteLater();
        m_job = nullptr;
    });

    m_job->exec();
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

//-----------------------------------------------------------------------------
void MainWindow::setContent(QByteArray const& data, QUrl const& location)
{
    QJsonParseError error;
    auto const& doc = QJsonDocument::fromJson(data, &error);
    if (!doc.isObject())
    {
        KMessageBox::error(this, error.errorString());
        return;
    }

    auto const& list = doc.object();
    auto const& name = list.value(QStringLiteral("name"));
    m_listName = (name.isString() ? name.toString() : i18n("(Untitled)"));

    m_location = location;
    m_modified = false;
    m_recentFiles->addUrl(location);

    updateTitleBar();
}

//-----------------------------------------------------------------------------
void MainWindow::updateTitleBar()
{
    auto const m = (m_modified ? QStringLiteral(" [*]") : QString{});
    setCaption(m_listName + m);
}
