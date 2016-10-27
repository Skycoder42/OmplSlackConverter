#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>
#include "iconverter.h"
#include "opmltoslackconverter.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCommandLineParser parser;

	parser.addVersionOption();
	parser.addHelpOption();
	parser.addOption({
						 {"m", "mode"},
						 "Specifies whether to read slack to OPML or the other way around. "
						 "Enter \"slack\" to convert TO slack and \"opml\" to convert TO OPML as <mode>.",
						 "mode"
					 });
	parser.addPositionalArgument("in", "The file to be read as input");
	parser.addPositionalArgument("out", "The file to be written as output");
	parser.process(a);
	if(parser.positionalArguments().size() != 2)
		parser.showHelp(EXIT_FAILURE);

	IConverter *converter;
	if(parser.value("m") == "slack")
		converter = new OpmlToSlackConverter(&a);
	else if(parser.value("m") == "opml")
		converter = nullptr;
	else
		parser.showHelp(EXIT_FAILURE);

	if(converter->setDevices(parser.positionalArguments()[0], parser.positionalArguments()[1])) {
		if(converter->performConversion()) {
			std::cerr << "Conversion successful!" << std::endl;
			return EXIT_SUCCESS;
		}
	}

	auto printStr = converter->errorString().toUtf8() + "\n";
	std::cerr.write(printStr.constData(), printStr.size());
	std::cerr.flush();
	return EXIT_FAILURE;
}
