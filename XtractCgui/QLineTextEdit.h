#ifndef QLINETEXTEDIT_H
#define QLINETEXTEDIT_H

// Cette classe est un QPlainTextEdit avec un widget supplémentaire présentant les numéros de lignes.
//
// Inspiré de l'exemple "Code Editor Example" de Qt
// Voir : http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
//

#include <QPlainTextEdit>

class QLineNumberArea;

class QLineTextEdit : public QPlainTextEdit
{
	Q_OBJECT

	friend QLineNumberArea;

public:
	QLineTextEdit(QWidget * parent = nullptr);
	~QLineTextEdit() = default;

	// Vide le contenu de la zone de texte.
	void reset() { setPlainText(""); }

protected:
	virtual void resizeEvent(QResizeEvent * event) override;
	virtual void paintEvent(QPaintEvent * event) override;

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);

private:
	QLineNumberArea *mLineNumberArea;
};



class QLineNumberArea : public QWidget
{
	Q_OBJECT

public:
	QLineNumberArea() = delete;
	QLineNumberArea(QLineTextEdit * textEdit);
	~QLineNumberArea() = default;

	virtual QSize sizeHint() const override;
	int lineNumberAreaWidth() const;

public slots:
	void updateArea(QRect const & rect, int dy);

protected:
	virtual void paintEvent(QPaintEvent *event) override;

private:
	QLineTextEdit *mTextEdit;
	int mOffset{ 8 };
};




#endif // QLINETEXTEDIT_H
