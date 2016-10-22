#include "QCppSyntaxHighlighter.h"




//#include <QTextEdit>
//
//#include <QDebug>
//


QCppSyntaxHighlighter::QCppSyntaxHighlighter(QTextDocument * document)
	: QSyntaxHighlighter(document)
{
	buildAllRules();
}

void QCppSyntaxHighlighter::buildAllRules()
{
	QTextCharFormat textFormat;
	QRegularExpression regEx;

	// Keywords
	textFormat.setForeground(QColor(0, 0, 255));
	textFormat.setFontWeight(QFont::Bold);
	buildKeyRules(CppKeywords, textFormat, true);

	// Preprocessor instructions
	textFormat.setForeground(QColor(111, 0, 138));
	textFormat.setFontWeight(QFont::Bold);
	buildKeyRules(CppPreprocesssor, textFormat, true);

	// Operators
	textFormat.setForeground(QColor(0, 0, 0));
	textFormat.setFontWeight(QFont::ExtraBold);
	buildKeyRules(CppOperators, textFormat, false);

	// Constants
	textFormat.setForeground(QColor(163, 21, 21));
	textFormat.setFontWeight(QFont::Bold);
	// Text
	appendRule(QRegularExpression("\"[^\"]*\""), textFormat); // defect : les guillemets \" ne fonctionnent pas.
	// Integer
	QString cannotStartWithLabelChar{ "([^a-zA-Z0-9_]|^)" };
	QString integerSuffix{ "(([uU][lL]{0,2})|([lL]{0,2}[uU]?))" };
	// Integer base 10
	appendRule(QRegularExpression(cannotStartWithLabelChar + "[1-9]([0-9]|[\'])*" + integerSuffix), textFormat);
	// Integer base 8
	appendRule(QRegularExpression(cannotStartWithLabelChar + "[0][0-7]*" + integerSuffix), textFormat);
	// Integer base 2
	appendRule(QRegularExpression(cannotStartWithLabelChar + "[0][bB][0-1]*" + integerSuffix), textFormat);
	// Integer base 16
	appendRule(QRegularExpression(cannotStartWithLabelChar + "[0][xX][0-9a-fA-F]*" + integerSuffix), textFormat);
	//// Floating-point number constant
	appendRule(QRegularExpression(cannotStartWithLabelChar + "(([0-9]+[\\.]?[0-9]*)|([0-9]*[\\.][0-9]*))([eEpP][\\-\\+]?[0-9]+)?[fFlL]?"), textFormat);

	// Functions
	textFormat.setForeground(QColor(43, 145, 175));
	textFormat.setFontWeight(QFont::Bold);
	//textFormat.setFontItalic(true);
	appendRule(QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()"), textFormat);

	// C++ single line comments
	textFormat.setForeground(QColor(0, 128, 0));
	textFormat.setFontWeight(QFont::Bold);
	appendRule(QRegularExpression("((?!.*\".*)|^|\\s*)//[^\n]*"), textFormat); // à valider davantage
}

void QCppSyntaxHighlighter::buildKeyRules(QStringList const & keyWords, QTextCharFormat const & format, bool applyBoundaries)
{
	for (auto keyWord : keyWords) {
		QString pattern = applyBoundaries ? "(^|\\s)" + keyWord + "($|\\s)" : keyWord;
		appendRule(QRegularExpression(pattern), format);
	}
}

void QCppSyntaxHighlighter::appendRule(QRegularExpression const & regEx, QTextCharFormat const & format)
{
	regEx.optimize();
	mHighlightingRules.append(HighlightingRule(regEx, format));
}


void QCppSyntaxHighlighter::highlightBlock(QString const & text)
{
	foreach(HighlightingRule const & rule, mHighlightingRules) {
		QRegularExpression expression(rule.pattern);
		QRegularExpressionMatchIterator i = expression.globalMatch(text);
		while (i.hasNext()) {
			QRegularExpressionMatch match = i.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.format);
		}
	}

	setCurrentBlockState(0);

	QTextCharFormat textFormat;
	textFormat.setForeground(QColor(43, 145, 175));
	textFormat.setFontWeight(QFont::Bold);
	int startIndex = 0;
	if (previousBlockState() != 1) {
		startIndex = mCommentStartExpression.match(text).capturedStart();
	}

    while (startIndex >= 0) {
		QRegularExpressionMatch match = mCommentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, textFormat);
        startIndex = mCommentStartExpression.match(text, startIndex + commentLength).capturedStart();
    }
}




const QRegularExpression QCppSyntaxHighlighter::mCommentStartExpression{ 
			[]()->QRegularExpression { 
					QRegularExpression regEx("/\\*"); 
					regEx.optimize(); 
					return regEx; }() 
			};

