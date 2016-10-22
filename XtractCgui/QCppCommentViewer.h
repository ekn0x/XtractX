#ifndef Q_CPP_COMMENT_VIEWER_H
#define Q_CPP_COMMENT_VIEWER_H


//
// Ce widget fait la gestion d'affichage d'un fichier du langage C++ et de ses commentaires.
//
// 
// 


#include <QWidget>

class QCppEditor;
class QLineTextEdit;
class QCheckBox;

#include "XtractC.h"


class QCppCommentViewer : public QWidget
{
	Q_OBJECT

public:
	QCppCommentViewer(QWidget * parent = nullptr);
	~QCppCommentViewer() = default;
	
	// Vide le contenu des éditeurs.
	void reset();

	// Détermine le filtre à appliquer.
	void setFileSuffixFilter(QStringList const & filter) { mFileSuffixFilter = filter; }
	// Retourne le filtre appliqué
	QStringList fileSuffixFilter() const { return mFileSuffixFilter; }

public slots:
	// Assigne le fichier à afficher
	void setFile(QString const & fileName);

signals:
	// Signal émis lorsque d'un évènement pouvant être signalé à l'usager sur la barre de status.
	void eventSignaled(QString const & message, int timeOut = 3500);

private:
	QString mSource;
	QCppEditor * mCppSourceViewer;
	QLineTextEdit * mCppCommentViewer;
	QCheckBox * mDisplayStatistics;
	XtractC mXtractC;
	QStringList mFileSuffixFilter;

private slots:
	void processComments();
};


#endif // Q_CPP_COMMENT_VIEWER_H
