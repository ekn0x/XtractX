#ifndef Q_CUSTOM_HEADER_FILE_SYSTEM_MODEL_H
#define Q_CUSTOM_HEADER_FILE_SYSTEM_MODEL_H



#include <QFileSystemModel>



class QCustomHeaderFileSystemModel : public QFileSystemModel
{
	Q_OBJECT

public:
	QCustomHeaderFileSystemModel(QObject *parent = nullptr);
	~QCustomHeaderFileSystemModel();

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // Q_CUSTOM_HEADER_FILE_SYSTEM_MODEL_H
