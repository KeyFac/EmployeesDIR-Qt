#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui { class MainWindow; }

// Reload Qt translator from current Config::appConfig.language.lang
void reloadTranslator();

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void retranslateUi();

private slots:
    void onEmployeeSelected(int row);
    void onEditClicked();
    void onDeleteClicked();
    void onNewClicked();
    void onConfirmClicked();
    void onCancelClicked();
    void onSave();
    void onOpen();
    void onSettings();
    void onAbout();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void flushWindow();
    void enterEditMode(bool isNew);
    void exitEditMode();

    Ui::MainWindow *ui;
    QString m_mode; // "view", "edit", "new"
};

#endif // MAINWINDOW_H