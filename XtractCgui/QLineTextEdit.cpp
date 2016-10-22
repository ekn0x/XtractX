#include "QLineTextEdit.h"



#include <QPainter>


QLineTextEdit::QLineTextEdit(QWidget *parent)
	:	QPlainTextEdit(parent)
{
	QFont font;
	font.setFamily("Courier new");
	font.setFixedPitch(true);
	font.setPointSize(9);
	font.setWeight(QFont::DemiBold);
	setFont(font);

	setReadOnly(true);
	setLineWrapMode(QPlainTextEdit::NoWrap);
	setTabStopWidth(QFontMetrics(font).width("    ")); // 4 spaces!

	mLineNumberArea = new QLineNumberArea(this);

	connect(this, &QPlainTextEdit::blockCountChanged, this, &QLineTextEdit::updateLineNumberAreaWidth);
	connect(this, &QPlainTextEdit::updateRequest, mLineNumberArea, &QLineNumberArea::updateArea);

	updateLineNumberAreaWidth(0);
}



void QLineTextEdit::resizeEvent(QResizeEvent * event)
{
	QPlainTextEdit::resizeEvent(event);

	QRect lineNumberAreaRect = contentsRect();
	lineNumberAreaRect.setWidth(mLineNumberArea->lineNumberAreaWidth());
	mLineNumberArea->setGeometry(lineNumberAreaRect);
}

void QLineTextEdit::paintEvent(QPaintEvent * event)
{
	if (toPlainText().isEmpty()) {
		QPainter painter(viewport());
		painter.setPen(Qt::black);
		painter.drawText(rect(), Qt::AlignCenter, placeholderText());
	} else {
		QPlainTextEdit::paintEvent(event);
	}
}

void QLineTextEdit::updateLineNumberAreaWidth(int newBlockCount)
{
	setViewportMargins(mLineNumberArea->lineNumberAreaWidth(), 0, 0, 0);
}










#include <QPainter>
#include <QTextBlock>
#include <QtCore/qmath.h>

QLineNumberArea::QLineNumberArea(QLineTextEdit * textEdit)
	:	QWidget(textEdit),
		mTextEdit{ textEdit }
{
}

QSize QLineNumberArea::sizeHint() const
{
	return QSize(lineNumberAreaWidth(), 0);
}

void QLineNumberArea::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), QColor(252, 252, 252));

	QTextBlock block = mTextEdit->firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = static_cast<int>(mTextEdit->blockBoundingGeometry(block).translated(mTextEdit->contentOffset()).top());
	int bottom = top + static_cast<int>(mTextEdit->blockBoundingRect(block).height());

	painter.setPen(QColor(128, 128, 128));
	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			//painter.setPen(QColor(128, 128, 128));
			painter.drawText(mOffset,
				top,
				width() - 2 * mOffset,
				fontMetrics().height(),
				Qt::AlignRight,
				number);
		}

		block = block.next();
		top = bottom;
		bottom = top + static_cast<int>(mTextEdit->blockBoundingRect(block).height());
		++blockNumber;
	}
}

void QLineNumberArea::updateArea(QRect const & rect, int dy)
{
	if (dy) {
		scroll(0, dy);
	}
	else {
		update(0, rect.y(), width(), rect.height());
	}

	if (rect.contains(mTextEdit->viewport()->rect())) {
		mTextEdit->updateLineNumberAreaWidth(0);
	}
}

int QLineNumberArea::lineNumberAreaWidth() const
{
	qreal max = qMax(1, mTextEdit->blockCount());
	int digits = static_cast<int>(qCeil(qLn(max) / qLn(10.0)));

	return 2 * mOffset + fontMetrics().width(QLatin1Char('8')) * digits;
}
