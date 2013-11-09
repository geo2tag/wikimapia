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

QList<XmlObject> XmlReader::parseObjects(double lonmin, double lonmax, 
	double latmin, double latmax)
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
		if (line.isEmpty()) 
			continue;

		buffer.append(line);

		QString data;
		int pos = regExp.indexIn(buffer);
		if (pos > -1) {
			data = regExp.cap(1); 
			XmlObject obj(buffer);
			if (!obj.isValid())
			{
				m_cuttedNumber++;
				qDebug() << "Not included " << m_fileName << obj.getId() ;
			}
			else if (obj.getLatitude() <= latmax && obj.getLatitude() >= latmin &&
				 obj.getLongitude() <= lonmax && obj.getLongitude() >= lonmin )
			{
				qDebug() << "found appropriate object, " << m_fileName << obj.getId();
				objects.push_back(obj);
			}
			buffer = "";	
		}
			
	
	}

	return objects;

}



int XmlReader::getCuttedNumber() const
{
    return m_cuttedNumber;
}
