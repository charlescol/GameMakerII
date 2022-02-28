#ifndef TILEENTITY_H
#define TILEENTITY_H

#include <QGraphicsPixmapItem>
#include <QPointer>

enum Plane {firstPlane , secondPlane  , thirdPlane , SIZE_planeEnum};// Enumeration des diférents plans

class DTileEntity : public QGraphicsPixmapItem
{
public:
    DTileEntity(QGraphicsItem *parent = 0);
    void setPlane(const Plane& plane);                   // Permet de changer le plan de l'objet
    void enableFirstPlaneDistinction(const bool enable); // Permet d'activer ou de désactiver la distinction dans l'affichage des items au 1er plan
    void setCutingPosition(const QPoint& pos);           // Permet de spécifier la position de découpage
    void setPictureIndex(const quint16 &pictureIndex);   // Permet de spécifier de quelle image provient celle de l'item

    QPoint getCutingPos() const;                         // Getter sur la position de découpage
    quint16 getPictureIndex() const;                     // Getter sur l'index de l'item
    quint16 getPlane() const;                            // Getter sur le plan de l'item
private :
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    Plane m_plane;                        // Le plan dans lequel se trouve l'item
    QPixmap m_firstPlanePixmap;           // Designe le plan de l'item lors de la modification des collisions
    bool m_distinction;
    QPoint m_cutingPosition;              // La position de découpage
    quint16 m_pictureIndex;
};

#endif // TILEENTITY_H
