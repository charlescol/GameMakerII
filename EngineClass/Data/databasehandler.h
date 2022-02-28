#ifndef DDATABASEHANDLER_H
#define DDATABASEHANDLER_H

#include <QtSql>

class DDatabaseHandler
{
public:
    DDatabaseHandler();
    void open();
    void close();
    void clearAllTables();
    ~DDatabaseHandler();
protected :
    QSqlDatabase m_database;
    QSqlQuery m_query;
    QString m_dbName;
};

#endif // DDATABASEHANDLER_H
