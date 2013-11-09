#ifndef XMLOBJECT_H_
#define XMLOBJECT_H_

#include <QString>

class XmlObject
{
	double m_latitude;
	double m_longitude;
	QString m_data;
	QString m_id;

	void parseObject(const QString& text);
	QString extractPOI(const QString& data);
public:

	XmlObject(const QString& text);

	XmlObject(double latitude=0, double longitude=0, const QString& data="", const QString& id=""):
		m_latitude(latitude),m_longitude(longitude), m_data(data), m_id(id){}

	double getLatitude() const;
	void setLatitude(double lat);

	double getLongitude()const ;
	void setLongitude(double lon);

	const QString getData() const;
	void setData(const QString& data);

	const QString getId() const;
	void setId(const QString& id);

	bool isValid() const;

};

#endif
