#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSettings>

struct LanguageConfig {
    QString lang = "en_us";
};

struct UpdateConfig {
    QString source = "Github";
    bool autoCheck = false;
};

struct DatabaseConfig {
    QString dbType = "SQLite";
    QString connection;
};

struct AppConfig {
    LanguageConfig language;
    UpdateConfig update;
    DatabaseConfig database;
};

namespace Config {

extern bool isRDebug;
extern AppConfig appConfig;

void load();
void save();

} // namespace Config

#endif // CONFIG_H