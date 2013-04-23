#include "XmlObject.h"

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

void XmlObject::setData(const QString& data)
{
	m_data = data;
}
