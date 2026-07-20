#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QDialog>

namespace Ui { class ErrorForm; }

class ErrorForm : public QDialog
{
    Q_OBJECT
public:
    explicit ErrorForm(const QString &errorMsg = QString(), QWidget *parent = nullptr);
    ~ErrorForm() override;

private slots:
    void onCopyClicked();
    void onViewLogClicked();
    void onOKClicked();

private:
    Ui::ErrorForm *ui;
    QString m_errorMsg;
};

#endif // ERRORFORM_H