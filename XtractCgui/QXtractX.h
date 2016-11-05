#ifndef QXTRACTX_H
#define QXTRACTX_H

#include <QWidget>

class QSplitter;
class QDirectorySelector;
class QTabWidget;
class QCppCommentViewer;

class QXtractX : public QWidget
{
	Q_OBJECT

public:
	QXtractX(QWidget * parent = nullptr);
	~QXtractX();

private:
	QSplitter * mSplitter;
	QDirectorySelector * mDirSelect;
	QTabWidget * mXtractViews;

	QCppCommentViewer * mCommentViewer;
};

#endif // QXTRACTX_H