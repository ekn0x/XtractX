#ifndef QDOSSIER_H
#define QDOSSIER_H

#include <QWidget>

#include "QOptions.h"

class QGroupBox;


class QOptions::QDossier : public QWidget
{
	Q_OBJECT;

public:
	QOptions::QDossier(QWidget *parent = 0);
	~QDossier() = default;

	QGroupBox* getGroupBox() { return boxDossier; };

private:
	QGroupBox * boxDossier;
};

#endif // QDOSSIER_H
