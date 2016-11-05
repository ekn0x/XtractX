#ifndef QSUPPLEMENT_H
#define QSUPPLEMENT_H

#include <QWidget>

class QSupplement : public QWidget
{
	Q_OBJECT

public:
	QSupplement(QWidget * parent = nullptr);
	~QSupplement();	

private slots:
	void aboutMSG();
};

#endif // QSUPPLEMENT_H