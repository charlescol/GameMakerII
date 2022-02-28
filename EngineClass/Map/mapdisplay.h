#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include "EngineClass/Map/tileentity.h"
#include <memory>
#include <array>

class DMapDisplay
{
public:
    DMapDisplay();
    std::array<QMap<QString, std::shared_ptr<DTileEntity> >, SIZE_planeEnum>& getMapItems();     // Permet de récuperer les items constituants la carte
    void setSizeMap(const QSize &size);                                                          // Permet de redéfinir la taille de la carte
    void setCurrentIndexPicture(const quint16& index);                                           // Permet de définir l'onglet séléctionné
    void addTile(std::shared_ptr<DTileEntity>& tileEntity ,const Plane &plane);                  // Permet d'ajouter un élement à la carte
    void clearMap();                                                                             // Permet de détruire la carte
    void deleteTile(const QString& key , Plane& plane);                                          // Permet de détruire une case du tableau
    void setMapPictures(const QString& pictureName);                                             // Permet d'indiquer les images associées a la carte (image A , B et C)

    static QString convertPosToKey(const QPointF& pos);                                          // Permet de convertir un QPointF en QString pour l'utiliser comme clée dans le conteneur QMap
    static QPointF convertKeyToPos(const QString& key);
private :
    std::array<QMap<QString , std::shared_ptr<DTileEntity>> , SIZE_planeEnum> m_map;             // Tableau contenant l'ensemble de la carte
    QSize m_size;                                                                                // La taille de la carte
    QMap<quint16 , QString> m_pictures;                                                          // Les images associées a la carte
    quint16 m_currentIndexPicture;                                                               // Permet de savoir quel est l'onglet séléctionné (A , B  C)
};

#endif // MAPDISPLAY_H
