#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QtCore>
#include <QtGui>

#include <add_user.h>
#include <del_user.h>
#include <authorized.h>
#include <string_check.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	other_window_working(false)
{
	ui->setupUi(this);

	webcam.open(0);


	if (!webcam.isOpened()) {
		ui->debug_info->setText("error: webcam not detected");
		return;
	}
	if (!log_in_manager.setup()) {
		return;
	}
	if (!recognizer.load_face_cascade()) {
		return;
	}

	dispatcher = new QTimer(this);
	connect(dispatcher, SIGNAL(timeout()), this, SLOT(process()));
	dispatcher->start(20);
}

void MainWindow::process()
{
	webcam.read(capture);

	if (capture.empty()) {
		return;
	}
	cv::cvtColor(capture, capture, CV_BGR2RGB);
	recognizer.detect(detected_faces, capture);

	if (other_window_working) {
		return;
	}


	QImage qimage_capture((uchar*)capture.data, capture.cols, capture.rows,
		capture.step, QImage::Format_RGB888);

	ui->captured_image->setPixmap(QPixmap::fromImage(qimage_capture));
}

MainWindow::~MainWindow()
{
	delete ui;
	delete dispatcher;
}

void MainWindow::on_actionAdd_user_triggered()
{
	add_user add_user_window(capture, log_in_manager);
	add_user_window.setModal(true);
	other_window_working = true;
	add_user_window.exec();
	other_window_working = false;

}

void MainWindow::on_actionDelete_user_triggered()
{
	del_user del_user_window(log_in_manager);
	del_user_window.setModal(true);
	other_window_working = true;
	del_user_window.exec();
	other_window_working = false;
}

void MainWindow::on_login_button_clicked()
{
	std::string login = (ui->login->text()).toUtf8().constData();
	std::string password = (ui->password->text()).toUtf8().constData();
	if (login.empty() || password.empty()) {
		ui->debug_info->setText("Login or password empty");
		return;
	}

	if (!str_only_letters(login) || !str_only_letters(password)) {
		ui->debug_info->setText("Login or password has not permitted characters");
		return;
	}

	if (!log_in_manager.validate(login, password)) {
		ui->debug_info->setText("Access not granted");
		return;
	}

	if(login != constant::root) {
		face::trainer t;
		t.get_data(login);
		cv::Ptr<cv::FaceRecognizer> cv_recognizer;
		t.train(cv_recognizer);
		if (detected_faces.empty()) {
			ui->debug_info->setText("Face not detected");
			return;
		}
		if (!recognizer.recognize(detected_faces[0], cv_recognizer)) {
				ui->debug_info->setText("Face do not match");
				return;
		}
	}
	ui->debug_info->setText("User validated");


	authorized auth(log_in_manager);
	auth.setModal(true);
	other_window_working = true;
	auth.exec();
	other_window_working = false;
}
