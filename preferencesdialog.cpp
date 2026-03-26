#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QSettings>
#include <QMessageBox>

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(QIcon(":/icons/windows.png"), "Windows");
    ui->comboBox->addItem(QIcon(":/icons/fusion.png"), "Fusion");
    loadSettings();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_buttonBox_accepted()
{
    QMessageBox::information(this, "Settings", "Restart the application");
    saveSettings();
    accept();
}

void PreferencesDialog::on_buttonBox_rejected()
{
    reject();
}

void PreferencesDialog::loadSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    ui->comboBox->setCurrentText(settings.value("style").toString());
    settings.endGroup();
}

void PreferencesDialog::saveSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    settings.setValue("style", ui->comboBox->currentText());
    settings.endGroup();
}