#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv/highgui.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	webcam.open(0);

	if (!webcam.isOpened()) {
		ui->debug_prints->appendPlainText("error: webcam not detected");
		return;
	}

	process_frame_timer = new QTimer(this);
	connect(process_frame_timer, SIGNAL(timeout()), this, SLOT(process_frame_and_update_gui()));

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pause_resume_clicked()
{
	if (process_frame_timer->isActive()) {
		process_frame_timer->stop();
		ui->pause_resume->setText("Resume");
	}
	else {
		process_frame_timer->start(20);
		ui->pause_resume->setText("Pause");
	}
}

void MainWindow::process_frame_and_update_gui()
{
	webcam.read(original_matrix);

	if (original_matrix.empty()) {
		return;
	}

//	cv::inRange(original_matrix, cv::Scalar(0,0,175), cv::Scalar(100,100,256), processed_matrix);
//	cv::GaussianBlur(processed_matrix, processed_matrix, cv::Size(9,9), 1.5);
//	cv::HoughCircles(processed_matrix, circles, CV_HOUGH_GRADIENT, 2,
//									 processed_matrix.rows / 4, 100, 50, 10, 400);

//	for (cit = circles.begin(); cit != circles.end(); ++cit) {
//		ui->debug_prints->appendPlainText(QString("ball position x=")
//				 + QString::number((*cit)[0]).rightJustified(4, '') + QString(", y=")
//				 + QString::number((*cit)[1]).rightJustified(4, '') + QString(", radius =") +
//				QString::number((*cit)[2], 'f', 3).rightJustified(7, ' '));

//		cv::circle(original_matrix, cv::Point((int)(*cit)[0], (int)(*cit)[1]),
//				3, cv::Scalar(0,255,0), CV_FILLED);

//		cv::circle(original_matrix, cv::Point((int)(*cit)[0], (int)(*cit)[1]),
//				(int)(*cit)[2], cv::Scalar(0,0,255), 3);

//	}
		//opencv uses bgr, qt uses rgb
		cv::cvtColor(original_matrix, original_matrix, CV_BGR2RGB);

		// convert from opencv to qt image format
		QImage qimage_original((uchar*)original_matrix.data, original_matrix.cols, original_matrix.rows,
													 original_matrix.step, QImage::Format_RGB888);

//		QImage qimage_processed((uchar*)processed_matrix.data, processed_matrix.cols, processed_matrix.rows,
//													 processed_matrix.step, QImage::Format_Indexed8);

		ui->original_image->setPixmap(QPixmap::fromImage(qimage_original));
//		ui->processed_image->setPixmap(QPixmap::fromImage(qimage_processed));
}

//}

void MainWindow::on_pushButton_clicked()
{
//	if (!original_matrix.empty()) {
	cv::Mat gray_matrix;
	cvtColor(original_matrix, gray_matrix, CV_BGR2GRAY);
		cv::imwrite("/home/dge/work/face_recognition/capture.jpg", gray_matrix);
//	}

}
