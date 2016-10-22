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
	
	// Vide le contenu des �diteurs.
	void reset();

	// D�termine le filtre � appliquer.
	void setFileSuffixFilter(QStringList const & filter) { mFileSuffixFilter = filter; }
	// Retourne le filtre appliqu�
	QStringList fileSuffixFilter() const { return mFileSuffixFilter; }

public slots:
	// Assigne le fichier � afficher
	void setFile(QString const & fileName);

signals:
	// Signal �mis lorsque d'un �v�nement pouvant �tre signal� � l'usager sur la barre de status.
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
