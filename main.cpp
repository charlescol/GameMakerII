#include <QApplication>
#include <QMessageBox>
#include "EngineClass/Display/mainwindow.h"
#include "EngineClass/Display/screenResolution.h"
#include "EngineClass/Data/databasehandler.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    MainWindow window;
    if(resolutionTest() == false)
    {
        QMessageBox::critical(&window , "Résolution insuffisante", "Résolution minimale requise : 1024 * 768");
        QApplication::quit();
        return 0;
    }
    else return App.exec();
}

// S'adapter a tout résolution
// La suprresion de l'usage de la molette pour la scrollBar lorsque la gomme est activée
// La demande de transparence lors de l'importation d'un tileset
// code eraser pas performant (repetitions)
// restreindre l'importation de tileset uniquement dans le fichier Pictures/Ressource/Tileset (pas encore crée)
// instruction supprimer toutes les tables sql d'un coup
