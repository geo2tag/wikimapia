#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <QtXml/QXmlStreamReader>
#include "XmlObject.h"


#define OBJECT_TAG QString("object")
#define LATITUDE_TAG QString("lat")
#define LONGITUDE_TAG QString("lon")
#define PLACE_TAG QString("place")
#define XML_SUBFILE_START QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>")
#define DATA_MAX_SIZE 2048

class XmlReader
{
	QString m_fileName;	
    int m_cuttedNumber;


public:
	XmlReader(const QString& fileName);

    QList<XmlObject> parseObjects(double lonmin, double lonmax, double latmin, double latmax);
    XmlObject parseObject(const QString& document );

    int getCuttedNumber() const ;

};

#endif
