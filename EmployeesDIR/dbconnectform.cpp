#include "dbconnectform.h"
#include "ui_dbconnectform.h"
#include "config.h"

#include <QFileDialog>

DBConnectForm::DBConnectForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::DBConnectForm)
{
    ui->setupUi(this);

    ui->typeComboBox->addItems({"SQLite", "MySQL"});
    ui->connectionStringTextBox->setText(Config::appConfig.database.connection);

    // Connections
    connect(ui->typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DBConnectForm::onTypeChanged);
    connect(ui->pathChooseButton, &QPushButton::clicked, this, &DBConnectForm::onPathChoose);
    connect(ui->testConnectionButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Testing connection:" << ui->connectionStringTextBox->text();
    });
    connect(ui->confirmButton, &QPushButton::clicked, this, &DBConnectForm::onConfirm);
    connect(ui->cancelButton, &QPushButton::clicked, this, &DBConnectForm::onCancel);
}

DBConnectForm::~DBConnectForm()
{
    delete ui;
}

void DBConnectForm::onTypeChanged(int)
{
    bool isSQLite = ui->typeComboBox->currentText() == "SQLite";
    ui->tabWidget->widget(0)->setEnabled(isSQLite);
    ui->tabWidget->widget(1)->setEnabled(!isSQLite);
}

void DBConnectForm::onPathChoose()
{
    QString path = QFileDialog::getSaveFileName(this,
        tr("Choose SQLite database"),
        QString(),
        tr("SQLite database files (*.db *.sqlite);;All files (*.*)"));
    if (!path.isEmpty())
        ui->connectionStringTextBox->setText(path);
}

void DBConnectForm::onConfirm()
{
    Config::appConfig.database.dbType = ui->typeComboBox->currentText();
    Config::appConfig.database.connection = ui->connectionStringTextBox->text();
    Config::save();
    accept();
}

void DBConnectForm::onCancel()
{
    reject();
}