#include "del_user.h"
#include "ui_del_user.h"

del_user::del_user(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::del_user)
{
	ui->setupUi(this);
}

del_user::~del_user()
{
	delete ui;
}
