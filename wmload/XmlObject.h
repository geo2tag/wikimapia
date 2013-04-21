#ifndef XMLOBJECT_H_
#define XMLOBJECT_H_

struct XmlObject
{
    double m_latitude;
    double m_longitude;
    QString m_data;

    XmlObject(double latitude, double longitude, const QString& data):
        m_latitude(latitude),m_longitude(longitude), m_data(data){}
};

#endif
