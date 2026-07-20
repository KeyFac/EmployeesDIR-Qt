#include "errorform.h"
#include "ui_errorform.h"

#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>

ErrorForm::ErrorForm(const QString &errorMsg, QWidget *parent)
    : QDialog(parent), ui(new Ui::ErrorForm), m_errorMsg(errorMsg)
{
    ui->setupUi(this);
    if (!m_errorMsg.isEmpty())
        ui->errorLabel->setText(m_errorMsg);

    connect(ui->copyButton, &QPushButton::clicked, this, &ErrorForm::onCopyClicked);
    connect(ui->viewLogButton, &QPushButton::clicked, this, &ErrorForm::onViewLogClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &ErrorForm::onOKClicked);
}

ErrorForm::~ErrorForm()
{
    delete ui;
}

void ErrorForm::onCopyClicked()
{
    QApplication::clipboard()->setText(m_errorMsg);
}

void ErrorForm::onViewLogClicked()
{
    QString logPath = QApplication::applicationDirPath() + "/logs";
    QDesktopServices::openUrl(QUrl::fromLocalFile(logPath));
}

void ErrorForm::onOKClicked()
{
    accept();
}