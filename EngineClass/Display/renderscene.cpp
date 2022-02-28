#include "renderscene.h"
#include "EngineClass/Map/tileentity.h"
#include <cmath>
#include <iterator>
#include <qDebug>
DRenderScene::DRenderScene(QObject *parent)
    : QGraphicsScene(parent) , m_grid(10 , 10) , m_drawingMode(Brush) , m_planeMode(thirdPlane)
{
    addWidget(&m_grid);
    items(QPointF(0,0) , Qt::IntersectsItemShape , Qt::AscendingOrder)[0]->setZValue(5);
    m_grid.setAttribute(Qt::WA_TranslucentBackground, true);// Permet de rendre le fond du QWidget transparent
    
    addItem(&m_selection);
    addItem(&m_eraser);
    setBackgroundBrush(Qt::gray);
    
    m_eraser.setVisible(false);
    m_longMouseClick = false;
    m_opacityIsActivated = false;
}

void DRenderScene::setGridVisible(const bool isVisible)
{
    m_grid.isVisible(isVisible);
}

void DRenderScene::setGridSize(const qreal sizeX, const qreal sizeY)
{
    m_grid.setGridSize(sizeX , sizeY);
    setSceneRect(0, 0, sizeX * DGrid::getTileSize().x() , sizeY * DGrid::getTileSize().y());
}

void DRenderScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(m_grid.grid_mousePosition(event->scenePos()));

    if(m_drawingMode == Brush) m_selection.setPos(pos);
    else if (m_drawingMode == Eraser) m_eraser.setPos(pos);
    
    if(pos.x() >= m_grid.getSizeX() * DGrid::getTileSize().x() || pos.y() >= m_grid.getSizeY() * DGrid::getTileSize().y()
            || pos.x() < 0 || pos.y() < 0)
    {
        setSceneRect(0, 0, m_grid.getSizeX() * DGrid::getTileSize().x() , m_grid.getSizeY() * DGrid::getTileSize().y());
        m_selection.setVisible(false);// Si la selection n'est pas dans le quadrillage on la rend invisible
        m_eraser.setVisible(false);   // Si la gomme n'est pas dans le quadrillage on la rend invisible
    }
    else if(!m_selection.isVisible() && m_drawingMode == Brush) m_selection.setVisible(true);// Si la selection est dans le quadrillage on la rend visible
    else if(!m_eraser.isVisible() && m_drawingMode == Eraser) m_eraser.setVisible(true);
    
    if(m_longMouseClick)// si le clique gauche est maintenu
    {
        if(m_drawingMode == Brush)
            drawTile(m_grid.grid_mousePosition(event->scenePos()));
        else if(m_drawingMode == Eraser)
            deleteTile(m_grid.grid_mousePosition(event->scenePos()));
    }

}

void DRenderScene::setSelectionSize(const QSize newSize)
{
    m_selection.setSize(newSize);
}

void DRenderScene::addItemToMap(const QPixmap &pixmap , const QPoint& cutingPos)
{
    m_pixmapSelected = pixmap;
    m_cutingPosPixmapSelected = cutingPos;
}

void DRenderScene::drawTile(const QPoint &grid_mousePosition)
{
    if(m_selection.isVisible() && (m_pixmapSelected.size().width() >= DGrid::getTileSize().x() || m_pixmapSelected.size().height() >= DGrid::getTileSize().y()))
    {

        for(quint16 y(0); y < m_selection.getSize().height(); ++y){
            for(quint16 x(0); x < m_selection.getSize().width(); ++x)
            {
                if(grid_mousePosition.x() + x * DGrid::getTileSize().x() < m_grid.getSizeX() * DGrid::getTileSize().x() && grid_mousePosition.y() + y * DGrid::getTileSize().y() < m_grid.getSizeY() * DGrid::getTileSize().y())
                {
                    std::shared_ptr<DTileEntity> tile(new DTileEntity());
                    tile.get()->setPos(QPointF(grid_mousePosition.x() + x * DGrid::getTileSize().x(), grid_mousePosition.y() + y * DGrid::getTileSize().y()));

                    if(m_longMouseClick) // Si le clique est maintenu
                    {
                        quint16 Xcopy = abs((grid_mousePosition.x() + x * DGrid::getTileSize().x()) - m_posWhenClick.x()) % m_pixmapSelected.size().width();
                        quint16 Ycopy = abs((grid_mousePosition.y() + y * DGrid::getTileSize().y()) - m_posWhenClick.y()) % m_pixmapSelected.size().height();
                        tile.get()->setPixmap(m_pixmapSelected.copy(QRect(Xcopy , Ycopy , DGrid::getTileSize().x() , DGrid::getTileSize().y())));
                        tile.get()->setCutingPosition(QPoint(m_cutingPosPixmapSelected.x() + Xcopy , m_cutingPosPixmapSelected.y() + Ycopy));
                    }
                    else {
                        tile.get()->setPixmap(m_pixmapSelected.copy(QRect(x * DGrid::getTileSize().x() ,y * DGrid::getTileSize().y() , DGrid::getTileSize().x() , DGrid::getTileSize().y())));
                        tile.get()->setCutingPosition(QPoint(m_cutingPosPixmapSelected.x() + x * DGrid::getTileSize().x() ,m_cutingPosPixmapSelected.y() + y * DGrid::getTileSize().y()));
                    }

                    m_map.addTile(tile, m_planeMode);
                    addItem(tile.get());
                }
            }
        }
    }

}


