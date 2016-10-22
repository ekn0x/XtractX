#include "QSelectedFileList.h"


#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "QDirectorySelector.h"

#include <QFileInfo>


QSelectedFileList::QSelectedFileList(QDirectorySelector * const & directorySelector, QWidget * parent)
	:	QWidget(parent) ,
		mDirectorySelector{ directorySelector }
{
	Q_CHECK_PTR(directorySelector);

	mSelectedFileModel = new QEStringListModel;
	mSelectedFileModel->setDuplicateAllowed(false);
	mSelectedFileView = new QListView;
	mSelectedFileView->setModel(mSelectedFileModel);
	mSelectedFileView->setSelectionMode(QAbstractItemView::ExtendedSelection);

	mAddSelectedFile = new QPushButton(tr("Ajouter sélection"));
	mRemoveSelectedFile = new QPushButton(tr("Retirer"));
	mRemoveAllFile = new QPushButton(tr("Retirer tout"));

	QHBoxLayout * buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(mAddSelectedFile);
	buttonLayout->addStretch();
	buttonLayout->addWidget(mRemoveSelectedFile);
	buttonLayout->addWidget(mRemoveAllFile);

	mSelectedFileCounter = new QLabel;
	QFont font = mSelectedFileCounter->font();
	//font.setItalic(true);
	mSelectedFileCounter->setFont(font);

	QVBoxLayout * selectedFileLayout = new QVBoxLayout;
	selectedFileLayout->addLayout(buttonLayout);
	selectedFileLayout->addWidget(mSelectedFileView);
	selectedFileLayout->addWidget(mSelectedFileCounter);

	setLayout(selectedFileLayout);

	connect(mAddSelectedFile, &QPushButton::clicked, this, &QSelectedFileList::addSelectedFile);
	connect(mRemoveSelectedFile, &QPushButton::clicked, this, &QSelectedFileList::removeSelectedFile);
	connect(mRemoveAllFile, &QPushButton::clicked, this, &QSelectedFileList::removeAllFile);

	updateGui();
}

void QSelectedFileList::updateSelectedFileCounter()
{
	QString rowCountText;
	switch (mSelectedFileModel->rowCount()) {
	case 0: rowCountText = "Aucun fichier sélectionné";
		break;
	case 1: rowCountText = "1 fichier sélectionné";
		break;
	default:rowCountText = QString::number(mSelectedFileModel->rowCount()) + " fichiers sélectionnés";
		break;
	}
	mSelectedFileCounter->setText(rowCountText);
}

void QSelectedFileList::addSelectedFile()
{
	QStringList files = mDirectorySelector->selectedFiles();

	for (auto file : files) {
		QFileInfo fileInfo(file);
		if (fileInfo.isFile() && mFileSuffixFilter.contains(fileInfo.suffix())) {
			*mSelectedFileModel << file;
		}
	}

	updateGui();

	emit listChanged();
}

void QSelectedFileList::removeSelectedFile()
{
	QModelIndexList list = mSelectedFileView->selectionModel()->selectedIndexes();

	if (list.size() == 0) {
		return;
	}

	qSort(list.begin(), list.end(), [](QModelIndex const & index1, QModelIndex const & index2)->bool { return index1.row() > index2.row(); });

	foreach(auto index, list) {
		if (!index.isValid()) return;
		mSelectedFileModel->removeRow(index.row());
	}

	updateGui();

	emit listChanged();
}

void QSelectedFileList::removeAllFile()
{
	mSelectedFileModel->removeRows(0, mSelectedFileModel->rowCount());

	updateGui();

	emit listChanged();
}

void QSelectedFileList::updateGui()
{
	mAddSelectedFile->setEnabled(true); // à ajuster!
	mRemoveSelectedFile->setEnabled(mSelectedFileModel->rowCount() > 0);
	mRemoveAllFile->setEnabled(mSelectedFileModel->rowCount() > 0);

	updateSelectedFileCounter();
}

QStringList QSelectedFileList::selectedFiles() const
{
	return mSelectedFileModel->stringList();
}

int QSelectedFileList::selectedFilesCount() const
{
	return mSelectedFileModel->rowCount();
}


