#include "slacktoomplconverter.h"
#include <QRegularExpression>
#include <QTextStream>
#include <QXmlStreamWriter>

SlackToOmplConverter::SlackToOmplConverter(QObject *parent) :
	IConverter(parent)
{}

bool SlackToOmplConverter::performConversion()
{
	QTextStream inStream(inDevice);

	QXmlStreamWriter outStream(outDevice);
	outStream.setAutoFormatting(true);
	outStream.setAutoFormattingIndent(-1);

	outStream.writeStartDocument();
	outStream.writeStartElement(QStringLiteral("opml"));
	outStream.writeAttribute(QStringLiteral("version"), QStringLiteral("2.0"));
	outStream.writeStartElement(QStringLiteral("body"));
	outStream.writeStartElement(QStringLiteral("outline"));
	outStream.writeAttribute(QStringLiteral("text"), QStringLiteral("Subscriptions"));
	outStream.writeAttribute(QStringLiteral("title"), QStringLiteral("Subscriptions"));

	QRegularExpression regex(QStringLiteral(R"__(URL: (.*))__"));
	while(!inStream.atEnd()) {
		auto line = inStream.readLine();
		auto match = regex.match(line);
		if(match.hasMatch()) {
			auto url = match.captured(1);
			outStream.writeStartElement(QStringLiteral("outline"));
			outStream.writeAttribute(QStringLiteral("xmlUrl"), url);
			outStream.writeEndElement();
		}
	}

	outStream.writeEndElement();
	outStream.writeEndElement();
	outStream.writeEndElement();
	outStream.writeEndDocument();

	return true;
}
