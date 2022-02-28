#include "filescripttreeview.h"

DFileScriptTreeView::DFileScriptTreeView()
    : QTreeView() , m_AddAction(QIcon("Pictures\\Icons\\ScriptIcons\\add.png") , QString("Ajouter sous") , m_menu)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    m_menu = new QMenu();

    connect(this , SIGNAL(customContextMenuRequested(QPoint)) , this , SLOT(slotCustomContextMenu()));
    m_menu->addAction(&m_AddAction);
    m_menu->setStyleSheet("color: white;background-color: rgb(39, 40, 34);selection-background-color: rgb(44, 66, 99)");
    m_menu->addAction(QIcon("Pictures\\Icons\\ScriptIcons\\insert.png") , QString("Inserer"));
    m_menu->addAction(QIcon("Pictures\\Icons\\Importer.png") , QString("Importer"));
    m_menu->addAction(QIcon("Pictures\\Icons\\ScriptIcons\\ben.png") , QString("Supprimer"));

    setStyleSheet("color: white;");
}

void DFileScriptTreeView::slotCustomContextMenu()
{
    m_menu->exec(QCursor::pos());
}

QMenu* DFileScriptTreeView::getMenu() const
{
    return m_menu.data();
}

void DFileScriptTreeView::setAddActionEnable(const bool &isEnable)
{
    m_AddAction.setEnabled(isEnable);
}

bool DFileScriptTreeView::isAddActionEnable() const
{
    return m_AddAction.isEnabled();
}
