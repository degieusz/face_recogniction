#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv/highgui.h"
#include <QtCore>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <sstream>

#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/contrib/contrib.hpp"

//
#include "authenticator.h"
//

using namespace cv;
using namespace std;

namespace constant {
const string face_cascade_name = "/home/dge/work/face_recogniction/haarcascade_frontalface_alt.xml";

}
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	detected_faces_saved_no(0)
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

void MainWindow::detect_face(cv::Mat img, cv::CascadeClassifier& face_cascade, vector<Rect> &faces)
{
		Mat img_gray;

		cvtColor(img, img_gray, CV_BGR2GRAY);
		face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(50,50 ) );
		Mat img_face;
		for (int i = 0; i < faces.size(); ++i) {
				Rect rect_face( faces[i]);
				rectangle(img, rect_face, Scalar (120, 5, 86), 2, 2, 0);

		}

		if (faces.size() > 0 && detected_faces_saved_no < 10) {
			img_face = img_gray(faces[0]);
			Mat img_normalized;
			cv::resize(img_face, img_normalized, Size(250,250), 1.0, 1.0, INTER_CUBIC);

			ostringstream oss;
			oss << detected_faces_saved_no;	const std::string user("user1");

			cv::imwrite("detected_face" + oss.str() + ".jpg", img_normalized);
			++detected_faces_saved_no;
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
		using namespace std;
		using namespace cv;


		CascadeClassifier face_cascade;

		if (!face_cascade.load(constant::face_cascade_name)) {
				return;
		};

	//	Mat img;
	//	img = imread( "capture.jpg");
		vector<Rect> faces;
		detect_face(original_matrix, face_cascade, faces);
//    waitKey(0);
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
	//if (!original_matrix.empty()) {
	cv::Mat gray_matrix;
	cvtColor(original_matrix, gray_matrix, CV_BGR2GRAY);
	cv::imwrite("capture3.jpg", gray_matrix);
//	}

}

void MainWindow::on_recognize_button_clicked()
{
	vector<Mat> learned_faces;
	int learned_face_no = 0;
	for (; learned_face_no < 10 ; ++learned_face_no) {
		ostringstream oss;
		oss << learned_face_no;
		learned_faces.push_back(imread("detected_face" + oss.str() + ".jpg"));
	}

	vector<Mat>::iterator it;
	for (it = learned_faces.begin(); it != learned_faces.end(); ++it) {
		cv::cvtColor(*it, *it, CV_BGR2GRAY);
	}


	vector<int> labels(10, 1);
	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
	model->train(learned_faces, labels);



	if (original_matrix.empty()) {
		cout <<  "camera read error ";
		return;
	}


	CascadeClassifier face_cascade;
	if (!face_cascade.load(constant::face_cascade_name)) {
		cout << "cannot load cascade file";
			return;
	};

	vector<Rect> faces;
	detect_face(original_matrix, face_cascade, faces);
	Mat normalized_face_to_authorise;
	cv::resize(original_matrix(faces[0]), normalized_face_to_authorise, Size(250, 250));

	cv::cvtColor(normalized_face_to_authorise, normalized_face_to_authorise, CV_BGR2GRAY);

	int label = 0;
	double confidence = 22.0;
	cv::imwrite("normalized.jpg", normalized_face_to_authorise);
	model->predict(normalized_face_to_authorise, label, confidence);
	cout << "plabel = " << label;
	cout << "\n conf" << confidence << endl;

}


