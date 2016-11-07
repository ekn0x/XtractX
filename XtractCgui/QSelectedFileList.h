#ifndef Q_SELECTED_FILE_LIST_H
#define Q_SELECTED_FILE_LIST_H


// Widget permettant de gérer une liste de nom de fichier à traiter.
// Ce widget doit être connecté à un objet de la classe QDirectorySelector via son constructeur.
// Il est possible :
//   - d'ajouter la sélection courante du directorySelector
//   - de supprimer un, plusieurs ou tout les fichiers de la liste.

#include <QWidget>

class QPushButton;
class QStringListModel;
class QListView;
class QLabel;
class QEStringListModel;
class QDirectorySelector;

class QSelectedFileList : public QWidget 
{
	Q_OBJECT

public:
	QSelectedFileList(QDirectorySelector * const & directorySelector, QWidget * parent = nullptr);
	~QSelectedFileList() = default;

	// Détermine le filtre à appliquer.
	void setFileSuffixFilter(QStringList const & filter) { mFileSuffixFilter = filter; }
	// Retourne le filtre à appliquer.
	QStringList fileSuffixFilter() const { return mFileSuffixFilter; }

	// Retourne la liste de fichiers inclue dans la liste.
	QStringList selectedFiles() const;
	// Retourne le nombre de fichier(s) inclue dans la liste.
	int selectedFilesCount() const;

signals:
	// Informe que la liste a changée.
	void listChanged();

private slots:
	void addSelectedFile();
	void removeSelectedFile();
	void removeAllFile();

private:
	QStringList mFileSuffixFilter;
	QDirectorySelector * const & mDirectorySelector;
	QEStringListModel * mSelectedFileModel;
	QListView * mSelectedFileView;
	QLabel * mSelectedFileCounter;
	QPushButton * mAddSelectedFile;
	QPushButton * mRemoveSelectedFile;
	QPushButton * mRemoveAllFile;


	void updateSelectedFileCounter();
	void updateGui();
	//void addFile(QString const & fileName);
};

#include <QStringListModel>
class QEStringListModel : public QStringListModel
{
	Q_OBJECT

public:
	QEStringListModel(QObject * parent = nullptr) : QStringListModel(parent), mDuplicateAllowed{ true } {}
	~QEStringListModel() = default;

	void setDuplicateAllowed(bool allowed) { mDuplicateAllowed = allowed; }
	bool duplicateAllowed() const { return mDuplicateAllowed; }

	void append(QString const & string) {
		QString a = data(index(0), Qt::DisplayRole).toString();
		if (mDuplicateAllowed || (match(index(0), Qt::DisplayRole, string).size() == 0)) {
			insertRows(rowCount(), 1);
			setData(index(rowCount() - 1), string);
		}
	}

	void append(QStringList const & strings) {
		for (auto string : strings) {
			append(string);
		}
	}

	QEStringListModel & operator<<(QString const & string) {
		append(string);
		return *this;
	}

	QEStringListModel & operator<<(QStringList const & strings) {
		append(strings);
		return *this;
	}

private:
	bool mDuplicateAllowed;
};


#endif // Q_SELECTED_FILE_LIST_H