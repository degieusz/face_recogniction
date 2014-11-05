#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pause_resume_clicked();

	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;

	cv::VideoCapture webcam;

	cv::Mat original_matrix;
	cv::Mat processed_matrix;

	QImage original_image;
	QImage processed_image;

	std::vector<cv::Vec3f> circles;
	std::vector<cv::Vec3f>::iterator cit;

	QTimer *process_frame_timer;

public slots:
	void process_frame_and_update_gui();

};

#endif // MAINWINDOW_H
