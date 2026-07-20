#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>

namespace Ui { class SettingsForm; }

class SettingsForm : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm() override;

signals:
    void configReloaded();

private slots:
    void onLanguageChanged(int index);
    void onSourceChanged(int index);
    void onCheckNow();
    void onDBSettings();
    void onOK();
    void onCancel();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H