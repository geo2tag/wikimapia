#ifndef XMLREADER_H_
#define XMLREADER_H_

#include "XmlObject.h"
#include <QString>

#define XML_SUBFILE_START QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>")

class XmlReader
{
	QString m_fileName;	
	int m_cuttedNumber;


public:
	XmlReader(const QString& fileName);

	QList<XmlObject> parseObjects(double lonmin, double lonmax, 
		double latmin, double latmax);

	int getCuttedNumber() const ;

};

#endif
