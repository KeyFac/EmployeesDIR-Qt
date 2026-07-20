#include "config.h"
#include <QCoreApplication>
#include <QDir>

namespace Config {

bool isRDebug = false;
AppConfig appConfig;

static const QString iniPath = QCoreApplication::applicationDirPath() + "/config.ini";

void load()
{
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.beginGroup("Language");
    appConfig.language.lang = settings.value("lang", "en_us").toString();
    settings.endGroup();

    settings.beginGroup("Update");
    appConfig.update.source = settings.value("source", "Github").toString();
    appConfig.update.autoCheck = settings.value("autoCheck", false).toBool();
    settings.endGroup();

    settings.beginGroup("Database");
    appConfig.database.dbType = settings.value("dbType", "SQLite").toString();
    appConfig.database.connection = settings.value("connection", "").toString();
    settings.endGroup();
}

void save()
{
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.beginGroup("Language");
    settings.setValue("lang", appConfig.language.lang);
    settings.endGroup();

    settings.beginGroup("Update");
    settings.setValue("source", appConfig.update.source);
    settings.setValue("autoCheck", appConfig.update.autoCheck);
    settings.endGroup();

    settings.beginGroup("Database");
    settings.setValue("dbType", appConfig.database.dbType);
    settings.setValue("connection", appConfig.database.connection);
    settings.endGroup();

    settings.sync();
}

} // namespace Config