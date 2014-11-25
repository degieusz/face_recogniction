#ifndef DEL_USER_H
#define DEL_USER_H

#include <QDialog>

namespace Ui {
class del_user;
}

class del_user : public QDialog
{
	Q_OBJECT

public:
	explicit del_user(QWidget *parent = 0);
	~del_user();

private:
	Ui::del_user *ui;
};

#endif // DEL_USER_H
