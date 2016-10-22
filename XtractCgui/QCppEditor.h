#ifndef Q_CPP_EDITOR_H
#define Q_CPP_EDITOR_H


// Cette classe est un QLineTextEdit avec rehausseur syntaxique pour le langage C++.
// 
// Le rehausseur syntaxique est incomplet et fonctionne partiellement. Cet outil n’utilise 
// pas d’interpréteur de code mais plutôt tente de faire correspondre des parties du document 
// à des expressions régulières. Il est donc impossible de produire un rehausseur syntaxique 
// sans erreur. Toutefois, le résultat obtenu est satisfaisant pour ce laboratoire.
//
// Inspiré de l'exemple "Code Editor Example" de Qt
// Voir : http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
//

#include "QLineTextEdit.h"

class QCppSyntaxHighlighter;


class QCppEditor : public QLineTextEdit
{
	Q_OBJECT

	friend QLineNumberArea;

public:
	QCppEditor(QWidget * parent = nullptr);
	~QCppEditor() = default;

private:
	QCppSyntaxHighlighter * mSyntaxHighlighter;
};

#endif // Q_CPP_EDITOR_H


