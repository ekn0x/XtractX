#ifndef QXTRACTX_H
#define QXTRACTX_H

#include <QWidget>

class QSplitter;
class QTabWidget;

class QDirectorySelector;
class QCppCommentViewer;
class QMultipleFile;


class QXtractX : public QWidget
{
	Q_OBJECT

public:
	QXtractX(QWidget * parent = nullptr);
	~QXtractX() = default;

private:
	QSplitter * mSplitter;
	QTabWidget * mXtractViews;

	QDirectorySelector * mDirSelect;
	QCppCommentViewer * mCommentViewer;
	QMultipleFile * mMultipleFile;
};

#endif // QXTRACTX_H