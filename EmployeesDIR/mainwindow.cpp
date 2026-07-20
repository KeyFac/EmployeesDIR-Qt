#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "employeelist.h"
#include "errorform.h"
#include "settingsform.h"

#include <QApplication>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Hide debug menu in release builds
#ifndef QT_NO_DEBUG
    ui->menuDebug->menuAction()->setVisible(true);
#else
    ui->menuDebug->menuAction()->setVisible(false);
#endif

    // Connect menu actions
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onSettings);
    connect(ui->actionExit, &QAction::triggered, this, [this]() {
        if (QMessageBox::question(this, QString(), tr("Really want to exit?")) == QMessageBox::Yes)
            QApplication::quit();
    });
    connect(ui->actionNewEmployee, &QAction::triggered, this, &MainWindow::onNewClicked);
    connect(ui->actionEditInfo, &QAction::triggered, this, &MainWindow::onEditClicked);
    connect(ui->actionDeleteEmployee, &QAction::triggered, this, &MainWindow::onDeleteClicked);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAbout);
    connect(ui->actionTestDebug, &QAction::triggered, this, [this]() {
        EmployeeList::appendEmployee("name", "sex", "number", "comment", "email", "edu", "salary");
        flushWindow();
    });
    connect(ui->actionErrorFormDebug, &QAction::triggered, this, [this]() {
        ErrorForm form("Test error message", this);
        form.exec();
    });
    connect(ui->actionDbConnectDebug, &QAction::triggered, this, [this]() {
        // DBConnectForm placeholder
    });

    // Connect list selection
    connect(ui->m_listWidget, &QListWidget::currentRowChanged,
            this, &MainWindow::onEmployeeSelected);

    // Connect buttons
    connect(ui->m_editBtn, &QPushButton::clicked, this, &MainWindow::onEditClicked);
    connect(ui->m_deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(ui->m_newBtn, &QPushButton::clicked, this, &MainWindow::onNewClicked);
    connect(ui->m_confirmBtn, &QPushButton::clicked, this, &MainWindow::onConfirmClicked);
    connect(ui->m_cancelBtn, &QPushButton::clicked, this, &MainWindow::onCancelClicked);

    retranslateUi();
    flushWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::retranslateUi()
{
    // Append ":" to field titles — ui text is just the base key
    ui->m_nameTitle->setText(tr("name") + ":");
    ui->m_sexTitle->setText(tr("sex") + ":");
    ui->m_numberTitle->setText(tr("number") + ":");
    ui->m_commentTitle->setText(tr("comment") + ":");
    ui->m_emailTitle->setText(tr("email") + ":");
    ui->m_eduTitle->setText(tr("edu") + ":");
    ui->m_salaryTitle->setText(tr("salary") + ":");

    setWindowTitle(QStringLiteral("EmployeesDIR - 3.1"));
}

void MainWindow::flushWindow()
{
    ui->m_listWidget->blockSignals(true);
    ui->m_listWidget->clear();
    for (const auto &emp : EmployeeList::employees)
        ui->m_listWidget->addItem(emp.getInfo()[0]);
    ui->m_listWidget->blockSignals(false);

    ui->m_nameLabel->clear();
    ui->m_sexLabel->clear();
    ui->m_numberLabel->clear();
    ui->m_commentLabel->clear();
    ui->m_emailLabel->clear();
    ui->m_eduLabel->clear();
    ui->m_salaryLabel->clear();

    exitEditMode();
}

void MainWindow::onEmployeeSelected(int row)
{
    if (row < 0 || row >= EmployeeList::employees.size())
        return;

    const auto &emp = EmployeeList::employees[row];
    QStringList info = emp.getInfo();
    ui->m_nameLabel->setText(ui->m_nameTitle->text() + " " + info[0]);
    ui->m_sexLabel->setText(ui->m_sexTitle->text() + " " + info[1]);
    ui->m_numberLabel->setText(ui->m_numberTitle->text() + " " + info[2]);
    ui->m_commentLabel->setText(ui->m_commentTitle->text() + " " + info[3]);
    ui->m_emailLabel->setText(ui->m_emailTitle->text() + " " + info[4]);
    ui->m_eduLabel->setText(ui->m_eduTitle->text() + " " + info[5]);
    ui->m_salaryLabel->setText(ui->m_salaryTitle->text() + " " + info[6]);

    ui->m_editBtn->setFocus();
}

void MainWindow::onEditClicked()
{
    int row = ui->m_listWidget->currentRow();
    if (row < 0) return;

    const auto &emp = EmployeeList::employees[row];
    QStringList info = emp.getInfo();

    ui->m_nameLabel->setText(ui->m_nameTitle->text());
    ui->m_sexLabel->setText(ui->m_sexTitle->text());
    ui->m_numberLabel->setText(ui->m_numberTitle->text());
    ui->m_commentLabel->setText(ui->m_commentTitle->text());
    ui->m_emailLabel->setText(ui->m_emailTitle->text());
    ui->m_eduLabel->setText(ui->m_eduTitle->text());
    ui->m_salaryLabel->setText(ui->m_salaryTitle->text());

    ui->m_nameEdit->setText(info[0]);
    ui->m_sexEdit->setText(info[1]);
    ui->m_numberEdit->setText(info[2]);
    ui->m_commentEdit->setText(info[3]);
    ui->m_emailEdit->setText(info[4]);
    ui->m_eduEdit->setText(info[5]);
    ui->m_salaryEdit->setText(info[6]);

    enterEditMode(false);
}

void MainWindow::onDeleteClicked()
{
    int row = ui->m_listWidget->currentRow();
    if (row < 0) return;

    const auto &emp = EmployeeList::employees[row];
    if (QMessageBox::question(this, QString(),
            tr("Really want to delete: ") + emp.getInfo()[0]) == QMessageBox::Yes)
    {
        EmployeeList::employees.removeAt(row);
        flushWindow();
    }
}

void MainWindow::onNewClicked()
{
    ui->m_nameLabel->setText(ui->m_nameTitle->text());
    ui->m_sexLabel->setText(ui->m_sexTitle->text());
    ui->m_numberLabel->setText(ui->m_numberTitle->text());
    ui->m_commentLabel->setText(ui->m_commentTitle->text());
    ui->m_emailLabel->setText(ui->m_emailTitle->text());
    ui->m_eduLabel->setText(ui->m_eduTitle->text());
    ui->m_salaryLabel->setText(ui->m_salaryTitle->text());

    ui->m_nameEdit->clear();
    ui->m_sexEdit->clear();
    ui->m_numberEdit->clear();
    ui->m_commentEdit->clear();
    ui->m_emailEdit->clear();
    ui->m_eduEdit->clear();
    ui->m_salaryEdit->clear();

    enterEditMode(true);
    ui->m_confirmBtn->setFocus();
}

void MainWindow::onConfirmClicked()
{
    QStringList tmp = {
        ui->m_nameEdit->text(), ui->m_sexEdit->text(), ui->m_numberEdit->text(),
        ui->m_commentEdit->text(), ui->m_emailEdit->text(), ui->m_eduEdit->text(),
        ui->m_salaryEdit->text()
    };

    if (m_mode == "edit") {
        int row = ui->m_listWidget->currentRow();
        if (row >= 0)
            EmployeeList::employees[row].changeInfo(tmp);
    } else if (m_mode == "new") {
        if (!tmp[0].isEmpty())
            EmployeeList::appendEmployee(tmp);
    }

    exitEditMode();
    flushWindow();
    ui->m_editBtn->setFocus();
}

void MainWindow::onCancelClicked()
{
    int row = ui->m_listWidget->currentRow();
    if (row >= 0)
        onEmployeeSelected(row);
    exitEditMode();
    ui->m_editBtn->setFocus();
}

void MainWindow::enterEditMode(bool isNew)
{
    m_mode = isNew ? "new" : "edit";

    ui->m_nameLabel->hide();
    ui->m_sexLabel->hide();
    ui->m_numberLabel->hide();
    ui->m_commentLabel->hide();
    ui->m_emailLabel->hide();
    ui->m_eduLabel->hide();
    ui->m_salaryLabel->hide();

    ui->m_nameEdit->show();
    ui->m_sexEdit->show();
    ui->m_numberEdit->show();
    ui->m_commentEdit->show();
    ui->m_emailEdit->show();
    ui->m_eduEdit->show();
    ui->m_salaryEdit->show();

    ui->m_editBtn->hide();
    ui->m_deleteBtn->hide();
    ui->m_newBtn->hide();
    ui->m_confirmBtn->show();
    ui->m_cancelBtn->show();
}

void MainWindow::exitEditMode()
{
    m_mode = "view";

    ui->m_nameEdit->hide();
    ui->m_sexEdit->hide();
    ui->m_numberEdit->hide();
    ui->m_commentEdit->hide();
    ui->m_emailEdit->hide();
    ui->m_eduEdit->hide();
    ui->m_salaryEdit->hide();

    ui->m_nameLabel->show();
    ui->m_sexLabel->show();
    ui->m_numberLabel->show();
    ui->m_commentLabel->show();
    ui->m_emailLabel->show();
    ui->m_eduLabel->show();
    ui->m_salaryLabel->show();

    ui->m_editBtn->show();
    ui->m_deleteBtn->show();
    ui->m_newBtn->show();
    ui->m_confirmBtn->hide();
    ui->m_cancelBtn->hide();
}

void MainWindow::onSave()
{
    QString path = QFileDialog::getSaveFileName(this,
        tr("Save Employees"),
        QString(),
        tr("Employees (*.employees);;All files (*.*)"));
    if (!path.isEmpty())
        EmployeeList::saveData(path);
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(this,
        tr("Open Employees"),
        QString(),
        tr("Employees (*.employees);;All files (*.*)"));
    if (!path.isEmpty()) {
        EmployeeList::openData(path);
        flushWindow();
    }
}

void MainWindow::onSettings()
{
    auto *form = new SettingsForm(this);
    connect(form, &SettingsForm::configReloaded, this, [this]() {
        Config::load();
        reloadTranslator();
        retranslateUi();
        flushWindow();
    });
    form->setAttribute(Qt::WA_DeleteOnClose);
    form->show();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, QString(),
        QStringLiteral("EmployeesDIR\n"
                       "Version 3.1\n"
                       "Copyright \302\251 2024 GLgele"));
}