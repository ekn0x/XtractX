#ifndef XTRACTCGUI_H
#define XTRACTCGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_XtractCgui.h"

class XtractCgui : public QMainWindow
{
	Q_OBJECT

public:
	XtractCgui(QWidget *parent = 0);
	~XtractCgui() = default;

private:
	Ui::XtractCguiClass ui;
};

#endif // XTRACTCGUI_H

