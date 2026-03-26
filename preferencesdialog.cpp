#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QSettings>
#include <QMessageBox>
#include <QStyleFactory>
#include <QDebug>

void PreferencesDialog::initialize()
{
    populateStyleCombo();
    loadSettings();
}

void PreferencesDialog::populateStyleCombo()
{
    const auto &styleList = QStyleFactory::keys();
    for (const auto &styleName : styleList)
    {
        QString iconUrl = ":/icons/";
        if (styleName.contains("windows", Qt::CaseInsensitive))
        {
            iconUrl += "windows.png";
        }
        else if (styleName.contains("fusion", Qt::CaseInsensitive))
        {
            iconUrl += "fusion.png";
        }
        ui->comboBox->addItem(QIcon(iconUrl), styleName);
    }
}

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    initialize();
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