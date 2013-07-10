#include "XmlReader.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QRegExp>
#include <QObject>


XmlReader::XmlReader(const QString& fileName):
    m_fileName(fileName),m_cuttedNumber(0)
{
}

QList<XmlObject> XmlReader::parseObjects(double lonmin, double lonmax, double latmin, double latmax)
{

	QList<XmlObject> objects;
	QFile file(m_fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Error opening " << m_fileName ;
		exit(1);
	}
	QTextStream in(&file);
	QString buffer;

	QRegExp regExp("<object version=\"1.0\">(.*)</object>");

	while(!in.atEnd()) {
		QString line = in.readLine();    
		if (line.isEmpty()) continue;
		qDebug() << line << "|||";

		buffer.append(line);

		qDebug() << "++++" << buffer << "++++";			

		QString data;
		int pos = regExp.indexIn(buffer);
		if (pos > -1) {
			data = regExp.cap(1); 
			XmlObject obj = parseObject(buffer);
			qDebug() << "Data found!!!!! " << data << "\\\\";
			if (data.size() > DATA_MAX_SIZE)
				m_cuttedNumber++;
			else if (obj.getLatitude() <= latmax && obj.getLatitude() >= latmin &&
				 obj.getLongitude() <= lonmax && obj.getLongitude() >= lonmin )
			{
				qDebug() << "found appropriate object!";
				obj.setData(data);
				objects.push_back(obj);
			}
			buffer = "";	
		}
			
	
	}

	return objects;

}

XmlObject XmlReader::parseObject(const QString& document)
{

    QXmlStreamReader xml(document);
    XmlObject object;


    QString lastName ;
    QString data;
    double latitude;
    double longitude;

    while(!xml.atEnd() &&
          !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement) {
            lastName = xml.name().toString();
        }

        if(token == QXmlStreamReader::Characters) {
        //    qDebug() << "Characters: " << xml.text();
            if (lastName == LATITUDE_TAG){
                latitude = xml.text().toString().toDouble();
            }else if (lastName == LONGITUDE_TAG){
                longitude = xml.text().toString().toDouble();
            }

        }

        if(token == QXmlStreamReader::EndElement) {
            if (xml.name().toString() == OBJECT_TAG){
  //              qDebug() << "End element" << xml.name();
                object.setLatitude(latitude);
		object.setLongitude(longitude);

            }

        }

    }

    if(xml.hasError()) {
        qDebug() << "Error during XML parsing";
    }
	return object;

}


int XmlReader::getCuttedNumber() const
{
    return m_cuttedNumber;
}
