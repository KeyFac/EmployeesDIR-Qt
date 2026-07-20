#include "employeelist.h"
#include "logger.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

namespace EmployeeList {

QVector<Employee> employees;

void saveData(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing:" << path;
        return;
    }

    QDataStream out(&file);
    // Simple binary format: int32 count, then for each employee:
    // 7 space-terminated strings, followed by a newline
    qint32 count = employees.size();
    out.writeRawData(reinterpret_cast<const char*>(&count), sizeof(qint32));

    for (const auto &emp : employees) {
        QStringList lst = emp.getInfo();
        for (const QString &s : lst) {
            QByteArray data = (s + " ").toUtf8();
            out.writeRawData(data.constData(), data.size());
        }
        out.writeRawData("\n", 1);
    }

    file.close();
    qInfo() << "Saved" << count << "employees to" << path;
}

void openData(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading:" << path;
        return;
    }

    QDataStream in(&file);

    // Read count
    qint32 count = 0;
    if (in.readRawData(reinterpret_cast<char*>(&count), sizeof(qint32)) != sizeof(qint32)) {
        qWarning() << "Failed to read count from file";
        file.close();
        return;
    }

    employees.clear();

    for (int i = 0; i < count; ++i) {
        QStringList lst;
        for (int ii = 0; ii < 7; ++ii) {
            QString tmp;
            char chr = 0;
            while (in.readRawData(&chr, 1) == 1 && chr != ' ')
                tmp += QChar(chr);
            lst.append(tmp);
        }
        // Skip trailing newline
        char nl;
        in.readRawData(&nl, 1);

        if (lst.size() == 7)
            appendEmployee(lst);
    }

    file.close();
    qInfo() << "Loaded" << count << "employees from" << path;
}

void appendEmployee(const QString &name, const QString &sex, const QString &number,
                    const QString &comment, const QString &email, const QString &edu,
                    const QString &salary)
{
    employees.append(Employee(0, name.trimmed(), sex.trimmed(), number.trimmed(),
                              comment.trimmed(), email.trimmed(), edu.trimmed(), salary.trimmed()));
}

void appendEmployee(const QStringList &lst)
{
    if (lst.size() >= 7)
        appendEmployee(lst[0], lst[1], lst[2], lst[3], lst[4], lst[5], lst[6]);
}

} // namespace EmployeeList