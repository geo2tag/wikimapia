#include <QDebug>
#include "XmlReader.h"
#include <QCoreApplication>
#include "DbFiller.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc,argv);

	if (argc != 8){
		qDebug() << "Not enaugh parameters.\n"
		"Usage: ./wmloader datafile dbname channel lonmin lonmax latmin latmax\n";
		return 0;
	}	

	QString datafile = argv[1];
	QString dbname = argv[2];
	QString channel = argv[3];
	double lonmin = QString(argv[4]).toDouble();
	double lonmax = QString(argv[5]).toDouble();
	double latmin = QString(argv[6]).toDouble();
        double latmax = QString(argv[7]).toDouble();

	XmlReader reader(datafile);

	QList<XmlObject> objects = reader.parseObjects(lonmin, lonmax, latmin, latmax);
    qDebug() << "Not included because of too much size - " << reader.getCuttedNumber();
    qDebug() << "Parsed" << objects.size();



    DbFiller filler(dbname, channel);

    filler.fillDb(objects);
	

    return 0;//app.exec();
}
