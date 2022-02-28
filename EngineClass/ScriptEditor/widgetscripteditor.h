#ifndef WIDGETSCRIPTEDITOR_H
#define WIDGETSCRIPTEDITOR_H

#include <QDialogButtonBox>
#include <QDialog>
#include <QProcess>
#include <QTextDocument>
#include <QStandardItemModel>
#include <QLayout>
#include <QInputDialog>

#include "EngineClass/ScriptEditor/codeeditor.h"
#include "EngineClass/ScriptEditor/filescripttreeview.h"
#include "EngineClass/ScriptEditor/scripthighlighter.h"

class DWidgetScriptEditor : public QDialog
{
    Q_OBJECT
public:
    explicit DWidgetScriptEditor(QWidget *parent = 0);

private slots:
    void clickedOnIndex(const QModelIndex& index); // Detecte chaque clique sur les élements de l'arbre
    void startGame();                              // Permet d'executer les scripts
    void textChanged();                            // Quand le texte d'un fichier à changer on enrengistre le nouveau texte à la place de l'ancien
    void menuTriggered(QAction* action);           // Quand une action du menu est utilisée
    void buttonPushing(QAbstractButton * button);  // Permet de fermer la fenetre

private :
    void insertFile(QString& fileName , QString code = ""); // Permet d'inserer un fichier
    void saveFiles();                                       // Permet de sauvegarder les fichiers
    QString renameFile();                                   // Permet de renommer les fichiers

     const QString m_filesPath;

    QProcess m_process;                            // Pour lancer l'interpreteur Python
    QMap<QString , QString> m_scriptdocument;      // Contient les textes des élements de l'arbre ainsi que les textes des documents pythons
    DCodeEditor m_codeEditor;                      // L'Editeur de code

    QStandardItemModel m_modele;                   // Le modele utilisé
    DFileScriptTreeView m_view;

    QTextDocument m_document;                      // Le texte de l'éditeur de code

    QDialogButtonBox m_buttonsWidget;              // Widget qui contient les boutons du bas

    DScriptHighlighter *highlighter;               // Permet d'utiliser la coloration syntaxique

    QVBoxLayout m_vertical_layout;
    QHBoxLayout m_horizontal_layout;

    struct RowSelected                             // Contient toutes les informations nécéssaires sur le séléctionné fichier de l'arbre
    {
        quint16 rowChildSelected;
        quint16 rowParentSelected;
        bool isValid;
        QString scriptName;                        // Le nom de l'élement sélectionné
    };
    struct RowSelected m_rowSelected;              // L'instance de la structure ci-dessus

    QPlainTextDocumentLayout m_documentlayout;     // Le layout qui contient l'editeur de code
};


#endif // WIDGETSCRIPTEDITOR_H
