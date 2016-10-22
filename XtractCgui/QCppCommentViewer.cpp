#include "QCppCommentViewer.h"


#include "QCppEditor.h"
#include "QLineTextEdit.h"
#include <QSplitter>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>

#include <sstream>

QCppCommentViewer::QCppCommentViewer(QWidget * parent)
	: QWidget(parent)
{
	mCppSourceViewer = new QCppEditor;
	mCppCommentViewer = new QLineTextEdit;

	mCppSourceViewer->setPlaceholderText(tr("aucun fichier sélectionné"));
	mCppCommentViewer->setPlaceholderText(tr("aucun commentaire"));

	QSplitter * splitter = new QSplitter;
	splitter->addWidget(mCppSourceViewer);
	splitter->addWidget(mCppCommentViewer);

	mDisplayStatistics = new QCheckBox(tr("Afficher les statistiques"));
	mDisplayStatistics->setChecked(true);

	QHBoxLayout * optionsLayout = new QHBoxLayout;
	optionsLayout->addStretch();
	optionsLayout->addWidget(mDisplayStatistics);

	QVBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(splitter);
	layout->addLayout(optionsLayout);
	setLayout(layout);

	connect(mDisplayStatistics, &QCheckBox::stateChanged, this, &QCppCommentViewer::processComments);
}

void QCppCommentViewer::reset()
{
	mCppSourceViewer->reset();
	mCppCommentViewer->reset();
}

void QCppCommentViewer::setFile(QString const & fileName)
{
	//static int timeOutDelay{ 5000 };

	QFileInfo fileInfo(fileName);

	if (!fileInfo.exists()) {
		reset();
		emit eventSignaled("Ce fichier n'existe pas : " + fileName);
		return;
	}
	if (!fileInfo.isReadable()) {
		reset();
		emit eventSignaled("Ce fichier n'est pas accessible en écriture : " + fileName);
		return;
	}
	if (!mFileSuffixFilter.contains(fileInfo.suffix(), Qt::CaseInsensitive)) {
		reset();
		emit eventSignaled("Le fichier n'est pas valide. L'extension " + fileInfo.suffix().toUpper() + " n'est pas supportée : " + fileName);
		return;
	}

	QFile file(fileName);
	if (file.open(QFile::ReadOnly | QFile::Text)) {
		mSource = file.readAll();
		mCppSourceViewer->setPlainText(mSource);
		processComments();
	} else {
		reset();
		emit eventSignaled("Incapable d'ouvrir le fichier : " + fileName);
		return;
	}
}

void QCppCommentViewer::processComments()
{
	if (mSource.isEmpty()) {
		mCppCommentViewer->reset();
	} else {
		try {
			std::stringstream strStreamIn(mSource.toStdString());
			std::stringstream strStreamOut;
			mXtractC.setup(strStreamIn, strStreamOut);
			mXtractC.process(mDisplayStatistics->isChecked());
			mCppCommentViewer->setPlainText(QString::fromStdString(strStreamOut.str()));
		}
		catch (XtractC::ParamException const & exception)
		{
			emit eventSignaled("XtractC exception caught : " + QString::fromStdString(exception.what()));
		}
		catch (XtractC::Exception const & exception) {
			emit eventSignaled("XtractC exception caught : " + QString::fromStdString(exception.what()));
		}
		catch (exception const & exception) {
			emit eventSignaled("XtractC exception caught : " + QString::fromStdString(exception.what()));
		}
	}
}

