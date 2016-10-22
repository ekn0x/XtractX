#include "QCustomHeaderFileSystemModel.h"

QCustomHeaderFileSystemModel::QCustomHeaderFileSystemModel(QObject *parent)
	: QFileSystemModel(parent)
{
}

QCustomHeaderFileSystemModel::~QCustomHeaderFileSystemModel()
{
}

QVariant QCustomHeaderFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
	if (role == Qt::DisplayRole) {
		switch (section) {
			case 0: return tr("Nom");
			case 1: return tr("Taille");
			case 2: return tr("Type");
			case 3: return tr("Dernière modification");
		}
	}

	return QFileSystemModel::headerData(section, orientation, role);
}

