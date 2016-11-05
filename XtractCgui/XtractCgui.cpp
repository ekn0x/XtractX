#include "XtractCgui.h"

#include "QXtractX.h"

XtractCgui::XtractCgui(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowIcon(QIcon(":/XtractCgui/Icon"));
	ui.setupUi(this);

	setCentralWidget(new QXtractX());
}

XtractCgui::~XtractCgui()
{

}
