#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <login_manager.h>
#include <trainer.h>
#include <recognizer.h>

namespace Ui {
class add_user;
}

class add_user : public QDialog
{
	Q_OBJECT

public:
	explicit add_user(cv::Mat& capture_, login_manager& log_in_manager_, QWidget *parent = 0);
	~add_user();

public slots:
	void process();

private slots:
	void on_create_text_user_clicked();

	void on_capture_img_button_clicked();

private:
	Ui::add_user *ui;
	QTimer *dispatcher;
	cv::Mat& capture;


	login_manager& log_in_manager;
	face::trainer trainer;

	std::string login;
	std::vector<cv::Mat> saved_faces;

	face::recognizer recognizer;
};

#endif // ADD_USER_H
