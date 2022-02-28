#include "movableselection.h"
#include "EngineClass/Display/grid.h"

DMovableSelection::DMovableSelection(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent) , m_size(1 , 1)
{
    m_selectionPixmap = QPixmap(DGrid::getTileSize().x() , DGrid::getTileSize().y());
    m_selectionPixmap.load("Pictures/Accessory/carreaux.png");
    m_selectionRect.push_back(std::shared_ptr<QGraphicsPixmapItem> (new QGraphicsPixmapItem(m_selectionPixmap)));
    addToGroup(m_selectionRect[0].get());

    setZValue(7);
}

QSize DMovableSelection::getSize() const
{
    return m_size;
}

void DMovableSelection::setSize(const QSize &newSize)
{
    m_size = newSize;
    m_selectionRect.clear();
    QPointF last_position(this->pos());

    for(quint16 y(0); y < newSize.height(); ++y)
    {
        for(quint16 x(0); x < newSize.width(); ++x)
        {
            std::shared_ptr<QGraphicsPixmapItem> pixmapItem(new QGraphicsPixmapItem(m_selectionPixmap));
            pixmapItem.get()->setPos(QPointF(x * DGrid::getTileSize().x() + last_position.x(), y * DGrid::getTileSize().y() + last_position.y()));
            m_selectionRect.push_back(pixmapItem);

            addToGroup(m_selectionRect[y * newSize.width() + x].get());
        }
    }
}
