#include "QXtractX.h"

#include "QDirectorySelector.h"
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
	setWindowIcon(QIcon(":/XtractCgui/Icon"));

	mSplitter = new QSplitter;
	mDirSelect = new QDirectorySelector;
	mXtractViews = new QTabWidget;

	// set acceptable extension
	mCommentViewer = new QCppCommentViewer;
	mCommentViewer->setFileSuffixFilter({ "c", "h", "cpp", "hpp" });
	
	mXtractViews->addTab(mCommentViewer, "View comments");
	//xtractViews->addTab();
	mXtractViews->addTab(new QSupplement, "Suppléments");

	connect(mDirSelect, &QDirectorySelector::fileSelected, mCommentViewer, &QCppCommentViewer::setFile);

	mSplitter->addWidget(mDirSelect);
	mSplitter->addWidget(mXtractViews);

	QGridLayout * layout = new QGridLayout;
	layout->addWidget(mSplitter);

	setLayout(layout);
}

QXtractX::~QXtractX()
{

}	