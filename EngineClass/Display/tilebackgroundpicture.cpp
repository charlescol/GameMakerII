#include "tilebackgroundpicture.h"
#include <cmath>
#include <QPainter>

DTileBackgroundPicture::DTileBackgroundPicture(const quint16 &sizeX, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) , m_sizeX(sizeX)
{}

void DTileBackgroundPicture::cutPixmap(const QPixmap & pixmap)
{
    if(pixmap.size().width() > m_sizeX)
    {
        QPixmap background("Pictures/Tilesets/base_tileset.png");// On crée une image de fond
        background = background.copy(QRect(0 , 0 , m_sizeX , (pixmap.size().width() / m_sizeX) * pixmap.size().height()));

        QPainter painter(&background);

        for(quint16 i(0); i < ceil((float) pixmap.size().width() / m_sizeX); ++i)
                painter.drawPixmap(QRect(0 , pixmap.size().height() * i , m_sizeX , pixmap.size().height()) , pixmap.copy(m_sizeX*i , 0 , m_sizeX , pixmap.size().height()));

        QGraphicsPixmapItem::setPixmap(background);
    }
    else QGraphicsPixmapItem::setPixmap(pixmap);
}

