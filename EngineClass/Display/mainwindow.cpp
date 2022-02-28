#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>

#include "EngineClass/Map/mapdisplay.h"
#include "EngineClass/Display/screenResolution.h" // Permet d'adapter les dimensions à la résolution de l'ordinateur
#include "EngineClass/Data/daomap.h" // Permet d'enrengistrer les informations du jeu dans la base de données

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) , m_renderView(&m_renderScene) , m_actionPlaneGroup(this) , m_actionDrawingGroup(this)
{
    ui->setupUi(this);
    m_renderScene.setSizeMap(QSize(ui->X->value() , ui->Y->value()));


    m_actionPlaneGroup.addAction(ui->FirstPlaneAction);
    m_actionPlaneGroup.addAction(ui->SecondPlaneAction);
    m_actionPlaneGroup.addAction(ui->ThirdPlaneAction);
    ui->ThirdPlaneAction->setChecked(true);

    m_actionDrawingGroup.addAction(ui->PenAction);
    m_actionDrawingGroup.addAction(ui->EraserAction);
    m_actionDrawingGroup.addAction(ui->ColisionAction);
    ui->PenAction->setChecked(true);

    connect(ui->CalculatorAction , SIGNAL(triggered()) , this , SLOT(calculator()));                           // Lancement de la calculette
    connect(ui->ImportAction ,SIGNAL(triggered()) , this , SLOT(importTilePicture()));                         // Importer une image
    connect(ui->VisibleGrid , SIGNAL(toggled(bool)) , this , SLOT(setGridVisible(bool)));                      // Changer l'apparence du quadrillage
    connect(ui->PlayAction , SIGNAL(triggered()) , this , SLOT(launchGame()));                                 // Permet de lancer le jeu
    connect(ui->AjustOpacityAction , SIGNAL(toggled(bool)) , &m_renderScene , SLOT(showOpacity(bool)));        // Permet de changer l'opacité des objets en fonction de leur plan
    connect(ui->ScriptEditAction , SIGNAL(triggered()) , this , SLOT(launchScriptEditor()));                   // Permet de lancer l'éditeur de scripts
    connect(&m_actionDrawingGroup , SIGNAL(triggered(QAction*)) , this , SLOT(setDrawingMode(QAction*)));      // Permet de changer d'outils de dessin
    connect(&m_actionPlaneGroup , SIGNAL(triggered(QAction*)) , this , SLOT(setPlaneMode(QAction*)));          // Permet de changer le mode de vue
    connect(ui->Tab , SIGNAL(currentChanged(int)) , this , SLOT(setCurentIndex(int)));                         // Permet de spécifier quel onglet est ouvert


    connect(ui->X , SIGNAL(valueChanged(int)) , this , SLOT(setGridSize()));                                   // La taille de la scene de rendu
    connect(ui->Y , SIGNAL(valueChanged(int)) , this , SLOT(setGridSize()));

    ui->Tab->setFixedSize(282 , 700);// La taille des widgets de gauche //static_cast<int>(0.96*screenResolution().y() - 337)
    ui->Map->setFixedSize(282 ,131);
    m_renderView.setFixedSize(1300 , ui->Tab->size().height() + ui->Map->size().height()); // La taille de la scene

    QVBoxLayout *mainVerticalLayout = new QVBoxLayout(); // On organise la fenetre avec des layouts
    mainVerticalLayout->addWidget(ui->Tab);
    mainVerticalLayout->addWidget(ui->Map);
    ui->MainHorizontalLayout->addLayout(mainVerticalLayout);
    ui->MainHorizontalLayout->addWidget(&m_renderView);


    for(quint16 i(0); i < SIZE_enum; ++i){
        m_tileView[i].setScene(&m_tileScene[i]);// On associe les vues avec les scenes
        m_tileView[i].setFixedSize(ui->Tab->size().width() - 6 , ui->Tab->size().height() - 25);// on rendimensionne les vues
        connect(&m_tileScene[i] , SIGNAL(mouseReleaseSignal(QSize)) , &m_renderScene , SLOT(setSelectionSize(QSize)));
        connect(&m_tileScene[i] , SIGNAL(mouseReleaseSignal(QPixmap , QPoint)) , &m_renderScene , SLOT(addItemToMap(QPixmap , QPoint)));
        connect(&m_tileScene[i] , SIGNAL(newPictureSignal(QString)) , &m_renderScene , SLOT(associatePictureWithCurentMap(QString)));
    }

    m_tileView[A].setParent(ui->A);         // On associe les vues avec les scenes
    m_tileView[B].setParent(ui->B);
    m_tileView[C].setParent(ui->C);
    m_tileScene[A].importTileset("Pictures/Tilesets/2D/Outside_B.png");
    //DSqlQueryRegisterMap::addPicturePathToDatabase(ui->Tab->currentIndex() , "D:/LOGICIEL/Qt/Tools/QtCreator/bin/GameMakerII/GameMakerII/Pictures/Tilesets/2D/PlateformerTileset.png");

    for(quint16 i(0); i < m_backgroundColorButton.size(); ++i){   // On définie les boutons qui permettent de changer la couleur de la scene de rendu
        m_backgroundColorButton[i].setGeometry(310 + 18*i , 60 , 17 , 17);
        m_backgroundColorButton[i].setParent(this);
    }
    m_backgroundColorButton[0].setStyleSheet("QPushButton { background-color: yellow; }");
    m_backgroundColorButton[1].setStyleSheet("QPushButton { background-color: black; }");
    m_backgroundColorButton[2].setStyleSheet("QPushButton { background-color: darkGreen; }");
    m_backgroundColorButton[3].setStyleSheet("QPushButton { background-color: gray; }");
    connect(&m_backgroundColorButton[0] , &QPushButton::clicked , [&](){m_renderScene.setBackgroundBrush(Qt::yellow);});
    connect(&m_backgroundColorButton[1] , &QPushButton::clicked , [&](){m_renderScene.setBackgroundBrush(Qt::black);});
    connect(&m_backgroundColorButton[2] , &QPushButton::clicked , [&](){m_renderScene.setBackgroundBrush(Qt::darkGreen);});
    connect(&m_backgroundColorButton[3] , &QPushButton::clicked , [&](){m_renderScene.setBackgroundBrush(Qt::gray);});



    showMaximized();// On affiche la fenetre pricipale
}

