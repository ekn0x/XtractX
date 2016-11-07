#ifndef QOPTIONS_H
#define QOPTIONS_H

#include <QWidget>
#include "qlabel.h"
#include "qspinbox.h"

class QGroupBox;
class QPushButton;
class QHBoxLayout;

class QOptions : public QWidget
{
	Q_OBJECT;

	class QDossier;
	//class QFile;
	//class QExtension;

public:
	QOptions(QWidget *parent = 0);
	~QOptions() = default;

private:
	QWidget * qParent;

	QGroupBox * mFolderOpt;
	QGroupBox * mFileOpt;
	QGroupBox * mExtOpt;

	QGroupBox * buildFolderBox();
	QGroupBox * buildFileBox();
	QGroupBox * buildExtBox();
	QHBoxLayout * buildOptFooter();

	// layout elements
	//mFolderOpt
	bool sourceFolder = true;
	QPushButton * mSelectFolder;
	QString mOptPath;
	QLabel * mPath;

	//FileOutput
	bool mOriginalName = true;
	QLineEdit * mPrefix;
	QSpinBox * mNumero;

	// generer function
	void genererOutputFiles();

public slots:
	void enableCustomOutputFolder();
	void disableCustomOutputFolder();
	void enableCustomOptName();
	void disableCustomOptName();
	void setOptCustom();
	void PB_Generer();

};


#endif // QOPTIONS_H
