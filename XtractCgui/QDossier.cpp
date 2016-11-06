#include "QOptions.h"
#include "QDossier.h"

#include <QVboxLayout>
#include <QHboxLayout>

#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

QOptions::QDossier::QDossier(QWidget * parent)
{
	boxDossier = new QGroupBox;
	boxDossier->setTitle(QString("Options de dossier"));
	
	// options
	// source output folder
	QRadioButton * source = new QRadioButton; // utiliser le dossier de sortie des fichiers
	source->setChecked(true); // option par defaut
	QLabel * sourceFolder = new QLabel;
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(source);
	line1->addWidget(sourceFolder);
	
	// selected output folder
	QRadioButton * select = new QRadioButton; // choisir le dossier de sortie
	QLabel * selectedFolder = new QLabel;
	QPushButton * selectFolder = new QPushButton;
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(select);
	line2->addWidget(selectedFolder);
	line2->addWidget(selectFolder);
	
	QLineEdit * path = new QLineEdit;

	// constuire le layout
	QVBoxLayout * layout = new QVBoxLayout;
	layout->addLayout(line1);
	layout->addLayout(line2);
	layout->addWidget(path);

	// 

	boxDossier->setLayout(layout);
} 