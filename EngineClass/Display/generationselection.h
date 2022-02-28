#ifndef GENERATIONSELECTION_H
#define GENERATIONSELECTION_H

#include "EngineClass/Display/movableselection.h"

class DGenerationSelection : public DMovableSelection
{
public:
    DGenerationSelection(QGraphicsItem * parent = 0);
    void generateSelection(const QPointF mousePosition);  // Permet de génerer une selection
    void resetSelection();                                // Permet de réinitialiser la selection
    QPointF getPosTopLeftCorner();                        // Permet d'optenir la position du coin en haut à gauche de la selection
private :
    qint16 m_SubstractionPosTopLeftCornerX;  // valeur à soustraire à la positionX de la selection pour obtenir la positionX du coin haut gauche de la selection
    qint16 m_SubstractionPosTopLeftCornerY;  // valeur à soustraire à la positionY de la selection pour obtenir la positionY du coin haut gauche de la selection
};

#endif // GENERATIONSELECTION_H
