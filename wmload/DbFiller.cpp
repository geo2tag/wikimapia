#include "DbFiller.h"
#include <QDebug>
#include <QDateTime>
#include <QSqlRecord>
#include <QtSql>

DbFiller::DbFiller(const QString& dbName, const QString& channel):
    m_channel(channel){
    initDb(dbName);
}

void DbFiller::fillDb(const QList<XmlObject>& objects){
    addChannel(m_channel);
    for (int i = 0 ; i < objects.size(); i++){
        addTag(objects.at(i));
    }
}

void DbFiller::initDb(const QString& dbName){
    QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL") ;
    database.setHostName(DB_HOST);
    database.setDatabaseName(dbName);
    database.setUserName(DB_USER);
    database.setPassword(DB_PASSWORD);

    bool result = database.open();
    qDebug() << "Connecting to db, result = "<< result;

}

void DbFiller::addChannel(const QString& channel){

    if (getChannelId(channel) != 0){
	qDebug() <<"Channel already exists, skip creation";
	return;
    }

    QSqlQuery addChannelQuery(QSqlDatabase::database());
        addChannelQuery.prepare("insert into channel (name,description,url,owner_id) values(:name, :description, :url, :owner_id);");
        addChannelQuery.bindValue(":name",channel);
        addChannelQuery.bindValue(":description", "added by wmloader");
        addChannelQuery.bindValue(":url", "http://wikimapia.org/");
        addChannelQuery.bindValue(":owner_id", getUserId(DB_CHANNEL_OWNER));

        QSqlDatabase::database().transaction();

        bool result=addChannelQuery.exec();
        if(!result)
        {
            QSqlDatabase::database().rollback();
        }else{
	    qDebug() << "channel " << channel << " added successfuly";
            QSqlDatabase::database().commit();
        }
}

void DbFiller::addTag(const XmlObject& tag){
    QSqlQuery addTagQuery(QSqlDatabase::database());
    addTagQuery.prepare("insert into tag (altitude , latitude, longitude, label, description, url, user_id,  channel_id) "
                        "         values(:altitude, :latitude, :longitude, :label, :description, :url, :user_id, :channel_id);");

    addTagQuery.bindValue(":altitude", 0.0);
    addTagQuery.bindValue(":latitude", tag.m_latitude);
    addTagQuery.bindValue(":longitude", tag.m_longitude);
    addTagQuery.bindValue(":description", tag.m_data.isEmpty() ? "data is empty": tag.m_data);
    addTagQuery.bindValue(":label", "added by wmloader");
    addTagQuery.bindValue(":url", "http://wikimapia.org/");

    addTagQuery.bindValue(":user_id", getUserId(DB_CHANNEL_OWNER));
    addTagQuery.bindValue(":channel_id", getChannelId(m_channel));

    QSqlDatabase::database().transaction();


    bool result = addTagQuery.exec();
    qDebug() << addTagQuery.executedQuery();
    if(!result)
    {
        QSqlDatabase::database().rollback();
        return ;
    }

    qDebug() << "tag added successfuly";
    QSqlDatabase::database().commit();


}

qlonglong DbFiller::getChannelId(const QString& channel){
    QSqlQuery query(QSqlDatabase::database());

    query.prepare("select id from channel where name=:name;");
    query.bindValue(":name",channel);
    query.exec();
    qlonglong id =0;  //default value

    if(query.next())
    {
        id = query.record().value("id").toLongLong();
    }

    return id;
}

qlonglong DbFiller::getUserId(const QString& name){
    QSqlQuery query(QSqlDatabase::database());

    query.prepare("select id from users where login=:login;");
    query.bindValue(":login",name);
    query.exec();
    qlonglong id =0;  //default value

    if(query.next())
    {
        id = query.record().value("id").toLongLong();
    }

    return id;

}
