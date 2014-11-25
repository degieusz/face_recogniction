#include "add_user.h"
#include "ui_add_user.h"

#include <QtCore>
#include <QtGui>

add_user::add_user(cv::Mat& capture_, login_manager& log_in_manager_, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::add_user),
	capture(capture_),
	log_in_manager(log_in_manager_)
{
	ui->setupUi(this);

	dispatcher = new QTimer(this);
	connect(dispatcher, SIGNAL(timeout()), this, SLOT(process()));
	dispatcher->start(20);
}

void add_user::process()
{
	QImage qimage_capture((uchar*)capture.data, capture.cols, capture.rows,
		capture.step, QImage::Format_RGB888);

	ui->captured_image->setPixmap(QPixmap::fromImage(qimage_capture));
}

add_user::~add_user()
{
	delete ui;
}

void add_user::on_create_text_user_clicked()
{
	std::string login = (ui->login->text()).toUtf8().constData();
	std::string password = (ui->password->text()).toUtf8().constData();
	std::string repeated_password = (ui->repeated_password->text()).toUtf8().constData();
	std::string root_password = (ui->root_password->text()).toUtf8().constData();
	if (login.empty() || password.empty() || repeated_password.empty() || root_password.empty()) {
		ui->debug_prints->appendPlainText("error: one of fields empty");
		return;
	}
	if (password != repeated_password) {
		ui->debug_prints->appendPlainText("password and repeated password not the same");
		return;
	}
	if (!log_in_manager.add(login, password, root_password)) {
		ui->debug_prints->appendPlainText("Cannot add user to the database");
		return;
	}

}
