#include "mapdisplay.h"
#include "EngineClass/Display/grid.h"

DMapDisplay::DMapDisplay()
{
    m_currentIndexPicture = 0;
    m_size = QSize(0 , 0);
}

void DMapDisplay::setSizeMap(const QSize &size)
{
    for(quint16 y(0); y < SIZE_planeEnum; ++y) {
        Plane plane = static_cast<Plane>(y);

        if(m_size.height() > size.height()) { // Si on rendimensionne en y de facon plus petite alors on supprime les tiles hors de la scene (en y)
            for(quint16 i(0); i < m_size.width(); ++i) {
                if(m_map[y].contains(convertPosToKey(QPointF(i * DGrid::getTileSize().x(), (m_size.height() - 1) * DGrid::getTileSize().y()))))
                    deleteTile(convertPosToKey(QPointF(i * DGrid::getTileSize().x(), (m_size.height() - 1) * DGrid::getTileSize().y())) , plane);
            }
        }
        else if(m_size.width() > size.width()) {// Sinon si on rendimensionne en x de facon plus petite alors on supprime les tiles hors de la scene (en x)
            for(quint16 j(0); j < m_size.height(); ++j) {
                if(m_map[y].contains(convertPosToKey(QPointF((m_size.width() - 1) * DGrid::getTileSize().x(), j * DGrid::getTileSize().y()))))
                    deleteTile(convertPosToKey(QPointF((m_size.width() - 1) * DGrid::getTileSize().x(), j * DGrid::getTileSize().y())) , plane);
            }
        }
    }

    m_size = size;
}

std::array<QMap<QString, std::shared_ptr<DTileEntity> >, SIZE_planeEnum> &DMapDisplay::getMapItems()
{
    return m_map;
}

void DMapDisplay::addTile(std::shared_ptr<DTileEntity> &tileEntity , const Plane& plane)
{
    tileEntity.get()->setPlane(plane);
    tileEntity.get()->setPictureIndex(m_currentIndexPicture);
    m_map[plane].insert(convertPosToKey(tileEntity.get()->pos()) , tileEntity);
}

void DMapDisplay::clearMap()
{
    for(quint16 i(0); i < SIZE_planeEnum; ++i)
        m_map[i].clear();
}

QString DMapDisplay::convertPosToKey(const QPointF &pos)
{
    QString key = QString::number(pos.x());
    key += QString::fromLatin1("*") + QString::number(pos.y());
    return key;
}

QPointF DMapDisplay::convertKeyToPos(const QString &key)
{
    QStringList posString = key.split('*');
    return QPointF(posString.at(0).toInt() , posString.at(1).toInt());
}

void DMapDisplay::deleteTile(const QString &key , Plane& plane)
{
    m_map[plane].erase(m_map[plane].find(key));
}

void DMapDisplay::setCurrentIndexPicture(const quint16 &index)
{
    m_currentIndexPicture = index;
}

void DMapDisplay::setMapPictures(const QString &pictureName)
{
    m_pictures.insert(m_currentIndexPicture , pictureName);
}

