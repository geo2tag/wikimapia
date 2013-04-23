#ifndef XMLOBJECT_H_
#define XMLOBJECT_H_

#include <QString>

class XmlObject
{
    double m_latitude;
    double m_longitude;
    QString m_data;

public:

    XmlObject(double latitude=0, double longitude=0, const QString& data=""):
        m_latitude(latitude),m_longitude(longitude), m_data(data){}

	double getLatitude() const;
	void setLatitude(double lat);

	double getLongitude()const ;
	void setLongitude(double lon);

	const QString getData() const;
	void setData(const QString& data);

};

#endif
