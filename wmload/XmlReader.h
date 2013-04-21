#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <QtXml/QXmlStreamReader>
#include "XmlObject.h"


#define OBJECT_TAG QString("object")
#define LATITUDE_TAG QString("lat")
#define LONGITUDE_TAG QString("lon")
#define PLACE_TAG QString("place")

class XmlReader
{
	QString m_fileName;	
    int m_cuttedNumber;

    bool isTooBig(const XmlObject& obj);

public:
	XmlReader(const QString& fileName);

    QList<XmlObject> parseObjects(double lonmin, double lonmax, double latmin, double latmax);

    int getCuttedNumber() const ;

};

#endif
