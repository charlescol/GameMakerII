#ifndef GRID_H
#define GRID_H

#include <QWidget>

class DGrid : public QWidget
{
public:
    DGrid(const quint16 nbQuadX,const quint16 nbQuadY, QWidget *parent = 0);
    static QPoint getTileSize();                                             // Permet de récuperer les dimensions des cases du quadrillage
    void isVisible(const bool visible);                                      // Permet de choisir si le quadrillage est visible ou non
    void setSizeY(const quint16 nbQuadY);                                    // Permet de changer la hauteur du quadrillage
    void setGridSize(const quint16 nbQuadX ,const quint16 nbQuadY);          // Permet de changer les dimensions du quadrillage
    quint16 getSizeX() const;                                                // Permet de récuperer la largeur du quadrillage
    quint16 getSizeY() const;                                                // Permet de récuperer la hauteur du quadrillage
    QPoint grid_mousePosition(const QPointF &mousePosition);                 // On calcule la position de la souris par rapport au quadrillage
private :
    void generateGrid(const quint16 nbQuadX,const quint16 nbQuadY ,const qint16 x = 0,const qint16 y = 0);    // Permet de generer un quadrillage
    virtual void paintEvent(QPaintEvent * event);                                                             // Permet de dessiner un quadrillage
    QVector<QLine> m_grid;                                                                                    // Un tableau dynamique contenant les lignes du quadrillage
    bool m_isVisible;                                                                                         // Regler la visibilité du quadrillage
    QSize m_size;                                                                                             // La taille du quadrillage
};

#endif // GRID_H
