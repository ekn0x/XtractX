#ifndef QMULTIPLEFILE_H
#define QMULTIPLEFILE_H

#include <QWidget>

class QSplitter;
class QSelectedFileList;
class QDirectorySelector;
class QOptions;

class QMultipleFile : public QWidget
{
	Q_OBJECT;

public:
	QMultipleFile(QDirectorySelector * const & dirSelector, QWidget *parent = 0);
	~QMultipleFile() = default;

private:
	QSplitter * mSplitter;
	
	QSelectedFileList * mFileList;
	QOptions * mOptions;
};


#endif // QMULTIPLEFILE_H