void DRenderScene::deleteTile(const QPoint &grid_mousePosition)
{
    if(m_eraser.isVisible())
    {
        for(quint16 y(0); y < m_eraser.getSize().height(); ++y){
            for(quint16 x(0); x < m_eraser.getSize().width(); ++x)
            {
                if(grid_mousePosition.x() + x * DGrid::getTileSize().x() < m_grid.getSizeX() * DGrid::getTileSize().x()
                        && grid_mousePosition.y() + y * DGrid::getTileSize().y() < m_grid.getSizeY() * DGrid::getTileSize().y())
                {
                    QString key = DMapDisplay::convertPosToKey(QPointF(grid_mousePosition.x() + x * DGrid::getTileSize().x(), grid_mousePosition.y() + y * DGrid::getTileSize().y()));
                    m_map.deleteTile(key , m_planeMode);
                }
            }
        }
    }
}

void DRenderScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_drawingMode == Brush) {
        drawTile(m_grid.grid_mousePosition(event->scenePos()));
        m_posWhenClick = QPoint(m_grid.grid_mousePosition(event->scenePos()));
    }
    else if(m_drawingMode == Eraser)
        deleteTile(m_grid.grid_mousePosition(event->scenePos()));
    else if(m_drawingMode == Colision)
        drawColisions(m_grid.grid_mousePosition(event->scenePos()));

    m_longMouseClick = true;
}

void DRenderScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_longMouseClick = false;
    QGraphicsScene::mouseReleaseEvent(event);
}

void DRenderScene::setDrawingMode(const Mode &mode)
{
    m_drawingMode = mode;

    if(m_drawingMode == Brush) {
        m_eraser.setVisible(false);// On rend la gomme invisible
        m_colisionsMap.setVisible(false);// On rend les collisions invisibles
    }

    else if (m_drawingMode == Eraser) {
        m_selection.setVisible(false);// On rend la selection invisible
        m_colisionsMap.setVisible(false);
    }
    else if(m_drawingMode == Colision) {
        m_selection.setVisible(false);
        m_eraser.setVisible(false);

        m_colisionsMap.setVisible(true);// On rend les collisions visibles
    }

    for(quint16 i(0); i < SIZE_planeEnum; ++i) {
        for(auto it : m_map.getMapItems()[i].keys())
            m_map.getMapItems()[i][it].get()->enableFirstPlaneDistinction(m_colisionsMap.isVisible());
    }
}

void DRenderScene::setPlaneMode(const Plane &plane)
{
    m_planeMode = plane;
    if(m_opacityIsActivated)
        ajustItemsOpacity();

}

void DRenderScene::ajustItemsOpacity()
{
    m_opacityIsActivated = true;
    const qreal highOpacity(1) , lowOpacity(0.2);
    qreal opacity;

    for(quint16 i(0); i < SIZE_planeEnum; ++i) {
        if(i == m_planeMode)
            opacity = highOpacity;
        else opacity = lowOpacity;
        for(auto it : m_map.getMapItems()[i].keys()) {
            m_map.getMapItems()[i][it].get()->setOpacity(opacity);
        }
    }
}

void DRenderScene::showOpacity(const bool &opacityIsActivated)
{
    if(opacityIsActivated)
        ajustItemsOpacity();
    else {
        for(quint16 i(0); i < SIZE_planeEnum; ++i) {
            for(auto it : m_map.getMapItems()[i].keys()) {
                m_map.getMapItems()[i][it].get()->setOpacity(1);
            }
        }
        m_opacityIsActivated = false;
    }
}

void DRenderScene::wheelEvent(QGraphicsSceneWheelEvent * wheelEvent)
{
    if(m_drawingMode == Eraser)
        m_eraser.setSize(wheelEvent , m_grid.getSizeX() , m_grid.getSizeY());
}

std::array<QMap<QString, std::shared_ptr<DTileEntity> >, SIZE_planeEnum>& DRenderScene::getMap()
{
    return m_map.getMapItems();
}

void DRenderScene::clearMap()
{
    m_map.clearMap();
}

void DRenderScene::setSizeMap(const QSize &sizeMap)
{
    m_map.setSizeMap(sizeMap);
    m_colisionsMap.setSizeMap(sizeMap);
}

void DRenderScene::setCurrentPictureIndex(const quint16 &index)
{
    m_map.setCurrentIndexPicture(index);
}

void DRenderScene::drawColisions(const QPoint &grid_mousePosition)
{
    if(grid_mousePosition.x() < m_grid.getSizeX() * DGrid::getTileSize().x() && grid_mousePosition.y() < m_grid.getSizeY() * DGrid::getTileSize().y()
            && grid_mousePosition.x() >= 0 && grid_mousePosition.y() >= 0)
    {
        bool firstPlaneExist = m_map.getMapItems()[firstPlane].contains(DMapDisplay::convertPosToKey(grid_mousePosition)); // On vérifie si il existe un item de 3eme plan a cette position

        QGraphicsPixmapItem *item = m_colisionsMap.setNextColisionAt(static_cast<QPointF> (grid_mousePosition) , firstPlaneExist); // On modifie la collision
        if(!this->items().contains(item) && item != nullptr)
            this->addItem(item);
    }
    update();
}

void DRenderScene::associatePictureWithCurentMap(const QString &pictureName)
{
    m_map.setMapPictures(pictureName);
}
