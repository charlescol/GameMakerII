#ifndef SCREENRESOLUTION_H
#define SCREENRESOLUTION_H

#include <QDesktopWidget>

inline QPoint screenResolution(void)// Permet de récuperer la résolution de l'écran
{
    QDesktopWidget *desktop = new QDesktopWidget;
    unsigned int largeur = desktop->screenGeometry().width();
    unsigned int hauteur = desktop->screenGeometry().height();
    return QPoint(largeur , hauteur);
}

inline QPoint screenResolutionMax(void)// Permet de récuperer la résolution maximum d'un écran
{
    return QPoint(1920 , 1080);
}

inline bool resolutionTest(void)// Permet de tester si la résolution de l'écran est suffisante pour lancer l'application
{
    if(screenResolution().x() >= 1024 && screenResolution().y() >= 768)
        return true;
    else {
        return false;
    }
}

#endif // SCREENRESOLUTION_H
