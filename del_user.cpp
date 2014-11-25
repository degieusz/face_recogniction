#include "del_user.h"
#include "ui_del_user.h"
#include "trainer.h"

del_user::del_user(login_manager& log_in_manager_, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::del_user),
	log_in_manager(log_in_manager_)
{
	ui->setupUi(this);
}

del_user::~del_user()
{
	delete ui;
}

void del_user::on_delete_user_clicked()
{
	std::string login = (ui->login->text()).toUtf8().constData();

	std::string root_password = (ui->root_password->text()).toUtf8().constData();
	if (login.empty() || root_password.empty()) {
		ui->debug_info->setText("error: one of fields empty");
		return;
	}
	if (!log_in_manager.remove(login, root_password)) {
		ui->debug_info->setText("Cannot delete user from the database");
		return;
	}

	face::trainer trainer;
	if (!trainer.remove_data(login)) {
		ui->debug_info->setText("Cannot delete user data directory");
		return;
	}
	ui->debug_info->setText("User deleted");
}
