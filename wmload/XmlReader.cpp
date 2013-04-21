#include "XmlReader.h"
#include <QFile>
#include <QDebug>


XmlReader::XmlReader(const QString& fileName):
    m_fileName(fileName),m_cuttedNumber(0)
{

}

QList<XmlObject> XmlReader::parseObjects(double lonmin, double lonmax, double latmin, double latmax)
{
    QFile* file = new QFile(m_fileName);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening " << m_fileName ;
        exit(1);
    }

    QXmlStreamReader xml(file);
    QList< XmlObject > objects;


    QString lastName ;
    QString data;
    double latitude;
    double longitude;

    while(!xml.atEnd() &&
          !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

   //     if(token == QXmlStreamReader::StartDocument) {
  //          continue;
   //     }


        if(token == QXmlStreamReader::StartElement) {

          //  qDebug() << "StartElement" << xml.name();
            lastName = xml.name().toString();
        }

        if(token == QXmlStreamReader::Characters) {
        //    qDebug() << "Characters: " << xml.text();
            if (lastName == PLACE_TAG){
                data = xml.text().toString();
            }else if (lastName == LATITUDE_TAG){
                latitude = xml.text().toString().toDouble();
            }else if (lastName == LONGITUDE_TAG){
                longitude = xml.text().toString().toDouble();
            }

        }

        if(token == QXmlStreamReader::EndElement) {
            if (xml.name().toString() == OBJECT_TAG){
                qDebug() << "End element" << xml.name();
                XmlObject obj(latitude, longitude, data);
                if (isTooBig(obj))
                    m_cuttedNumber++;
                else if (latitude <= latmax && latitude >= latmin &&
                         longitude <= lonmax && longitude >= lonmin )
                    objects.push_back(obj);

            }

        }


    }

    if(xml.hasError()) {
        qDebug() << "Error during XML parsing";
    }


    return objects;
}

bool XmlReader::isTooBig(const XmlObject& obj)
{
    return false;
}


int XmlReader::getCuttedNumber() const
{
    return m_cuttedNumber;
}
