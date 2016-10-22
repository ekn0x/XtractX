#ifndef QDIRECTORYSELECTOR_H
#define QDIRECTORYSELECTOR_H



// Widget permettant la gestion d'un explorateur de fichiers avec quelques fonctionnalités de base.


#include <QWidget>

class QCustomHeaderFileSystemModel;
class QLabel;
class QTreeView;
class QLineEdit;
class QCheckBox;
class QMenu;

class QDirectorySelector : public QWidget
{
	Q_OBJECT

public:
	QDirectorySelector(QString const & title = tr("Explorateur de fichiers"), QWidget *parent = nullptr);
	~QDirectorySelector() = default;

	// Retourne la liste de fichier(s) actuellement sélectionnée(s)
	QStringList selectedFiles() const;

protected:
	QCustomHeaderFileSystemModel * mDirectoryModel;
	QLabel * mDirectoryTitle;
	QTreeView * mDirectoryView;
	QLineEdit * mDirectoryEdit;
	QCheckBox * mShowDetails;
	
	QMenu * mDirViewContextMenu;
	QAction * mDirViewContextMenuAction;

	virtual void buildContextMenu();
	
protected slots:
	virtual void openItem();

private slots:
	void synchronizeEditFromTree(QModelIndex const & index);
	void synchronizeTreeFromEdit();
	void reexpand();
	void reactToExpansion(QModelIndex const & index);
	void showDetails();
	void contextMenuOpenFileExplorer(const QPoint &pos);

signals:
	void treeSynchronized(QModelIndex const & index);
	void fileSelected(QString const & fileName);
};


#endif // QDIRECTORYSELECTOR_H
