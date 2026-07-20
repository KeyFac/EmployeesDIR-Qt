#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QStringList>

class Employee
{
public:
    Employee() = default;
    Employee(int id, const QString &name, const QString &sex, const QString &number,
             const QString &comment, const QString &email, const QString &edu, const QString &salary);

    int id() const { return m_id; }

    QStringList getInfo() const;
    void changeInfo(const QString &name, const QString &sex, const QString &number,
                    const QString &comment, const QString &email, const QString &edu,
                    const QString &salary);
    void changeInfo(const QStringList &lst);

private:
    int m_id = 0;
    QString m_name;
    QString m_sex;
    QString m_number;
    QString m_comment;
    QString m_email;
    QString m_edu;
    QString m_salary;
};

#endif // EMPLOYEE_H