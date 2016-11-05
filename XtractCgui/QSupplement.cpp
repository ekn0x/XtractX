#include "QSupplement.h"

#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

QSupplement::QSupplement(QWidget * parent)
{
	QPushButton * button = new QPushButton(QString("About"));
	connect(button, &QPushButton::clicked, this, &QSupplement::aboutMSG);

	QHBoxLayout * HLayout = new QHBoxLayout;
	HLayout->addStretch();
	HLayout->addWidget(button);

	QVBoxLayout * VLayout = new QVBoxLayout;
	VLayout->addStretch();
	VLayout->addLayout(HLayout);

	setLayout(VLayout);
}

QSupplement::~QSupplement()
{

}

void QSupplement::aboutMSG()
{
	QMessageBox::about(this, QString("About"), QString("XtractC est un logiciel \n\n Ce programme a ete realise par : \n - Alex H.Lamarche\n - Guillaume Whittom\n\nDans le cadre du cours\n"));
}