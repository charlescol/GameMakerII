#ifndef DDAOMAP_H
#define DDAOMAP_H

#include "databasehandler.h"
#include "EngineClass/Map/tileentity.h"

class DDAOMap : public DDatabaseHandler
{
public:
    DDAOMap(const QSize& sizeMap, const QString &mapName = "");
    void addEntityToTable(const DTileEntity* entity);
private :
    QSize m_sizeMap;
    QString m_mapName;
};

#endif // DDAOMAP_H
