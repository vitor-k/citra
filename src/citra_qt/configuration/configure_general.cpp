// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <QMessageBox>
#include "citra_qt/configuration/configure_general.h"
#include "citra_qt/uisettings.h"
#include "core/core.h"
#include "core/settings.h"
#include "ui_configure_general.h"

ConfigureGeneral::ConfigureGeneral(QWidget* parent)
    : QWidget(parent), ui(new Ui::ConfigureGeneral) {

    ui->setupUi(this);
    SetConfiguration();

    connect(ui->toggle_frame_limit, &QCheckBox::toggled, ui->frame_limit, &QSpinBox::setEnabled);

    ui->updateBox->setVisible(UISettings::values.updater_found);
    connect(ui->button_reset_defaults, &QPushButton::clicked, this,
            &ConfigureGeneral::ResetDefaults);

    ui->label_is_n3ds_true->setVisible(Settings::values.is_new_3ds);
    ui->label_GDB_debug->setVisible(Settings::values.use_gdbstub);
    bool messages_to_show = Settings::values.use_gdbstub || Settings::values.is_new_3ds;
    ui->info_messages_group->setVisible(messages_to_show);
}

ConfigureGeneral::~ConfigureGeneral() = default;

void ConfigureGeneral::SetConfiguration() {
    ui->toggle_check_exit->setChecked(UISettings::values.confirm_before_closing);

    ui->toggle_update_check->setChecked(UISettings::values.check_for_update_on_start);
    ui->toggle_auto_update->setChecked(UISettings::values.update_on_close);

    // The first item is "auto-select" with actual value -1, so plus one here will do the trick
    ui->region_combobox->setCurrentIndex(Settings::values.region_value + 1);

    ui->toggle_frame_limit->setChecked(Settings::values.use_frame_limit);
    ui->frame_limit->setEnabled(ui->toggle_frame_limit->isChecked());
    ui->frame_limit->setValue(Settings::values.frame_limit);
}

void ConfigureGeneral::ResetDefaults() {
    QMessageBox::StandardButton answer = QMessageBox::question(
        this, tr("Citra"),
        tr("Are you sure you want to <b>reset your settings</b> and close Citra?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (answer == QMessageBox::No)
        return;

    FileUtil::Delete(FileUtil::GetUserPath(FileUtil::UserPath::ConfigDir) + "qt-config.ini");
    std::exit(0);
}

void ConfigureGeneral::ApplyConfiguration() {
    UISettings::values.confirm_before_closing = ui->toggle_check_exit->isChecked();

    UISettings::values.check_for_update_on_start = ui->toggle_update_check->isChecked();
    UISettings::values.update_on_close = ui->toggle_auto_update->isChecked();

    Settings::values.region_value = ui->region_combobox->currentIndex() - 1;

    Settings::values.use_frame_limit = ui->toggle_frame_limit->isChecked();
    Settings::values.frame_limit = ui->frame_limit->value();
}

void ConfigureGeneral::RetranslateUI() {
    ui->retranslateUi(this);
}
