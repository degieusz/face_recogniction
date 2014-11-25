#ifndef AUTHORIZED_H
#define AUTHORIZED_H

#include <QDialog>

namespace Ui {
class authorized;
}

class authorized : public QDialog
{
	Q_OBJECT

public:
	explicit authorized(QWidget *parent = 0);
	~authorized();

private:
	Ui::authorized *ui;
};

#endif // AUTHORIZED_H
