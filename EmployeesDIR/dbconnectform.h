#ifndef DBCONNECTFORM_H
#define DBCONNECTFORM_H

#include <QDialog>

namespace Ui { class DBConnectForm; }

class DBConnectForm : public QDialog
{
    Q_OBJECT
public:
    explicit DBConnectForm(QWidget *parent = nullptr);
    ~DBConnectForm() override;

private slots:
    void onTypeChanged(int index);
    void onPathChoose();
    void onConfirm();
    void onCancel();

private:
    Ui::DBConnectForm *ui;
};

#endif // DBCONNECTFORM_H