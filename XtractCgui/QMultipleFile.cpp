#include "QMultipleFile.h"
#include "Qoptions.h"
#include "QSelectedFileList.h"
#include "QDirectorySelector.h"

#include <QSplitter>
#include <QGridLayout>


QMultipleFile::QMultipleFile(QDirectorySelector * const & dirSelector, QWidget *parent)
{
	mSplitter = new QSplitter;

	mFileList = new QSelectedFileList(dirSelector);
	mFileList->setFileSuffixFilter({ "c", "h", "cpp", "hpp" });

	mOptions = new QOptions(this);

	mSplitter->addWidget(mFileList);
	mSplitter->addWidget(mOptions);

	QGridLayout * layout = new QGridLayout;
	layout->addWidget(mSplitter);

	setLayout(layout);
}

QStringList QMultipleFile::getFileList()
{
	return mFileList->selectedFiles();
}

int QMultipleFile::selectedFilesCount()
{
	return mFileList->selectedFilesCount();
}