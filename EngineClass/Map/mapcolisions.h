#ifndef MAPCOLISIONS_H
#define MAPCOLISIONS_H

#include <QGraphicsPixmapItem>
#include <memory>
#include <QPointer>

class DMapColisions
{
public:
    DMapColisions();
    void setSizeMap(const QSize &size);                                                         // Permet de changer la taille de la map
    QGraphicsPixmapItem * setNextColisionAt(const QPointF& pos , const bool &firstPlaneExist);  // Permet de changer la collision d'un item
    void setVisible(const bool isVisible);                                                      // Permet de rendre visible / invisible les collisions
    bool isVisible() const;                                                                     // Getter sur m_isVisible
private :
    static QString convertPosToKey(const QPointF& pos);  // Permet de convertir un QPointF en QString pour l'utiliser comme clée dans le conteneur QMap

    struct ColisionPixmap // Contient a la fois l'item et le chemin du fichier de son image
    {
        std::shared_ptr<QGraphicsPixmapItem> item;
        QString fileName;
    };

    QMap<QString , ColisionPixmap> m_map; // Tableau contenant l'ensemble des collisions de la carte
    bool m_isVisible;                     // Permet de savoir si les collisions sont visible ou non
    QSize m_sizeMap;                      // La taille de la carte
    QString m_colisionPixmapFileName;     // L'image des collisions brutes
    QString m_crossingPixmapFileName;     // L'image des collisions de passage
};

#endif // MAPCOLISIONS_H
