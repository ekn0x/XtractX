#include "QDirectorySelector.h"


#include "QCustomHeaderFileSystemModel.h"

#include <QLabel>
#include <QTreeView>
#include <QLineEdit>
#include <QCheckBox>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDesktopServices>
#include <QUrl>

#include <QDebug>

QDirectorySelector::QDirectorySelector(QString const & title, QWidget *parent)
	: QWidget(parent)
{
	mDirectoryModel = new QCustomHeaderFileSystemModel;
	mDirectoryModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
	mDirectoryModel->setRootPath("");

	mDirectoryTitle = new QLabel(title);

	mDirectoryView = new QTreeView;
	mDirectoryView->setModel(mDirectoryModel);
	mDirectoryView->setSortingEnabled(true);
	mDirectoryView->sortByColumn(0, Qt::AscendingOrder);
	mDirectoryView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	mDirectoryView->setContextMenuPolicy(Qt::CustomContextMenu);

	mDirectoryEdit = new QLineEdit;

	mShowDetails = new QCheckBox(tr("Afficher les détails"));
	mShowDetails->setChecked(true);
	QHBoxLayout * optionLayout = new QHBoxLayout;
	optionLayout->addWidget(mShowDetails);
	optionLayout->addStretch();

	QVBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(mDirectoryTitle);
	layout->addWidget(mDirectoryView);
	layout->addWidget(mDirectoryEdit);
	layout->addLayout(optionLayout);
	layout->setContentsMargins(0, 0, 0, 0);

	setLayout(layout);

	buildContextMenu();

	connect(mDirectoryView, &QTreeView::customContextMenuRequested, this, &QDirectorySelector::contextMenuOpenFileExplorer);
	connect(mDirectoryView, &QTreeView::clicked, this, &QDirectorySelector::synchronizeEditFromTree);
	connect(mDirectoryEdit, &QLineEdit::returnPressed, this, &QDirectorySelector::synchronizeTreeFromEdit);

	connect(mDirectoryView, &QTreeView::expanded, this, &QDirectorySelector::reexpand, Qt::QueuedConnection);
	connect(this, &QDirectorySelector::treeSynchronized, this, &QDirectorySelector::reactToExpansion, Qt::QueuedConnection);

	connect(mShowDetails, &QCheckBox::clicked, this, &QDirectorySelector::showDetails);
}

QStringList QDirectorySelector::selectedFiles() const
{
	QStringList files;

	QModelIndexList indexes = mDirectoryView->selectionModel()->selectedIndexes();
	for (auto index{ indexes.begin() }; index != indexes.end(); ++++++++index) { // 4 columns => for indexes by line!
		files << mDirectoryModel->fileInfo(*index).absoluteFilePath();
	}

	return files;
}

void QDirectorySelector::synchronizeEditFromTree(QModelIndex const & index)
{
	QString fileName{ mDirectoryModel->fileInfo(index).absoluteFilePath() };
	mDirectoryEdit->setText(fileName);

	if (!QFileInfo(fileName).isDir()) {
		emit fileSelected(fileName);
	}
}

void QDirectorySelector::synchronizeTreeFromEdit()
{
	if (QDir(mDirectoryEdit->text()).exists()) {
		mDirectoryView->setFocus();
		mDirectoryView->setCurrentIndex(mDirectoryModel->index(mDirectoryEdit->text()));
		mDirectoryView->setExpanded(mDirectoryView->currentIndex(), true);

		emit treeSynchronized(mDirectoryView->currentIndex());
	} else {
		synchronizeEditFromTree(mDirectoryView->currentIndex());
	}
}

void QDirectorySelector::reexpand()
{
	mDirectoryView->setCurrentIndex(mDirectoryView->currentIndex());
	mDirectoryView->setExpanded(mDirectoryView->currentIndex(), true);

	emit treeSynchronized(mDirectoryView->currentIndex());
}

void QDirectorySelector::reactToExpansion(QModelIndex const & index)
{
	mDirectoryView->resizeColumnToContents(0);
	mDirectoryView->scrollTo(index, QAbstractItemView::PositionAtTop);
}

void QDirectorySelector::showDetails()
{
	if (mShowDetails->isChecked()) {
		mDirectoryView->showColumn(1);
		mDirectoryView->showColumn(2);
		mDirectoryView->showColumn(3);
	} else {
		mDirectoryView->hideColumn(1);
		mDirectoryView->hideColumn(2);
		mDirectoryView->hideColumn(3);
	}
}

void QDirectorySelector::buildContextMenu()
{
	mDirViewContextMenu = new QMenu(tr("Menu contextuel"), this);
	mDirViewContextMenuAction = new QAction(tr("Ouvrir l'élément sélectionné..."), this);
	mDirViewContextMenu->addAction(mDirViewContextMenuAction);

	connect(mDirViewContextMenuAction, &QAction::triggered, this, &QDirectorySelector::openItem);
}

void QDirectorySelector::contextMenuOpenFileExplorer(const QPoint &pos)
{
	mDirViewContextMenu->exec(mapToGlobal(pos));
}

void QDirectorySelector::openItem()
{
	QString path = QDir::toNativeSeparators(mDirectoryModel->fileInfo(mDirectoryView->currentIndex()).absoluteFilePath());
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}


