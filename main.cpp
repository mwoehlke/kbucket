#include "MainWindow.h"

#include <KAboutData>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>

namespace
{
    auto copyright = []{
        return i18n("Copyright 2017");
    };

    auto shortDescription = []{
        return i18n("A simple but flexible list editor");
    };

    auto extendedDescription = []{
        return i18n("Blah blah blah...");
    };
}

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app{argc, argv};
    KLocalizedString::setApplicationDomain("KBucket");

    KAboutData aboutData{
        QStringLiteral("KBucket"),  // internal name
        i18n("KBucket"),            // display name
        QStringLiteral("0.1"),
        shortDescription(),
        KAboutLicense::GPL,
        copyright(),
        extendedDescription(),
        QStringLiteral("https://github.com/mwoehlke/kbucket"),
        QStringLiteral("https://github.com/mwoehlke/kbucket/issues")};

    aboutData.addAuthor(
        i18n("Matthew Woehlke"),
        i18n("Lead Developer"),
        QStringLiteral("mwoehlke.floss@gmail.com"));

    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;

    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow* window = new MainWindow();
    window->show();

    return app.exec();
}

