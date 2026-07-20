#include "mainwindow.h"
#include "config.h"
#include "logger.h"

#include <QApplication>
#include <QTranslator>
#include <QDir>

// Global translator pointer for runtime language switching
static QTranslator *s_translator = nullptr;

void reloadTranslator()
{
    if (!s_translator)
        return;

    QApplication::instance()->removeTranslator(s_translator);

    QString langCode = Config::appConfig.language.lang;
    QString qtLang = langCode;
    if (qtLang.contains('_')) {
        auto parts = qtLang.split('_');
        if (parts.size() == 2)
            qtLang = parts[0] + "_" + parts[1].toUpper();
    }

    QString tsPath = QApplication::applicationDirPath() + "/i18n/EmployeesDIR_" + qtLang;
    if (s_translator->load(tsPath)) {
        QApplication::instance()->installTranslator(s_translator);
        qDebug() << "Loaded translation:" << tsPath;
    } else {
        qWarning() << "Translation not found for:" << langCode;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Parse --debug flag
    bool debugMode = false;
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "--debug") {
            debugMode = true;
            break;
        }
    }

    Config::isRDebug = debugMode;
    installLogger(debugMode);
    qInfo() << "Entering application.";

    // Load config
    Config::load();

    // Setup global translator
    s_translator = new QTranslator(&a);
    reloadTranslator();

    // Ensure config.ini exists
    if (!QFile::exists(QApplication::applicationDirPath() + "/config.ini"))
        Config::save();

    MainWindow w;
    w.show();

    int ret = QApplication::exec();
    qInfo() << "Exiting application.";
    return ret;
}