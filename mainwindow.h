#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <login_manager.h>
#include <recognizer.h>
#include <trainer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void process();

private:
	Ui::MainWindow *ui;
	QTimer *dispatcher;


	login_manager log_in_manager;
	face::recognizer recognizer;
	cv::VideoCapture webcam;
	cv::Mat capture;
	std::vector<cv::Mat> detected_faces;


	bool other_window_working;
private slots:
	void on_actionAdd_user_triggered();
	void on_actionDelete_user_triggered();
	void on_login_button_clicked();
};

#endif // MAINWINDOW_H
