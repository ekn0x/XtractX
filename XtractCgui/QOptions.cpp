#include "XtractC.h"
#include "QOptions.h"
#include "QMultipleFile.h"
//#include "QDossier.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QMessageBox>

#include <sstream>

QOptions::QOptions(QWidget * parent)
	: qParent{parent}
{
	QVBoxLayout * layout = new QVBoxLayout;
	
	layout->addWidget(buildFolderBox(), 0, 0);
	layout->addWidget(buildFileBox(), 1, 0);
	layout->addWidget(buildExtBox(), 2, 0);
	layout->addLayout(buildOptFooter(), 3);
	layout->addStretch();
	
	setLayout(layout);
}

QGroupBox* QOptions::buildFolderBox()
{
	mFolderOpt = new QGroupBox;
	mFolderOpt->setTitle(QString("Options repertoire de sortie"));

	// source output folder
	QRadioButton * source = new QRadioButton; // utiliser le dossier de sortie des fichiers
	source->setChecked(true); // option par defaut
	QLabel * sourceFolder = new QLabel(QString("Utiliser le repertoire source"));
	sourceFolder->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(source);
	line1->addWidget(sourceFolder);
	line1->addStretch();

	// selected output folder
	QRadioButton * select = new QRadioButton; // choisir le dossier de sortie
	QLabel * selectedFolder = new QLabel(QString("Specifier un repertoire de sortie"));
	selectedFolder->setFixedWidth(200);
	mSelectFolder = new QPushButton(QString("Selectionner"));
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(select);
	line2->addWidget(selectedFolder);
	line2->addStretch();
	line2->addWidget(mSelectFolder);

	QLineEdit * path = new QLineEdit;
	path->setReadOnly(true);

	// constuire le layout
	QVBoxLayout * subLayout = new QVBoxLayout;
	subLayout->addLayout(line1, 0);
	subLayout->addLayout(line2, 1);
	subLayout->addWidget(path);
	subLayout->addStretch();

	mFolderOpt->setLayout(subLayout);

	// Connections
	// gray out button when repertoire is selected
	connect(select, &QRadioButton::clicked, this, &QOptions::enableCustomOutputFolder);


	return mFolderOpt;
}

QGroupBox* QOptions::buildFileBox()
{
	mFileOpt = new QGroupBox;
	mFileOpt->setTitle(QString("Options fichier de sortie"));

	// source output folder
	QRadioButton * fileName = new QRadioButton;
	fileName->setChecked(true); // option par defaut
	QLabel * srcFileName = new QLabel(QString("Utiliser le meme nom de fichier"));
	srcFileName->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(fileName);
	line1->addWidget(srcFileName);
	line1->addStretch();

	QRadioButton * select = new QRadioButton; // choisir le dossier de sortie
	QLabel * selectedFolder = new QLabel(QString("Utiliser un nom de fichier avec numerotation automatique"));
	selectedFolder->setFixedWidth(300);
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(select);
	line2->addWidget(selectedFolder);
	line2->addStretch();

	QLabel * labelPrefix = new QLabel(QString("Prefixe du nom de fichier"));
	labelPrefix->setFixedWidth(200);
	QLineEdit * prefix = new QLineEdit;
	prefix->setFixedWidth(200);
	QHBoxLayout * line3 = new QHBoxLayout;
	line3->addWidget(labelPrefix);
	line3->addStretch();
	line3->addWidget(prefix);

	QLabel * labelNumero = new QLabel(QString("Debuter la numerotation a"));
	labelNumero->setFixedWidth(200);
	QSpinBox * numero = new QSpinBox;
	numero->setFixedWidth(200);
	QHBoxLayout * line4 = new QHBoxLayout;
	line4->addWidget(labelNumero);
	line4->addStretch();
	line4->addWidget(numero);

	// constuire le layout
	QVBoxLayout * subLayout = new QVBoxLayout;
	subLayout->addLayout(line1, 0);
	subLayout->addLayout(line2, 1);
	subLayout->addLayout(line3, 2);
	subLayout->addLayout(line4, 3);
	subLayout->addStretch();

	mFileOpt->setLayout(subLayout);

	return mFileOpt;
}

