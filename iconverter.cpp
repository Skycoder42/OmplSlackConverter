#include "iconverter.h"
#include <QFile>

IConverter::IConverter(QObject *parent) :
	QObject(parent),
	inDevice(nullptr),
	outDevice(nullptr),
	lastError()
{}

bool IConverter::setDevices(const QString &in, const QString &out)
{
	this->inDevice = new QFile(in, this);
	if(!this->inDevice->open(QIODevice::ReadOnly | QIODevice::Text)) {
		this->lastError = this->inDevice->errorString();
		return false;
	}

	this->outDevice = new QFile(out, this);
	if(!this->outDevice->open(QIODevice::WriteOnly | QIODevice::Text)) {
		this->lastError = this->outDevice->errorString();
		return false;
	}

	return true;
}

QString IConverter::errorString() const
{
	return this->lastError;
}
