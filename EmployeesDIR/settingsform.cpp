#include "settingsform.h"
#include "ui_settingsform.h"
#include "config.h"
#include "dbconnectform.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    // Populate combos
    ui->downloadComboBox->addItems({"Github", "Gitee"});
    ui->downloadComboBox->setCurrentText(Config::appConfig.update.source);

    ui->languageComboBox->addItem(tr("Chinese"), "zh_cn");
    ui->languageComboBox->addItem(tr("English"), "en_us");
    int idx = ui->languageComboBox->findData(Config::appConfig.language.lang);
    if (idx >= 0) ui->languageComboBox->setCurrentIndex(idx);

    ui->checkUpdateBox->setChecked(Config::appConfig.update.autoCheck);
    ui->dbTypeLabel->setText(Config::appConfig.database.dbType);

    // Connections
    connect(ui->languageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsForm::onLanguageChanged);
    connect(ui->downloadComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsForm::onSourceChanged);
    connect(ui->checkUpdateBox, &QCheckBox::toggled, this, [this](bool checked) {
        Config::appConfig.update.autoCheck = checked;
    });
    connect(ui->checkUpdateButton, &QPushButton::clicked, this, &SettingsForm::onCheckNow);
    connect(ui->dbSetButton, &QPushButton::clicked, this, &SettingsForm::onDBSettings);
    connect(ui->OKButton, &QPushButton::clicked, this, &SettingsForm::onOK);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsForm::onCancel);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::onLanguageChanged(int)
{
    Config::appConfig.language.lang = ui->languageComboBox->currentData().toString();
}

void SettingsForm::onSourceChanged(int)
{
    Config::appConfig.update.source = ui->downloadComboBox->currentText();
}

void SettingsForm::onCheckNow()
{
    qDebug() << "Check update requested, source:" << Config::appConfig.update.source;
}

void SettingsForm::onDBSettings()
{
    DBConnectForm form(this);
    form.exec();
    ui->dbTypeLabel->setText(Config::appConfig.database.dbType);
}

void SettingsForm::onOK()
{
    Config::save();
    emit configReloaded();
    accept();
}

void SettingsForm::onCancel()
{
    reject();
}