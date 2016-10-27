#ifndef OPMLTOSLACKCONVERTER_H
#define OPMLTOSLACKCONVERTER_H

#include "iconverter.h"
#include <QUrl>
class QXmlStreamReader;

class OpmlToSlackConverter : public IConverter
{
public:
	OpmlToSlackConverter(QObject *parent = nullptr);

	bool performConversion() override;

private:
	void setError(QXmlStreamReader &reader, QString defaultError);

	bool readOutline(QXmlStreamReader &reader);
	void writeUrl(const QUrl &url);
};

#endif // OPMLTOSLACKCONVERTER_H
