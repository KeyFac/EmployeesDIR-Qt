#include "logger.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

static Logger *g_logger = nullptr;

static void messageHandlerForward(QtMsgType type, const QMessageLogContext &ctx, const QString &msg)
{
    if (g_logger)
        g_logger->messageHandler(type, ctx, msg);
}

void installLogger(bool debugMode)
{
    Logger::instance().setDebugMode(debugMode);
}

Logger &Logger::instance()
{
    static Logger inst;
    return inst;
}

Logger::Logger()
{
    // Ensure logs directory exists
    QString logDir = QCoreApplication::applicationDirPath() + "/logs";
    QDir().mkpath(logDir);

    QString logPath = logDir + "/" + QDateTime::currentDateTime().toString("yyyyMMdd") + ".log";
    m_logFile.setFileName(logPath);
    if (m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        qInstallMessageHandler(messageHandlerForward);
    }

    // Default pattern shows just the message
    qSetMessagePattern("%{message}");
}

Logger::~Logger()
{
    qInstallMessageHandler(nullptr);
    if (m_logFile.isOpen())
        m_logFile.close();
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &msg)
{
    QMutexLocker locker(&m_mutex);

    QString levelStr;
    switch (type) {
    case QtDebugMsg:    levelStr = "DEBUG"; break;
    case QtInfoMsg:     levelStr = "INFO"; break;
    case QtWarningMsg:  levelStr = "WARN"; break;
    case QtCriticalMsg: levelStr = "ERROR"; break;
    case QtFatalMsg:    levelStr = "FATAL"; break;
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString formatted = QString("[%1] %2: %3").arg(timestamp, levelStr, msg);

    // Write to file
    if (m_logFile.isOpen()) {
        QTextStream stream(&m_logFile);
        stream << formatted << "\n";
        stream.flush();
    }

    // Console output (always on for debug, only errors+warnings otherwise)
    if (m_debugMode || type >= QtWarningMsg) {
        fprintf(stderr, "%s\n", qPrintable(formatted));
        fflush(stderr);
    }

    if (type == QtFatalMsg)
        abort();
}