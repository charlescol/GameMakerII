#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <array>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QActionGroup>
#include "EngineClass/Display/tilescene.h"
#include "EngineClass/Display/renderscene.h"
#include "EngineClass/ScriptEditor/widgetscripteditor.h"

namespace Ui {
class MainWindow;
}

enum TabComposition {
    A , B , C , SIZE_enum};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots :
    void calculator() const;
    void importTilePicture();
    void setGridVisible(bool isVisible);
    void setGridSize();
    void setDrawingMode(QAction * action);
    void setPlaneMode(QAction * action);
    void setCurentIndex(int index);
    void launchScriptEditor();
    void launchGame();
private:
    Ui::MainWindow *ui;
    std::array<QGraphicsView , SIZE_enum> m_tileView;      // Contient l'esemble des vues de tuile
    std::array<DTileScene , SIZE_enum> m_tileScene;        // Contient l'ensemble des scènes de tuile
    DRenderScene m_renderScene;                            // Contient la scène de rendu
    QGraphicsView m_renderView;                            // Contient la vue de rendu

    DWidgetScriptEditor m_scriptEditor;

    QActionGroup m_actionPlaneGroup;                               // Le groupe contenant les actions de changement de plan
    QActionGroup m_actionDrawingGroup;                             // Le groupe contenant les outils de dessins

    std::array<QPushButton , 4> m_backgroundColorButton;         // Contient les boutons gerants la couleur de fond

};

#endif // MAINWINDOW_H
