#include "databasehandler.h"

DDatabaseHandler::DDatabaseHandler()
{
    m_database = QSqlDatabase::addDatabase("QODBC3");
    m_query = QSqlQuery();
    m_dbName = "Database_GameMaker";
    open();
    clearAllTables();
}

void DDatabaseHandler::open()
{
    QString serverName = "LOCALHOST\\SQLEXPRESS";

    m_database.setConnectOptions();
    QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted_Connection=yes;").arg(serverName).arg(m_dbName);
    m_database.setDatabaseName(dsn);

    if(!m_database.open())
        qDebug()<<"ERROR: "<< QSqlError(m_database.lastError()).text();
}

void DDatabaseHandler::close()
{
    m_database.close();
    m_database = QSqlDatabase();
}

void DDatabaseHandler::clearAllTables()
{
    m_query.exec("TRUNCATE TABLE [Database_GameMaker].[dbo].[Map_display]");
    m_query.exec("TRUNCATE TABLE [Database_GameMaker].[dbo].[Map_mainFeatures]");
}

DDatabaseHandler::~DDatabaseHandler()
{
    close();
}
