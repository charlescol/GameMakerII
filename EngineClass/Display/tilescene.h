#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "EngineClass/Display/grid.h"
#include "EngineClass/Display/tilebackgroundpicture.h"
#include "EngineClass/Display/generationselection.h"

class DTileScene: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DTileScene(QObject *parent = 0);
    void importTileset(const QString &fileName);      // Permet d'importer une image
    void sendPixmapSelected();                        // Permet d'envoyer l'image sélectionnée à la scene de rendu
private :
    DGrid m_grid;                                     // Le quadrillage
    QPalette m_palette;                               // Le motif de fond
    DTileBackgroundPicture m_importPicture;           // L'image à importer
    DGenerationSelection m_selection;                 // La selection

    bool m_longMouseClick;                            // Permet de savoir si le bouton de la souris est maintenu appuyé
    quint16 m_initialHeightPicture;                   // La hauteur de l'image importée
    
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);   // Permet de detecter la position de la souris lorsqu'on effectue un clique gauche
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // Permet de detecter la position de la souris lorsqu'on relache le bouton du clique gauche
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    // Permet de detecter la position de la souris lorsqu'on la déplace dans la scène

signals :
    void mouseReleaseSignal(const QSize newSize);                            // Signal déclenché lorsque le bouton gauche de la souris est relaché (newSize = nombre de carreaux de la selection)
    void mouseReleaseSignal(const QPixmap& pixmap , const QPoint& cutingPos);// Signal déclenché lorsque le bouton gauche de la souris est relaché (pixmap  = la partie de l'image selectionnée)
    void newPictureSignal(const QString& pictureName);                       // Signal déclenché lorsque l'on importe une nouvelle image (cela nous permet d'identifier son nom pour l'afficher dans le jeu)
    
};

#endif // TILESCENE_H
