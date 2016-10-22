#ifndef Q_CPP_SYNTAX_HIGHLIGHTER_H
#define Q_CPP_SYNTAX_HIGHLIGHTER_H

//
// Inspiré de l'exemple "Syntax Highlighter Example" de Qt 
// Voir : http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
//

#include <QSyntaxHighlighter>

#include <QString>
#include <QStringList>
#include <QVector>
#include <QMap>
#include <QRegularExpression>
#include <QTextCharFormat>

class QTextEdit;


class QCppSyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	QCppSyntaxHighlighter(QTextDocument * document);
	~QCppSyntaxHighlighter() = default;

protected:
	virtual void highlightBlock(QString const & text) override;

protected:
	struct HighlightingRule
	{
		HighlightingRule() = default;
		HighlightingRule(QRegularExpression const & p, QTextCharFormat const & f) : pattern{p}, format{ f } {}
		QRegularExpression pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> mHighlightingRules;

	void buildAllRules();
	virtual void buildKeyRules(QStringList const & keyWords, QTextCharFormat const & format, bool applyBoundaries);
	void appendRule(QRegularExpression const & regEx, QTextCharFormat const & format);

private:
	static const QStringList CppKeywords;
	static const QStringList CppPreprocesssor;
	static const QStringList CppOperators;
	static const QRegularExpression mCommentStartExpression;
	static const QRegularExpression mCommentEndExpression;
};

#endif // Q_CPP_SYNTAX_HIGHLIGHTER_H
