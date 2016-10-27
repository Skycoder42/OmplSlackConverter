#ifndef ICONVERTER_H
#define ICONVERTER_H

#include <QObject>
#include <QString>
#include <QIODevice>

class IConverter : public QObject
{
public:
	IConverter(QObject *parent = nullptr);

	bool setDevices(const QString &in, const QString &out);

	virtual bool performConversion() = 0;
	QString errorString() const;

protected:
	QIODevice *inDevice;
	QIODevice *outDevice;
	QString lastError;
};

#endif // ICONVERTER_H
