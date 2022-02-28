#include "generationselection.h"
#include "EngineClass/Display/grid.h"
#include <cmath>

DGenerationSelection::DGenerationSelection(QGraphicsItem *parent)
    : DMovableSelection(parent)
{}

void DGenerationSelection::generateSelection(const QPointF mousePosition)
{
    QPointF memory_selection = this->pos();
    QPoint soustraction((mousePosition.x() - this->pos().x()) / DGrid::getTileSize().x(), (mousePosition.y() - this->pos().y()) / DGrid::getTileSize().y());
    m_selectionRect.clear();// on detruit l'encienne selection

    qreal coeficientX(1) , coeficientY(1);
    if(soustraction.x() < 0) coeficientX = -1;
    if(soustraction.y() < 0) coeficientY = -1;

    for(quint16 y(0); y < abs(soustraction.y()) + 1; ++y){
        for(quint16 x(0); x < abs(soustraction.x()) + 1; ++x)
        {
            std::shared_ptr<QGraphicsPixmapItem> pixmapItem(new QGraphicsPixmapItem(m_selectionPixmap));// on ajoute un carré de selection sur la position de l'item
            pixmapItem.get()->setPos(QPointF(memory_selection.x() + coeficientX * x * DGrid::getTileSize().x(), memory_selection.y() + coeficientY * y * DGrid::getTileSize().x()));
            m_selectionRect.push_back(pixmapItem);

            addToGroup(m_selectionRect[m_selectionRect.size() - 1].get());
        }
    }
    m_size = QSize(abs(soustraction.x()) + 1 , abs(soustraction.y()) + 1);
    m_SubstractionPosTopLeftCornerX = 0;
    m_SubstractionPosTopLeftCornerY = 0;

    if(coeficientX == -1)
        m_SubstractionPosTopLeftCornerX =  -1 * (m_size.width() -1) * DGrid::getTileSize().x();
    if(coeficientY == -1)
        m_SubstractionPosTopLeftCornerY =  -1 * (m_size.height()-1) * DGrid::getTileSize().y();
}

void DGenerationSelection::resetSelection()
{
    QPointF last_position(this->pos());

    m_selectionRect.clear();// on detruit l'ancienne selection

    std::shared_ptr<QGraphicsPixmapItem> pixmapItem(new QGraphicsPixmapItem(m_selectionPixmap));// on ajoute un carré de selection sur la position de l'item
    pixmapItem.get()->setPos(QPointF(last_position.x(), last_position.y()));
    m_selectionRect.push_back(pixmapItem);

    addToGroup(m_selectionRect[0].get());
    m_size = QSize(1 , 1);
}

QPointF DGenerationSelection::getPosTopLeftCorner()
{
    return QPointF(this->pos().x() + m_SubstractionPosTopLeftCornerX , this->pos().y() + m_SubstractionPosTopLeftCornerY);
}

