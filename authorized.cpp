#include "authorized.h"
#include "ui_authorized.h"
#include <string_check.h>

authorized::authorized(login_manager& log_in_manager_, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::authorized),
	log_in_manager(log_in_manager_)
{
	ui->setupUi(this);

}

authorized::~authorized()
{
	delete ui;
}

void authorized::on_change_password_clicked()
{
	std::string login = (ui->login->text()).toUtf8().constData();
	std::string password = (ui->password->text()).toUtf8().constData();
	std::string repeated_password = (ui->repeated_password->text()).toUtf8().constData();
	std::string old_password = (ui->old_password->text()).toUtf8().constData();
	if (login.empty() || password.empty() || repeated_password.empty() || old_password.empty()) {
		ui->debug_info->setText("Error: one of fields empty");
		return;
	}
	if (!str_only_letters(login) || !str_only_letters(password) || !str_only_letters(repeated_password)
			 || !str_only_letters(old_password)) {
		ui->debug_info->setText("One of fields has not permitted characters");
		return;
	}
	if (password != repeated_password) {
		ui->debug_info->setText("Password and repeated password not the same");
		return;
	}
	if (!log_in_manager.change_password(login, old_password, password)) {
		ui->debug_info->setText("Cannot change user password");
		return;
	}
	ui->debug_info->setText("Password changed");
}
