#include "employee.h"

Employee::Employee(int id, const QString &name, const QString &sex, const QString &number,
                   const QString &comment, const QString &email, const QString &edu,
                   const QString &salary)
    : m_id(id), m_name(name), m_sex(sex), m_number(number), m_comment(comment),
      m_email(email), m_edu(edu), m_salary(salary)
{
}

QStringList Employee::getInfo() const
{
    return { m_name, m_sex, m_number, m_comment, m_email, m_edu, m_salary };
}

void Employee::changeInfo(const QString &name, const QString &sex, const QString &number,
                          const QString &comment, const QString &email, const QString &edu,
                          const QString &salary)
{
    m_name = name;
    m_sex = sex;
    m_number = number;
    m_comment = comment;
    m_email = email;
    m_edu = edu;
    m_salary = salary;
}

void Employee::changeInfo(const QStringList &lst)
{
    if (lst.size() >= 7)
        changeInfo(lst[0], lst[1], lst[2], lst[3], lst[4], lst[5], lst[6]);
}