#ifndef AUTHORIZED_H
#define AUTHORIZED_H

#include <QDialog>
#include <login_manager.h>

namespace Ui {
class authorized;
}

class authorized : public QDialog
{
	Q_OBJECT

public:
	explicit authorized(login_manager& log_in_manager_, QWidget *parent = 0);
	~authorized();

private slots:
	void on_change_password_clicked();

private:
	Ui::authorized *ui;
	login_manager& log_in_manager;
};

#endif // AUTHORIZED_H
