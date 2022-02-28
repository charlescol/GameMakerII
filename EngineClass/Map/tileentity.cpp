#include "tileentity.h"
#include "EngineClass/Display/grid.h"

#include <QPainter>

DTileEntity::DTileEntity(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent) , m_distinction(false)
{
    m_firstPlanePixmap.load("Pictures\\Accessory\\Colision\\firstPlaneDesignation.png");
}

void DTileEntity::setPlane(const Plane &plane)
{
    m_plane = plane;
    setZValue(4 - m_plane);
}

void DTileEntity::enableFirstPlaneDistinction(const bool enable)
{
    m_distinction = enable;
    if(m_distinction && m_plane == firstPlane)
        setZValue(6);
    else
        setZValue(4 - m_plane);

    update();
}

quint16 DTileEntity::getPlane() const
{
    return m_plane;
}

void DTileEntity::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QGraphicsPixmapItem::paint(painter , option , widget);
    if(m_distinction && m_plane == firstPlane)
        painter->drawPixmap(QRect(0 , 0 , DGrid::getTileSize().x() + 1 , DGrid::getTileSize().y() + 1), m_firstPlanePixmap);
}

void DTileEntity::setCutingPosition(const QPoint &pos)
{
    m_cutingPosition = pos;
}

QPoint DTileEntity::getCutingPos() const
{
    return m_cutingPosition;
}

void DTileEntity::setPictureIndex(const quint16 &pictureIndex)
{
    m_pictureIndex = pictureIndex;
}

quint16 DTileEntity::getPictureIndex() const
{
    return m_pictureIndex;
}
