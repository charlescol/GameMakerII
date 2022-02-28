#include "mapcolisions.h"
#include "EngineClass/Display/grid.h"

DMapColisions::DMapColisions() : m_isVisible(false)
{
    m_colisionPixmapFileName.append("Pictures\\Accessory\\Colision\\croixColision.png");
    m_crossingPixmapFileName.append("Pictures\\Accessory\\Colision\\etoileColisions.png");
}

QString DMapColisions::convertPosToKey(const QPointF &pos)
{
    QString key = QString::number(pos.x());
    key += QString::fromLatin1("*") + QString::number(pos.y());
    return key;
}

void DMapColisions::setSizeMap(const QSize &size)
{
    m_sizeMap = size;
}

bool DMapColisions::isVisible() const
{
    return m_isVisible;
}

void DMapColisions::setVisible(const bool isVisible)
{
    m_isVisible = isVisible;
    for(auto it : m_map.keys()) {
        if(m_map[it].item.get() != nullptr)
            m_map[it].item.get()->setVisible(isVisible);
    }

}

QGraphicsPixmapItem * DMapColisions::setNextColisionAt(const QPointF &pos , const bool& firstPlaneExist)
{
    QString key = convertPosToKey(pos);
    if(m_map.contains(key)) {
        if(m_map[key].item.get() == nullptr) {// Si les collisions étaient désactivés
            m_map[key].item.reset(new QGraphicsPixmapItem(m_colisionPixmapFileName));// On les rends actives
            m_map[key].fileName = m_colisionPixmapFileName;
        }
        else if(m_map[key].fileName == m_colisionPixmapFileName && firstPlaneExist)// Si les collisions étaient activés
        {
            m_map[key].item.reset(new QGraphicsPixmapItem(m_crossingPixmapFileName));// On y change par "passage"
            m_map[key].fileName = m_crossingPixmapFileName;
        }
        else
            m_map[key].item.reset();// Si le "passage" était activé on regle le pointer sur NULL
    }
    else {// Si l'item n'est pas deja dans le map alors on l'ajoute dans le conteneur
        struct ColisionPixmap colisionItem;
        colisionItem.fileName = m_colisionPixmapFileName;
        std::shared_ptr<QGraphicsPixmapItem> item(new QGraphicsPixmapItem(m_colisionPixmapFileName));
        colisionItem.item = item;

        m_map.insert(key , colisionItem);
    }
    if(m_map[key].item != nullptr) {
        m_map[key].item.get()->setPos(pos);
        m_map[key].item.get()->setZValue(7);
    }

    return m_map[key].item.get();
}
