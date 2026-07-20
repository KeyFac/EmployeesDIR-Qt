#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QMessageLogContext>
#include <QMutex>
#include <QString>

void installLogger(bool debugMode);

class Logger
{
public:
    static Logger &instance();
    void messageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &msg);
    void setDebugMode(bool debug) { m_debugMode = debug; }

private:
    Logger();
    ~Logger();
    QFile m_logFile;
    QMutex m_mutex;
    bool m_debugMode = false;
};

#endif // LOGGER_H