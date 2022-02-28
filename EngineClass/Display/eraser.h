#ifndef ERASER_H
#define ERASER_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneWheelEvent>
#include <memory>

class DEraser : public QGraphicsItemGroup
{
public:
    explicit DEraser(QGraphicsItem *parent = 0);
    void setSize(QGraphicsSceneWheelEvent * wheelEvent , quint16 limitSizeX , quint16 limitSizeY);// Permet de changer la taille de la gomme en fonction de la molette
    QSize getSize() const;
private :
     QVector<std::shared_ptr<QGraphicsPixmapItem>> m_eraserRect; // Contient l'ensemble des carrés représentants la gomme
     QPixmap m_eraserPixmap;                                     // L'apparence de la gomme
     QSize m_size;                                               // La taille de la gomme
};

#endif // ERASER_H
