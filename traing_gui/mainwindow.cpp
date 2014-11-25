#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QtCore>
#include <QtGui>

#include <add_user.h>
#include <del_user.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	webcam.open(0);


	if (!webcam.isOpened()) {
		//ui->debug_prints->appendPlainText("error: webcam not detected");
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
	QImage qimage_capture((uchar*)capture.data, capture.cols, capture.rows,
		capture.step, QImage::Format_RGB888);

	ui->captured_image->setPixmap(QPixmap::fromImage(qimage_capture));

}

void MainWindow::on_triggered()
{
	std::cout << "action triggered";
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionAdd_user_triggered()
{
	add_user add_user_window;
	add_user_window.setModal(true);
	add_user_window.exec();

}

void MainWindow::on_actionDelete_user_triggered()
{
	del_user del_user_window;
	del_user_window.setModal(true);
	del_user_window.exec();
}
