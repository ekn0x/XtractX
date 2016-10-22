#include "QCppEditor.h"

#include "QCppSyntaxHighlighter.h"


QCppEditor::QCppEditor(QWidget *parent)
	: QLineTextEdit(parent)
{
	mSyntaxHighlighter = new QCppSyntaxHighlighter(document());
}

