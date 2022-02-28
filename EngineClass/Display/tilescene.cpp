#include "tilescene.h"

DTileScene::DTileScene(QObject *parent) :
    QGraphicsScene(parent), m_grid(8 , 0) , m_importPicture(m_grid.getSizeX() * DGrid::getTileSize().x())
{
    addItem(&m_importPicture);
    addWidget(&m_grid);
    addItem(&m_selection);

    m_grid.setAttribute(Qt::WA_TranslucentBackground, true);// Permet de rendre le fond du QWidget transparent

    m_selection.setPos(QPointF(0 , 0));

    m_longMouseClick = false;
    m_initialHeightPicture = 1;
}

void DTileScene::importTileset(const QString &fileName)
{
    QPixmap pictureImport(fileName);
    m_initialHeightPicture = pictureImport.height();
    m_importPicture.cutPixmap(pictureImport);
    m_grid.setSizeY(m_importPicture.pixmap().size().height() / DGrid::getTileSize().y());
    setSceneRect(QRect(0 , 0 , m_grid.getSizeX() * DGrid::getTileSize().x() , m_importPicture.pixmap().size().height()));

    if(m_initialHeightPicture == 0)
        m_initialHeightPicture = 1;

    emit newPictureSignal(fileName);
    emit mouseReleaseSignal(m_importPicture.pixmap().copy(QRect(0 , 0 , DGrid::getTileSize().x() ,DGrid::getTileSize().y())) ,QPoint(0,0));
}

void DTileScene::sendPixmapSelected()
{
    quint16 cutingPosX = static_cast<int>(m_selection.getPosTopLeftCorner().y() / m_initialHeightPicture) * m_grid.getSizeX() * DGrid::getTileSize().x() + m_selection.getPosTopLeftCorner().x();
    quint16 cutingPosY = (static_cast<int>(m_selection.getPosTopLeftCorner().y()) % m_initialHeightPicture);
    emit mouseReleaseSignal(m_importPicture.pixmap().copy(QRect(m_selection.getPosTopLeftCorner().x() , m_selection.getPosTopLeftCorner().y() , m_selection.getSize().width() * DGrid::getTileSize().x() , m_selection.getSize().height() * DGrid::getTileSize().y()))
                            , QPoint(cutingPosX , cutingPosY));// On envoie l'image et la position de coupe
    emit mouseReleaseSignal(QSize(m_selection.getSize().width() , m_selection.getSize().height())); // On envoie la taille de la sélection adaptée à l'image
}

void DTileScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_longMouseClick = true;
    m_selection.resetSelection();// On réinitialise la sélection
    m_selection.setPos(m_grid.grid_mousePosition(event->scenePos()));
}

void DTileScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_longMouseClick = false;

    sendPixmapSelected();// On envoie l'image vers la scnène

    QGraphicsScene::mouseReleaseEvent(event);
}

void DTileScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_longMouseClick)// Si la touche est maintenue
    {
        QPoint grid_mousePosition = m_grid.grid_mousePosition(event->scenePos());
        if(grid_mousePosition.x() < m_grid.getSizeX() * DGrid::getTileSize().x() && grid_mousePosition.y() < m_grid.getSizeY() * DGrid::getTileSize().y()){
            m_selection.generateSelection(grid_mousePosition);
        }
    }
}
