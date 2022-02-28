#include "daomap.h"
#include "EngineClass/Display/grid.h"

DDAOMap::DDAOMap(const QSize &sizeMap , const QString &mapName) : DDatabaseHandler()
{
    m_mapName = mapName;
    m_sizeMap = sizeMap;

    QString sizeX(QString::number(m_sizeMap.width()));
    QString sizeY(QString::number(m_sizeMap.height()));
    QString tileSizeX(QString::number(DGrid::getTileSize().x()));
    QString tileSizeY(QString::number(DGrid::getTileSize().y()));

    qDebug() << m_mapName << sizeX << sizeY << tileSizeX << tileSizeY;

    QString query = QString("INSERT INTO [%1].[dbo].[Map_mainFeatures] VALUES (\'%2\',%3,%4,%5,%6)").arg(m_dbName).arg(m_mapName).arg(sizeX).arg(sizeY).arg(tileSizeX).arg(tileSizeY);
    m_query.exec(query);
}

void DDAOMap::addEntityToTable(const DTileEntity* entity)
{
    QString posX(QString::number(entity->pos().x()));// La position
    QString posY(QString::number(entity->pos().y()));
    QString plane(QString::number(static_cast<int>(entity->getPlane())));// Le plan

    QString pictureIndex(QString::number(static_cast<int>(entity->getPictureIndex())));// L'image

    QString cutingPosX(QString::number(entity->getCutingPos().x()));// La position de découpage
    QString cutingPosY(QString::number(entity->getCutingPos().y()));

    QString query = QString("INSERT INTO [%1].[dbo].[Map_display] VALUES (%2,%3,%4,%5,%6,%7)").arg(m_dbName).arg(posX).arg(posY).arg(plane).arg(pictureIndex).arg(cutingPosX).arg(cutingPosY);
    m_query.exec(query);

}