const QRegularExpression QCppSyntaxHighlighter::mCommentEndExpression{ 
			[]()->QRegularExpression { 
					QRegularExpression regEx("\\*/");
					regEx.optimize(); 
					return regEx; }() 
			};

const QStringList QCppSyntaxHighlighter::CppKeywords{
		QStringList()	<< "alignas"			// Since C++11
						<< "alignof"			// Since C++11
						<< "and"
						<< "and_eq"
						<< "asm"
						<< "atomic_cancel"
						<< "atomic_commit"
						<< "atomic_noexcept"
						<< "auto"
						<< "bitand"
						<< "bitor"
						<< "bool"
						<< "break"
						<< "case"
						<< "catch"
						<< "char"
						<< "char16_t"			// Since C++11
						<< "char32_t"			// Since C++11
						<< "class"
						<< "compl"
						<< "concept"
						<< "const"
						<< "constexpr"			// Since C++11
						<< "const_cast"
						<< "continue"
						<< "decltype"			// Since C++11
						<< "default"
						<< "delete"
						<< "do"
						<< "double"
						<< "dynamic_cast"
						<< "else"
						<< "enum"
						<< "explicit"
						<< "export"
						<< "extern"
						<< "false"
						<< "final"				// Since C++11
						<< "float"
						<< "for"
						<< "friend"
						<< "goto"
						<< "if"
						<< "inline"
						<< "int"
						<< "import"
						<< "long"
						<< "module"
						<< "mutable"
						<< "namespace"
						<< "new"
						<< "noexcept"			// Since C++11
						<< "not"
						<< "not_eq"
						<< "nullptr"			// Since C++11
						<< "operator"
						<< "or"
						<< "or_eq"
						<< "override"			// Since C++11
						<< "private"
						<< "protected"
						<< "public"
						<< "register"
						<< "reinterpret_cast"
						<< "requires"
						<< "return"
						<< "short"
						<< "signed"
						<< "sizeof"
						<< "static"
						<< "static_assert"		// Since C++11
						<< "static_cast"
						<< "struct"
						<< "switch"
						<< "synchronized"
						<< "template"
						<< "this"
						<< "thread_local"		// Since C++11
						<< "throw"
						<< "transaction_safe"
						<< "transaction_safe_dynamic"
						<< "true"
						<< "try"
						<< "typedef"
						<< "typeid"
						<< "typename"
						<< "union"
						<< "unsigned"
						<< "using"
						<< "virtual"
						<< "void"
						<< "volatile"
						<< "wchar_t"
						<< "while"
						<< "xor"
						<< "xor_eq"
						<< "\\.\\.\\."
	};

const QStringList QCppSyntaxHighlighter::CppPreprocesssor{
		QStringList()	<< "\\#if"
						<< "\\#elif"
						<< "\\#else"
						<< "\\#endif"
						<< "\\#defined"
						<< "\\#ifdef"
						<< "\\#ifndef"
						<< "\\#define"
						<< "\\#undef"
						<< "\\#include"
						<< "\\#line"
						<< "\\#error"
						<< "\\#pragma"
	};


const QStringList QCppSyntaxHighlighter::CppOperators{
		QStringList()	<< "\\="
						<< "\\+"
						<< "\\-"
						<< "\\*"
						<< "\\/"
						<< "\\%"
//						<< "\\+\\+"
//						<< "\\-\\-"
//						<< "\\=\\="
//						<< "\\!\\="
						<< "<"
						<< ">"
//						<< "<\\="
//						<< ">\\="
						<< "\\!"
						//<< "not"
//						<< "&&"
						//<< "and"
//						<< "\\|\\|"
						//<< "or"
						<< "~"
						//<< "compl"
						<< "&"
						//<< "bitand"
						<< "\\|"
						//<< "bitor"
						<< "\\^"
						//<< "xor"
//						<< "<<"
//						<< ">>"
//						<< "\\+\\="
//						<< "\\-\\="
//						<< "\\*\\="
//						<< "\\/\\="
//						<< "\\%\\="
//						<< "&\\="
						//<< "and_eq"
//						<< "\\|\\="
						//<< "or_eq"
//						<< "\\^\\="
						//<< "xor_eq"
//						<< "<<\\="
//						<< ">>\\="
						<< "\\["
						<< "\\]"
						<< "\\*"
						<< "\\&"
//						<< "\\->"
						<< "\\."
//						<< "\\->*"
//						<< "\\.\\*"
						<< "\\("
						<< "\\)"
						<< ","
						<< "::"
						<< "\\?"
						<< ":"
						//<< "sizeof"
						//<< "sizeof..."
						//<< "alignof"
						//<< "_Alignof"
						//<< "typeid"
						//<< "static_cast"
						//<< "dynamic_cast"
						//<< "const_cast"
						//<< "reinterpret_cast"
						//<< "new"
						//<< "delete"
						//<< "noexcept"
	};









