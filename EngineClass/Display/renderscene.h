#ifndef RENDERSCENE_H
#define RENDERSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "EngineClass/Display/grid.h"
#include "EngineClass/Display/movableselection.h"
#include "EngineClass/Map/mapdisplay.h"
#include "EngineClass/Display/eraser.h"
#include "EngineClass/Map/mapcolisions.h"

enum Mode {Brush , Eraser , Colision};// Enumeration des diférents plans

class DRenderScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DRenderScene(QObject *parent = 0);
    void setGridVisible(const bool isVisible);                                               // Permet de choisir si le quadrillage est visible ou non
    void setGridSize(const qreal sizeX , const qreal sizeY);                                 // Permet de changer la taille du quadrillage
    void setDrawingMode(const Mode &mode);                                                   // Permet de changer le mode
    void setPlaneMode(const Plane &plane);                                                   // Permet de changer le plan

    void ajustItemsOpacity();                                                                // Permet d'ajuster l'opacité des items de la carte

    std::array<QMap<QString, std::shared_ptr<DTileEntity> >, SIZE_planeEnum>& getMap();      // Permet de récuperer la carte des tuiles
    void clearMap();                                                                         // Permet de supprimer la carte
    void setSizeMap(const QSize& sizeMap);                                                   // Permet de préciser la taille de la carte
    void setCurrentPictureIndex(const quint16& index);                                     // Permet de spécifier l'onglet ouvert (A , B ou C)
private :
    void drawTile(const QPoint& grid_mousePosition);          // Permet de dessiner les tiles
    void deleteTile(const QPoint& grid_mousePosition);        // Permet d'effacer les tiles
    void drawColisions(const QPoint& grid_mousePosition);     // Permet de dessiner les collisions

    DGrid m_grid;                    // Le quadrillage
    DMovableSelection m_selection;   // La selection
    DEraser m_eraser;                // La gomme
    QPixmap m_pixmapSelected;        // L'image selectionnée
    QPoint m_cutingPosPixmapSelected;// La position de découpage de l'image sélectionnée

    bool m_longMouseClick;         // Permet de savoir si le bouton de la souris est maintenu appuyé
    bool m_opacityIsActivated;     // Permet de savoir si l'opacité est activée
    Mode m_drawingMode;            // Permet de savoir quelle option est activée
    Plane m_planeMode;             // Permet de savoir quel plan est activé
    QPoint m_posWhenClick;         // Retiens la position de la souris au moment ou l'utilisateur clique

    DMapDisplay m_map;             // La carte à afficher
    DMapColisions m_colisionsMap;  // La carte des collisions

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    // Permet de detecter la position de la souris lorsqu'on la déplace dans la scène
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);   // Permet de detecter la position de la souris lorsqu'on effectue un clique gauche
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // Permet de detecter la position de la souris lorsqu'on relache le bouton du clique gauche
    virtual void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);  // Permet de detecter quand la molette de la souris est tournée

public slots :
    void setSelectionSize(const QSize newSize);                           // Permet de changer la taille de la selection
    void addItemToMap(const QPixmap& pixmap , const QPoint& cutingPos);   // Permet d'ajouter des items à la carte
    void showOpacity(const bool& opacityIsActivated);                     // Permet d'activer / de désactiver l'affichage de l'opacité
    void associatePictureWithCurentMap(const QString& pictureName);       // Permet de stocker le nom de chaque nouvelle image utiliser dans l'editeur
};
// voire void QGraphicsItem :: setAcceptedMouseButtons (Qt :: MouseButtons boutons)

#endif // RENDERSCENE_H
