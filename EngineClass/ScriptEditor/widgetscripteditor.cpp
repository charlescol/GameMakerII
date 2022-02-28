#include "widgetscripteditor.h"

#include <QHeaderView>
#include <QDirIterator>
#include <QPlainTextDocumentLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

DWidgetScriptEditor::DWidgetScriptEditor(QWidget *parent) :
    QDialog(parent) , m_documentlayout(&m_document) , m_filesPath("PythonCodeFile\\scripts") , m_buttonsWidget(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, Qt::Horizontal)
{
    setStyleSheet("color: gray;background-color: rgb(39, 40, 34)");
    setFixedSize(1100 , 800);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    m_document.setDocumentLayout(&m_documentlayout);
    m_codeEditor.setDocument(&m_document);


    QDirIterator fileIt(m_filesPath, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QStringList fileList;
    QStandardItem* item = new QStandardItem;
    do
    {
        fileList << fileIt.next();

        QFile code_file(fileIt.filePath());

        if(code_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString textDocument = QString(code_file.readAll());
            QFileInfo fileInfo(code_file.fileName());
            QString fileNameWithoutPath =  fileInfo.fileName().remove(fileInfo.fileName().size() - 3 , fileInfo.fileName().size() - 1);
            QFileInfo folder(fileInfo.absolutePath());// Permet de récuperer le nom du dossier dans lequel se situe le fichier python
            if(fileNameWithoutPath == "main") {
                item = new QStandardItem(fileNameWithoutPath);
                item->setEditable(false);
                m_modele.appendRow(item);
                m_scriptdocument.insert(fileNameWithoutPath , textDocument);
            }
            else {
                if(item->text() != folder.fileName())// Permet de trier en fonction des fichiers
                {
                    QString folderName = folder.fileName();
                    item = new QStandardItem(folderName);
                    item->setEditable(false);// Permet d'empecher de renommer les dossiers
                    m_modele.appendRow(item);
                }
                m_scriptdocument.insert(fileNameWithoutPath , textDocument);
                QStandardItem *withinItem = new QStandardItem(fileNameWithoutPath);
                withinItem->setEditable(false);// Permet d'empecher de renommer les fichier
                item->appendRow(withinItem);
            }
            code_file.close();
        }
    } while (fileIt.hasNext());

    highlighter = new DScriptHighlighter(&m_document); //Nous passons à  notre classe un QTextDocument plutôt que le QTextEdit

    m_view.setModel(&m_modele);
    m_view.header()->hide();
    m_horizontal_layout.addWidget(&m_view);
    m_codeEditor.setWindowTitle(QObject::tr("Code Editor"));
    m_horizontal_layout.addWidget(&m_codeEditor);

    m_vertical_layout.addLayout(&m_horizontal_layout);
    m_vertical_layout.addWidget(&m_buttonsWidget);
    m_vertical_layout.setAlignment(&m_buttonsWidget , Qt::AlignCenter);

    setLayout(&m_vertical_layout);

    connect(&m_view , SIGNAL(pressed(QModelIndex)) , this , SLOT(clickedOnIndex(QModelIndex)));
    connect(&m_codeEditor , SIGNAL(textChanged()) , this , SLOT(textChanged()));
    connect(m_view.getMenu() , SIGNAL(triggered(QAction*)) , this , SLOT(menuTriggered(QAction*)));

    connect(&m_buttonsWidget , SIGNAL(clicked(QAbstractButton*)) , this , SLOT(buttonPushing(QAbstractButton*)));
}

void DWidgetScriptEditor::clickedOnIndex(const QModelIndex &index)
{
    m_rowSelected.isValid = index.parent().isValid();
    m_rowSelected.rowChildSelected = index.row();
    m_rowSelected.rowParentSelected = index.parent().row();// on identifie la position de l'item séléctionné

    m_rowSelected.scriptName = index.data(Qt::DisplayRole).toString();// on recupere le nom du fichier

    if(m_rowSelected.scriptName == "main")
        m_view.getMenu()->setEnabled(false);// on grise le menu si le main est séléctionné
    else {
        m_view.getMenu()->setEnabled(true);
        m_view.setAddActionEnable(!m_rowSelected.isValid);// on grise ou dégrise le bouton "Ajouter sous" en fonction du fichier choisit (document / fichier)
    }

    m_document.setPlainText(m_scriptdocument[m_rowSelected.scriptName]);
}

void DWidgetScriptEditor::textChanged()
{
    m_scriptdocument[m_rowSelected.scriptName] = m_codeEditor.toPlainText();
}

void DWidgetScriptEditor::saveFiles()
{
    QDirIterator fileIt(m_filesPath , QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QStringList *fileList = new QStringList();

    do {
        *fileList << fileIt.next();
        QFile code_file(fileIt.filePath());
        if(code_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&code_file);
            QFileInfo fileInfo(code_file.fileName());
            QString fileNameWithoutPath =  fileInfo.fileName().remove(fileInfo.fileName().size() - 3 , fileInfo.fileName().size() - 1);

            out << m_scriptdocument[fileNameWithoutPath];
            code_file.close();
        }
    } while (fileIt.hasNext());
}

void DWidgetScriptEditor::startGame()
{
    saveFiles();
    m_process.start(m_filesPath, QStringList() << (m_filesPath + "\\main.py")); // Lancement du processus python
}

void DWidgetScriptEditor::menuTriggered(QAction* action)
{
    if(action->text() == "Supprimer")
    {
        qreal answer = QMessageBox::warning(this , "Suppression", "Etes vous sure de vouloir supprimer cet élement ? ", QMessageBox::Yes | QMessageBox::No);
        if(answer == QMessageBox::No)
            return;
        else if(m_rowSelected.isValid){// Si l'élement séléctionné n'est pas un dossier
            m_modele.item(m_rowSelected.rowParentSelected)->removeRow(m_rowSelected.rowChildSelected);// On supprime l'élement de l'arbre
            m_scriptdocument.erase(m_scriptdocument.find(m_rowSelected.scriptName));// On supprime l'élement du conteneur
        }
        else if(m_modele.findItems(m_rowSelected.scriptName).size() != 0) {// Si l'élement est un dossier
            if(m_modele.item(m_rowSelected.rowChildSelected)->takeColumn(0).size() != 0) {// On supprime tous les élements qu'il contient
                for(quint16 i(0); i < m_modele.item(m_rowSelected.rowChildSelected)->takeColumn(0).size(); ++i) {
                    m_modele.item(m_rowSelected.rowChildSelected)->removeRow(i);
                    m_scriptdocument.erase(m_scriptdocument.find(m_modele.item(m_rowSelected.rowChildSelected)->takeChild(i)->text()));
                }
            }
            m_modele.removeRow(m_modele.item(m_rowSelected.rowChildSelected)->row());
            m_scriptdocument.erase(m_scriptdocument.find(m_rowSelected.scriptName));
        }
    }
    else if(action->text() == "Inserer")
    {
        QString fileName = renameFile();
        if(fileName != "") // Si l'utilisateur a cliqué sur "ok"
            insertFile(fileName);// On insert le fichier
        else return;// Sinon on quitte la fonction
    }
    else if(action->text() == "Importer")
    {
        QString fileName;
        do {
            QFile scriptFile(QString(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichier Python (*.py)")));// Permet d'importer le fichier
            QString fileContent = scriptFile.readAll();
            QFileInfo fileInfo(scriptFile);
            fileName = fileInfo.fileName().remove(fileInfo.fileName().size() - 3, fileInfo.fileName().size() - 1);// Le nom du fichier importé

            if(!scriptFile.open(QIODevice::ReadOnly))
                return;
            else if(!m_scriptdocument.contains(fileName)) {
                insertFile(fileName , fileContent);
                return;
            }
            else
                QMessageBox::critical(this , "Nom du fichier", "Nom déjà utilisé ou vide , veillez renommer le fichier");

        }while(m_scriptdocument.contains(fileName));
    }
    else if(action->text() == "Ajouter sous")
    {
        QString fileName = renameFile();

        if(fileName != "") {// Si l'utilisateur a cliqué sur "ok"
            QStandardItem* item = new QStandardItem();

            m_modele.item(m_rowSelected.rowChildSelected)->insertRow(0 , item);

            item->setText(fileName);
            m_scriptdocument.insert(fileName , "");
            item->setEditable(false);
        }
        else return;// Sinon on quitte la fonction
    }
}

void DWidgetScriptEditor::insertFile(QString &fileName, QString code)
{
    QStandardItem* item = new QStandardItem();
    if(m_rowSelected.isValid) // Si l'élement séléctionné n'est pas un dossier
        m_modele.item(m_rowSelected.rowParentSelected)->insertRow(m_rowSelected.rowChildSelected , item);
    else // Si l'élement séléctionné est un dossier
        m_modele.insertRow(m_modele.item(m_rowSelected.rowChildSelected)->row() , item);

    item->setText(fileName);
    m_scriptdocument.insert(fileName , code);
    item->setEditable(false);
}

QString DWidgetScriptEditor::renameFile()
{
    bool answer;
    QString fileName = QInputDialog::getText(this, "Nom du fichier", "Entrez le nom du fichier à insérer" , QLineEdit::Normal, QString(), &answer);

    while(m_scriptdocument.contains(fileName) && answer) {
        QMessageBox::critical(this , "Nom du fichier", "Nom déjà utilisé ou vide , veillez renommer le fichier");
        fileName = QInputDialog::getText(this, "Nom du fichier", "Entrez le nom du fichier à insérer" , QLineEdit::Normal, QString(), &answer);
    }
    if(!answer)
        fileName = "";

    return fileName;
}

void DWidgetScriptEditor::buttonPushing(QAbstractButton * button)
{
    if(m_buttonsWidget.buttonRole(button) == QDialogButtonBox::AcceptRole) { // Si l'utilisateur clique sur Ok
        saveFiles();
        close();
    }
    else if(m_buttonsWidget.buttonRole(button) == QDialogButtonBox::ApplyRole) // Si l'utilisateur clique sur Apply
        saveFiles();
    else if(m_buttonsWidget.buttonRole(button) == QDialogButtonBox::RejectRole)// Si l'utilisateur clique sur Cancel
        close();
}

