#include "QXtractX.h"

#include "QDirectorySelector.h"
#include "QMultipleFile.h"
#include "QCppCommentViewer.h"
#include "QSupplement.h"

// Qt lib
#include <QWidget>
#include <QSplitter>
#include <QTabWidget>
#include <QGridLayout>
#include <QString>

QXtractX::QXtractX(QWidget * parent)
{
	mSplitter = new QSplitter;
	mDirSelect = new QDirectorySelector;
	mXtractViews = new QTabWidget;

	// set view and acceptable extensions for one file
	mCommentViewer = new QCppCommentViewer;
	mCommentViewer->setFileSuffixFilter({ "c", "h", "cpp", "hpp" });

	mMultipleFile = new QMultipleFile(mDirSelect);

	
	mXtractViews->addTab(mCommentViewer, "Consulter un fichier source et ses commentaires");
	mXtractViews->addTab(mMultipleFile, "Generer des fichiers de commentaires");
	mXtractViews->addTab(new QSupplement, "Supplements");

	connect(mDirSelect, &QDirectorySelector::fileSelected, mCommentViewer, &QCppCommentViewer::setFile);

	mSplitter->addWidget(mDirSelect);
	mSplitter->addWidget(mXtractViews);

	QGridLayout * layout = new QGridLayout;
	layout->addWidget(mSplitter);

	setLayout(layout);
}
