#ifndef TILEBACKGROUNDPICTURE_H
#define TILEBACKGROUNDPICTURE_H

#include <QGraphicsPixmapItem>

class DTileBackgroundPicture : public QGraphicsPixmapItem
{
public:
    DTileBackgroundPicture(const quint16& sizeX , QGraphicsItem * parent = 0);
    void cutPixmap(const QPixmap & pixmap);// Permet de choisir une nouvelle image et de l'adapter aux dimensions
private :
    quint16 m_sizeX;
};

#endif // TILEBACKGROUNDPICTURE_H
