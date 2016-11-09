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
#include <QFileDialog>
#include "qdir.h"

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
	source->setText("Utiliser le repertoire source");
	source->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(source);
	line1->addStretch();

	// selected output folder
	QRadioButton * select = new QRadioButton; // choisir le dossier de sortie
	select->setText("Specifier un repertoire de sortie");
	select->setFixedWidth(200);
	mSelectFolder = new QPushButton(QString("Selectionner"));
	mSelectFolder->setEnabled(false);
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(select);
	line2->addStretch();
	line2->addWidget(mSelectFolder);

	mPath = new QLabel;

	// constuire le layout
	QVBoxLayout * subLayout = new QVBoxLayout;
	subLayout->addLayout(line1, 0);
	subLayout->addLayout(line2, 1);
	subLayout->addWidget(mPath);
	subLayout->addStretch();

	mFolderOpt->setLayout(subLayout);

	// Connections
	// gray out button when repertoire is selected
	connect(select, &QRadioButton::clicked, this, &QOptions::enableCustomOutputFolder);
	connect(source, &QRadioButton::clicked, this, &QOptions::disableCustomOutputFolder);
	connect(mSelectFolder, &QPushButton::clicked, this, &QOptions::setOptCustom);


	return mFolderOpt;
}

QGroupBox* QOptions::buildFileBox()
{
	mFileOpt = new QGroupBox;
	mFileOpt->setTitle(QString("Options fichier de sortie"));

	// source output folder
	QRadioButton * origFileName = new QRadioButton;
	origFileName->setChecked(true); // option par defaut
	origFileName->setText("Utiliser le meme nom de fichier");
	origFileName->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(origFileName);
	line1->addStretch();

	QRadioButton * select = new QRadioButton; // choisir le nom de sortie
	select->setText("Utiliser un nom de fichier avec numerotation automatique");
	select->setFixedWidth(300);
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(select);
	line2->addStretch();

	QLabel * labelPrefix = new QLabel(QString("Prefixe du nom de fichier"));
	labelPrefix->setFixedWidth(200);
	mPrefix = new QLineEdit;
	mPrefix->setEnabled(false);
	mPrefix->setFixedWidth(200);
	QHBoxLayout * line3 = new QHBoxLayout;
	line3->addWidget(labelPrefix);
	line3->addStretch();
	line3->addWidget(mPrefix);

	QLabel * labelNumero = new QLabel(QString("Debuter la numerotation a"));
	labelNumero->setFixedWidth(200);
	mNumero = new QSpinBox;
	mNumero->setEnabled(false);
	mNumero->setFixedWidth(200);
	QHBoxLayout * line4 = new QHBoxLayout;
	line4->addWidget(labelNumero);
	line4->addStretch();
	line4->addWidget(mNumero);

	// constuire le layout
	QVBoxLayout * subLayout = new QVBoxLayout;
	subLayout->addLayout(line1, 0);
	subLayout->addLayout(line2, 1);
	subLayout->addLayout(line3, 2);
	subLayout->addLayout(line4, 3);
	subLayout->addStretch();

	mFileOpt->setLayout(subLayout);

	connect(select, &QRadioButton::clicked, this, &QOptions::enableCustomOptName);
	connect(origFileName, &QRadioButton::clicked, this, &QOptions::disableCustomOptName);

	return mFileOpt;
}

QGroupBox* QOptions::buildExtBox()
{
	mExtOpt = new QGroupBox;
	mExtOpt->setTitle(QString("Options extension des fichiers de sortie"));

	QRadioButton * extXtractC = new QRadioButton;
	extXtractC->setChecked(true);
	extXtractC->setText("Utiliser l'extension XtractC");
	extXtractC->setFixedWidth(200);
	QHBoxLayout * line1 = new QHBoxLayout;
	line1->addWidget(extXtractC);
	line1->addStretch();

	QRadioButton * extCustom = new QRadioButton;
	extCustom->setText("Specifier l'extension");
	extCustom->setFixedWidth(200);
	QLineEdit * extension = new QLineEdit;
	extension->setFixedWidth(200);
	QHBoxLayout * line2 = new QHBoxLayout;
	line2->addWidget(extCustom);
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
	statistique->setText("Inclure les statistiques");
	QPushButton * generer = new QPushButton(QString("Generer"));

	QHBoxLayout * subLayout = new QHBoxLayout;
	subLayout->addStretch();
	subLayout->addWidget(statistique);
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
		XtractC extracteur;
		// 1) Obtenir la liste des fichiers
		QStringList fileList = static_cast<QMultipleFile*>(qParent)->getFileList();


		for (auto it = fileList.begin(); it != fileList.end(); ++it)
		{
			// 2) Obtenir la liste des options de sortie

			// 3)  Lancer la machine
			QMessageBox::information(this, QString("Active File"), *it);
			try
			{
				std::string strFileIn((*it).toStdString());
				std::string strFileOut("G:/test.XtractC");
				extracteur.setup(strFileIn, strFileOut);
				if (!extracteur.process(true))
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

void QOptions::disableCustomOutputFolder()
{
	sourceFolder = true; 
	
	mOptPath = "";
	mPath->setText(mOptPath);
	mPath->setEnabled(false);

	mSelectFolder->setEnabled(false);


}

void QOptions::setOptCustom()
{
	QFileDialog dirSelect;
	int result;
	
	dirSelect.setFileMode(QFileDialog::Directory);
	dirSelect.setOption(QFileDialog::ShowDirsOnly);

	result = dirSelect.exec();

	if (result)
	{
		mOptPath = dirSelect.selectedFiles()[0];
		mPath->setText(mOptPath);
		mPath->setEnabled(true);
	}
}


void QOptions::enableCustomOutputFolder()
{
	sourceFolder = false;
	mSelectFolder->setEnabled(true);
}

void QOptions::PB_Generer()
{
	genererOutputFiles();
}

void QOptions::enableCustomOptName()
{
	mOriginalName = false;
	mPrefix->setEnabled(true);
	mNumero->setEnabled(true);
}

void QOptions::disableCustomOptName()
{
	mOriginalName = true;
	mPrefix->setEnabled(false);
	mNumero->setEnabled(false);
}



