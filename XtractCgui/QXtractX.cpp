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

	splitter = new QSplitter;
	dirSelect = new QDirectorySelector;
	xtractViews = new QTabWidget;
	
	xtractViews->addTab(new QCppCommentViewer, "View comments");
	//xtractViews->addTab();
	xtractViews->addTab(new QSupplement, "Suppléments");

	splitter->addWidget(dirSelect);
	splitter->addWidget(xtractViews);

	QGridLayout * layout = new QGridLayout;
	layout->addWidget(splitter);

	setLayout(layout);
}

QXtractX::~QXtractX()
{

}	