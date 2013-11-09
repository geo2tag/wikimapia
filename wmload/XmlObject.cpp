#include "XmlObject.h"
#include <QTextStream>
#include <QtXml/QXmlStreamReader>
#include <QDebug>

#define DATA_MAX_SIZE 2048//600048
#define OBJECT_TAG QString("object")
#define LATITUDE_TAG QString("lat")
#define LONGITUDE_TAG QString("lon")
#define PLACE_TAG QString("place")
#define ID_TAG QString("id")

#define POLYGON_OPENING_TAG QString("<polygon>")

void XmlObject::parseObject(const QString& text)
{
	QXmlStreamReader xml(text);
	QString lastName ;

	while(!xml.atEnd() &&
		!xml.hasError()) 
	{

		QXmlStreamReader::TokenType token = xml.readNext();
		if(token == QXmlStreamReader::StartElement)
			lastName = xml.name().toString();
		

		if(token == QXmlStreamReader::Characters) {
			if (lastName == LATITUDE_TAG)
				m_latitude = xml.text().toString().toDouble();
			else if (lastName == LONGITUDE_TAG)
				m_longitude = xml.text().toString().toDouble();
			else if (lastName == ID_TAG)
				m_id = xml.text().toString();
		}
	}

	if(xml.hasError()) 
		qDebug() << "Error during XML parsing id = " << m_id;
	

	setData(text);

}

XmlObject::XmlObject(const QString& text){
	parseObject(text);
}

double XmlObject::getLatitude() const
{
	return m_latitude;
}

void XmlObject::setLatitude(double lat)
{
	m_latitude = lat;
}

double XmlObject::getLongitude()const 
{
	return m_longitude;
}


void XmlObject::setLongitude(double lon)
{
	m_longitude = lon;
}

const QString XmlObject::getData() const
{
	return m_data;
}

QString XmlObject::extractPOI(const QString& data)
{
	QString	result;
	int index = data.indexOf(POLYGON_OPENING_TAG);
	if (index > -1)
	{
		qDebug()  << "found <polygon> tag at id=" << m_id;
		if (data.left(index).size() <= DATA_MAX_SIZE) {
			result = data.left(index);
		}else {
			qDebug() << "POI too big, id = " << m_id;
			qDebug() << "size = " << data.left(index).size();
		}
			 
	}

	return result;
}

void XmlObject::setData(const QString& data)
{
	QString dataString = data; 
	if (data.size() > DATA_MAX_SIZE)
		dataString = extractPOI(data);


	qDebug() << "POI = " << dataString;

	m_data = dataString;
}

const QString XmlObject::getId() const
{
	return m_id;
}

void XmlObject::setId(const QString& id)
{
	m_id = id;
}

bool XmlObject::isValid() const{
	return !m_data.isEmpty();
}
