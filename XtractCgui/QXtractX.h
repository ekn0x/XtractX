#ifndef QXTRACTX_H
#define QXTRACTX_H

#include <QWidget>

class QSplitter;
class QDirectorySelector;
class QTabWidget;

class QXtractX : public QWidget
{
	Q_OBJECT

public:
	QXtractX(QWidget * parent = nullptr);
	~QXtractX();

private:
	QSplitter * splitter;
	QDirectorySelector * dirSelect;
	QTabWidget * xtractViews;
};

#endif // QXTRACTX_H