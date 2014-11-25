#ifndef DEL_USER_H
#define DEL_USER_H

#include <QDialog>

#include <login_manager.h>

namespace Ui {
class del_user;
}

class del_user : public QDialog
{
	Q_OBJECT

public:
	explicit del_user(login_manager& log_in_manager_, QWidget *parent = 0);
	~del_user();

private slots:
	void on_delete_user_clicked();

private:
	Ui::del_user *ui;
	login_manager& log_in_manager;
};

#endif // DEL_USER_H
