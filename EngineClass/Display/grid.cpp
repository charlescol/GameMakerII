#include "grid.h"
#include <QPainter>

DGrid::DGrid(const quint16 nbQuadX, const quint16 nbQuadY, QWidget *parent) :
    QWidget(parent) , m_size(nbQuadX , nbQuadY)
{
    m_isVisible = true;
    generateGrid(nbQuadX , nbQuadY);
}

void DGrid::generateGrid(const quint16 nbQuadX,const quint16 nbQuadY,const qint16 x,const qint16 y) // On dessine le quadrillage
{
    m_grid.clear();
    resize(nbQuadX * DGrid::getTileSize().x() + 1, nbQuadY * DGrid::getTileSize().y() + 1);

    float limitX = nbQuadX * getTileSize().x();
    float limitY = nbQuadY * getTileSize().y();

    if(nbQuadY > 0) {
        for(quint16 i(0); i <= nbQuadY; ++i)
        {
            QLine line(x , y + getTileSize().y() * i , limitX , y + getTileSize().y() * i);
            m_grid.push_back(line);
        }
    }
    if(nbQuadX > 0) {
        for(quint16 i(0); i <= nbQuadX; ++i)
        {
            QLine line(x + getTileSize().x()* i , y  , x + getTileSize().x() * i , limitY);
            m_grid.push_back(line);
        }
    }
    update();
}

void DGrid::setSizeY(const quint16 nbQuadY)
{
    m_size.setHeight(nbQuadY);
    generateGrid(m_size.width() , m_size.height());
}

void DGrid::setGridSize(const quint16 nbQuadX, const quint16 nbQuadY)
{
    m_size.setWidth(nbQuadX);
    m_size.setHeight(nbQuadY);
    generateGrid(m_size.width() , m_size.height());
}

quint16 DGrid::getSizeX() const
{
    return m_size.width();
}

quint16 DGrid::getSizeY() const
{
    return m_size.height();
}

void DGrid::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    if(m_isVisible) painter.drawLines(m_grid);
    else painter.drawRect(QRect(0 , 0 , m_size.width() * getTileSize().x() , m_size.height() * getTileSize().y()));
}

QPoint DGrid::getTileSize()
{
    return QPoint(32 , 32);
}

void DGrid::isVisible(bool visible)
{
    m_isVisible = visible;
    update();
}

QPoint DGrid::grid_mousePosition(const QPointF& mousePosition)
{
    qint16 grid_mousePositionX(static_cast<int>(mousePosition.x() / getTileSize().x()) * getTileSize().x());
    qint16 grid_mousePositionY(static_cast<int>(mousePosition.y() / getTileSize().y()) * getTileSize().y());

    return QPoint(grid_mousePositionX  , grid_mousePositionY);
}
