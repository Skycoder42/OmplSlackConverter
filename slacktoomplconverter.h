#ifndef SLACKTOOMPLCONVERTER_H
#define SLACKTOOMPLCONVERTER_H

#include "iconverter.h"

class SlackToOmplConverter : public IConverter
{
	Q_OBJECT
public:
	explicit SlackToOmplConverter(QObject *parent = nullptr);

public:
	bool performConversion() override;
};

#endif // SLACKTOOMPLCONVERTER_H
