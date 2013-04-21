#ifndef DBFILLER_H_
#define DBFILLER_H_

#include <QSqlQuery>
#include <QList>
#include "XmlObject.h"

#define DB_USER "geo2tag"
#define DB_HOST "localhost"
#define DB_PASSWORD "geo2tag"
#define DB_CHANNEL_OWNER "Mark"

class DbFiller
{
	QString m_channel;

    qlonglong getChannelId(const QString& channel);
    qlonglong getUserId(const QString& name);


    void initDb(const QString& dbName);
    void addChannel(const QString& channel);
    void addTag(const XmlObject& tag);

public:

    DbFiller(const QString& dbName, const QString& channel);
	void fillDb(const QList<XmlObject>& objects);
	
};

#endif
