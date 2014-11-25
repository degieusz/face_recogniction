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

	if (!recognizer.load_face_cascade()) {
		return;
	}

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
	login = (ui->login->text()).toUtf8().constData();
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

	if (saved_faces.size() == face::constant::learned_faces_no) {
		trainer.prepare_data(login, saved_faces);
	}

}

void add_user::on_capture_img_button_clicked()
{
	std::vector<cv::Mat> detected_faces;
	recognizer.detect(detected_faces, capture);
	if (detected_faces.size() > 0 && saved_faces.size() < face::constant::learned_faces_no) {
		saved_faces.push_back(detected_faces[0]);
		ui->debug_prints->appendPlainText("Face saved");
	}

	if (saved_faces.size() == face::constant::learned_faces_no) {
		ui->create_text_user->setEnabled(true);
		ui->debug_prints->appendPlainText("Faces acquisition finished. Now you can create user.");
	}
}
