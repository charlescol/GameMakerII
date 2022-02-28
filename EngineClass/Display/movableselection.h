#ifndef MOVABLESELECTION_H
#define MOVABLESELECTION_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <memory>

class DMovableSelection : public QGraphicsItemGroup
{
public:
    explicit DMovableSelection(QGraphicsItem * parent = 0);
    QSize getSize() const;                                               // Permet de connaitre la taille de la selection
    void setSize(const QSize& newSize);                                  // Permet de modifier la taille de la selection
protected :
    QVector<std::shared_ptr<QGraphicsPixmapItem>> m_selectionRect;       // Les rectangles de selection
    QPixmap m_selectionPixmap;                                           // L'image de la selection
    QSize m_size;                                                        // La taille en carreaux de la selection

};

#endif // MOVABLESELECTION_H
