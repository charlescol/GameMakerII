#include "eraser.h"
#include "EngineClass/Display/grid.h"

DEraser::DEraser(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent) , m_size(1 , 1)
{
    m_eraserPixmap = QPixmap(DGrid::getTileSize().x() , DGrid::getTileSize().y());
    m_eraserPixmap.load("Pictures/Accessory/gomme.png");
    m_eraserRect.push_back(std::shared_ptr<QGraphicsPixmapItem> (new QGraphicsPixmapItem(m_eraserPixmap)));

    addToGroup(m_eraserRect[0].get());

    setZValue(6);
}

QSize DEraser::getSize() const
{
    return m_size;
}

void DEraser::setSize(QGraphicsSceneWheelEvent *wheelEvent, quint16 limitSizeX, quint16 limitSizeY)
{
    qint16 deltaCoeficient = wheelEvent->delta() / abs(wheelEvent->delta());// Pour savoir si on augmente ou réduit la taille de la gomme
    bool isAbleToSetSize(false);// Verifie si on peut changer la taille de la gomme

    if(deltaCoeficient == 1)
    {
        QSize maxEraserSize(15 , 15);// La valeur maximale de la taille de la gomme
        if(m_size.width() < maxEraserSize.width() && m_size.height() < maxEraserSize.height() && m_size.width() // Pour ne pas que la gomme soit plus grande que l'écran on fixe une limite
                && m_size.width() < limitSizeX && m_size.height() < limitSizeY)// Pour ne pas que la gomme soit plus grande que le quadrillage
        {
            m_size.setWidth(m_size.width() + 1);
            m_size.setHeight(m_size.height() + 1);
            isAbleToSetSize = true;
        }
    }
    else
    {
        if(m_size.width() > 1 && m_size.height() > 1)
        {
            m_size.setWidth(m_size.width() - 1);
            m_size.setHeight(m_size.height() - 1);
            isAbleToSetSize = true;
        }
    }

    if(isAbleToSetSize)// Si on peut changer la taille de la gomme
    {
        m_eraserRect.clear();// On détruit l'encienne gomme
        for(quint16 x(0); x < m_size.width(); ++x){
            for(quint16 y(0); y < m_size.height(); ++y)
            {
                std::shared_ptr<QGraphicsPixmapItem> pixmapItem(new QGraphicsPixmapItem(m_eraserPixmap));
                pixmapItem.get()->setPos(QPointF(this->pos().x() + x * DGrid::getTileSize().x() ,this->pos().y() + y * DGrid::getTileSize().y()));

                m_eraserRect.push_back(pixmapItem);// On en genere une nouvelle
                addToGroup(pixmapItem.get());
            }
        }
    }
}