QGroupBox* QOptions::buildExtBox()
{
	mExtOpt = new QGroupBox;
	mExtOpt->setTitle(QString("Options extension des fichiers de sortie"));

	QRadioButton * extXtractC = new QRadioButton;
	extXtractC->setChecked(true);
	QLabel * labelExtXtractC = new QLabel("Utiliser l'extension XtractC");
	labelExtXtractC->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(extXtractC);
	line1->addWidget(labelExtXtractC);
	line1->addStretch();

	QRadioButton * extCustom = new QRadioButton;
	QLabel * labelExtCustom = new QLabel("Specifier l'extension");
	labelExtCustom->setFixedWidth(200);
	QLineEdit * extension = new QLineEdit;
	extension->setFixedWidth(200);
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(extCustom);
	line2->addWidget(labelExtCustom);
	line2->addStretch();
	line2->addWidget(extension);

	// constuire le layout
	QVBoxLayout * subLayout = new QVBoxLayout;
	subLayout->addLayout(line1, 0);
	subLayout->addLayout(line2, 1);
	subLayout->addStretch();

	mExtOpt->setLayout(subLayout);

	return mExtOpt;
}

QHBoxLayout * QOptions::buildOptFooter()
{
	QCheckBox * statistique = new QCheckBox;
	QLabel * labelStatistique = new QLabel("Inclure les statistiques");
	QPushButton * generer = new QPushButton(QString("Generer"));

	QHBoxLayout * subLayout = new QHBoxLayout;
	subLayout->addStretch();
	subLayout->addWidget(statistique);
	subLayout->addWidget(labelStatistique);
	subLayout->addWidget(generer);
	
	connect(generer, &QPushButton::released, this, &QOptions::PB_Generer);

	return subLayout;
}

// Functions
void QOptions::genererOutputFiles()
{
	QMultipleFile* owner = dynamic_cast<QMultipleFile*>(qParent);
	int fileCount = owner->selectedFilesCount();
	if (fileCount > 0)
	{
		// 1) Obtenir la liste des fichiers
		QStringList fileList = static_cast<QMultipleFile*>(qParent)->getFileList();

		// 2) Obtenir la liste des options de sortie
		
		// 3) 
		for (auto it = fileList.begin(); it != fileList.end(); ++it)
		{
			XtractC extracteur;

			QMessageBox::information(this, QString("Active File"), *it);
			try 
			{
				std::stringstream strStreamIn((*it).toStdString());
				std::stringstream strStreamOut("G:/test.XtractC");
				extracteur.setup(strStreamIn, strStreamOut);
				if(!extracteur.process(true))
					QMessageBox::information(this, QString("Active File"), QString("L'operation n'a pas fonctionner"));

			}
			catch (XtractC::ParamException const & exception)
			{
				QMessageBox::information(this, QString("Active File"), QString("XtractC exception caught : ") + QString::fromStdString(exception.what()));
			}
			catch (XtractC::Exception const & exception) {
				QMessageBox::information(this, QString("Active File"), QString("XtractC exception caught : ") + QString::fromStdString(exception.what()));
			}
			catch (exception const & exception) {
				QMessageBox::information(this, QString("Active File"), QString("XtractC exception caught : ") + QString::fromStdString(exception.what()));
			}
		}
	}
	else
		QMessageBox::information(this, QString("Liste de fichier vide"), QString("Aucun fichier dans la liste"));
}

// slots

void QOptions::enableCustomOutputFolder()
{
	mSelectFolder->setFlat(!mSelectFolder->isFlat());
}

void QOptions::PB_Generer()
{
	genererOutputFiles();
}

