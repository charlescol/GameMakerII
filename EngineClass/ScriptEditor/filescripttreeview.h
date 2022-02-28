#ifndef FILESCRIPTTREEVIEW_H
#define FILESCRIPTTREEVIEW_H

#include <QTreeView>
#include <QMenu>
#include <QPointer>
#include <QAction>

class DFileScriptTreeView : public QTreeView
{
    Q_OBJECT
public:
    DFileScriptTreeView();
    QMenu* getMenu() const;
    void setAddActionEnable(const bool& isEnable);
    bool isAddActionEnable() const;
public slots :
    void slotCustomContextMenu();
private :
    QPointer<QMenu> m_menu;// Le menu
    QAction m_AddAction;// L'action "inserer sous" du menu (on a besoin de cette instance pour la griser)
};

#endif // FILESCRIPTTREEVIEW_H
