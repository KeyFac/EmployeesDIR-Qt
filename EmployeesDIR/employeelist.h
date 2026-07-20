#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

#include <QVector>
#include <QString>
#include "employee.h"

namespace EmployeeList {

extern QVector<Employee> employees;

void saveData(const QString &path);
void openData(const QString &path);
void appendEmployee(const QString &name, const QString &sex, const QString &number,
                    const QString &comment, const QString &email, const QString &edu,
                    const QString &salary);
void appendEmployee(const QStringList &lst);

} // namespace EmployeeList

#endif // EMPLOYEELIST_H