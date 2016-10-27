#include "opmltoslackconverter.h"
#include <QXmlStreamReader>

OpmlToSlackConverter::OpmlToSlackConverter(QObject *parent) :
	IConverter(parent)
{}

bool OpmlToSlackConverter::performConversion()
{
	QXmlStreamReader reader(this->inDevice);

	if(reader.readNextStartElement() && reader.name() == "opml") {
		while (reader.readNextStartElement()) {
			if(reader.name() == "body")
				return this->readOutline(reader);
			else {
				auto endName = reader.name();
				while(!reader.atEnd() && !reader.hasError()) {
					if(reader.readNext() == QXmlStreamReader::EndElement &&
					   reader.name() == endName)
						break;
				}

				this->setError(reader, "No <body> element found!");
			}
		}

		return true;
	} else
		this->setError(reader, "start element is not <opml>");

	return false;
}

void OpmlToSlackConverter::setError(QXmlStreamReader &reader, QString defaultError)
{
	if(reader.hasError())
		defaultError = "XML-Reader Error: " + reader.errorString();

	this->lastError = QString("Error at [%1:%2] --> %3")
			.arg(reader.lineNumber())
			.arg(reader.columnNumber())
			.arg(defaultError);
}

bool OpmlToSlackConverter::readOutline(QXmlStreamReader &reader)
{
	if(reader.hasError()) {
		this->setError(reader, QString());
		return false;
	}

	//check if this outline has a feed
	if(reader.name() == "outline" && reader.attributes().value("type") == "rss") {
		auto url = reader.attributes().value("xmlUrl").toString();
		QUrl realUrl(url);
		if(realUrl.isValid())
			this->writeUrl(url);
	}

	//children
	while(reader.readNextStartElement())
		this->readOutline(reader);

	return true;
}

void OpmlToSlackConverter::writeUrl(const QUrl &url)
{
	this->outDevice->write(QStringLiteral("/feed subscribe %1\n")
						   .arg(url.toString())
						   .toUtf8());
}