void MainWindow::calculator() const // On ouvre la calculatrice
{
    QProcess::startDetached("C:\\Windows\\System32\\calc.exe");
}

void MainWindow::setGridVisible(bool isVisible)// On active ou désactive le quadrillage sur la carte de rendu
{
    m_renderScene.setGridVisible(isVisible);
}

void MainWindow::setGridSize()// On change la taille de la carte de rendu
{
    m_renderScene.setGridSize(ui->X->value() , ui->Y->value());
    m_renderScene.setSizeMap(QSize(ui->X->value() , ui->Y->value()));
}

void MainWindow::setDrawingMode(QAction *action)
{
    Mode drawingMode;
    if(action == ui->PenAction)
        drawingMode = Brush;
    else if(action == ui->EraserAction)
        drawingMode = Eraser;
    else
        drawingMode = Colision;

    if(action == ui->ColisionAction) {
        ui->AjustOpacityAction->setChecked(false);
        ui->AjustOpacityAction->setEnabled(false);
        ui->FirstPlaneAction->setEnabled(false);
        ui->SecondPlaneAction->setEnabled(false);
        ui->ThirdPlaneAction->setEnabled(false);
    }
    else {
        ui->AjustOpacityAction->setEnabled(true);
        ui->FirstPlaneAction->setEnabled(true);
        ui->SecondPlaneAction->setEnabled(true);
        ui->ThirdPlaneAction->setEnabled(true);
    }

    m_renderScene.setDrawingMode(drawingMode);
}

void MainWindow::setPlaneMode(QAction *action)
{
    Plane planeMode;
    if(action == ui->FirstPlaneAction) planeMode = firstPlane;
    else if(action == ui->SecondPlaneAction) planeMode = secondPlane;
    else  if(action == ui->ThirdPlaneAction) planeMode = thirdPlane;


    m_renderScene.setPlaneMode(planeMode);

}

void MainWindow::setCurentIndex(int index)
{
    m_renderScene.setCurrentPictureIndex(index);
    m_tileScene[ui->Tab->currentIndex()].sendPixmapSelected();
}

void MainWindow::importTilePicture()// On importe une image
{
    if(!m_renderScene.getMap()[firstPlane].isEmpty() || !m_renderScene.getMap()[secondPlane].isEmpty() || !m_renderScene.getMap()[thirdPlane].isEmpty())
    {
        qreal answer = QMessageBox::warning(this , "Importation de nouveaux contenus", "Attention , si vous effectuez cette action le contenu de votre carte sera réinitialisé. Etes-vous sûre de vouloir continuer ?", QMessageBox::Yes | QMessageBox::No);
        if(answer == QMessageBox::No) return;
    }
    m_renderScene.clearMap();
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    m_tileScene[ui->Tab->currentIndex()].importTileset(fileName);

    //DSqlQueryRegisterMap::addPicturePathToDatabase(ui->Tab->currentIndex() , fileName);
}

void MainWindow::launchScriptEditor()
{
    m_scriptEditor.exec();
}

void MainWindow::launchGame()
{
    DDAOMap map(QSize(ui->X->value() * DGrid::getTileSize().x(), ui->Y->value()* DGrid::getTileSize().y()) , "map1"); // On envoie les caractéristiques de la carte dans la base de données
    for(quint16 i(0); i < SIZE_planeEnum; ++i) {
        for(auto it : m_renderScene.getMap()[i].keys()) {
            map.addEntityToTable(m_renderScene.getMap()[i][it].get()); // On enregistre la carte tuile par tuile dans la base de données
        }
    }
}

MainWindow::~MainWindow()
{
    m_renderScene.clearMap();
    delete ui;
}
