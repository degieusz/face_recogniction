#include "authorized.h"
#include "ui_authorized.h"

authorized::authorized(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::authorized)
{
	ui->setupUi(this);
}

authorized::~authorized()
{
	delete ui;
}
