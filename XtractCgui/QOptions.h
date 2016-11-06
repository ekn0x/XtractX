#ifndef QOPTIONS_H
#define QOPTIONS_H

#include <QWidget>

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
	QGroupBox * mFolderOpt;
	QGroupBox * mFileOpt;
	QGroupBox * mExtOpt;

	QGroupBox * buildFolderBox();
	QGroupBox * buildFileBox();
	QGroupBox * buildExtBox();
	QHBoxLayout * buildOptFooter();

	// layout elements
	QPushButton * mSelectFolder;

public slots:
	void grayOut();

};


#endif // QOPTIONS_H
