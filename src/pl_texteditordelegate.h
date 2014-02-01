#ifndef PL_TEXTEDITORDELEGATE_H
#define PL_TEXTEDITORDELEGATE_H
//
#include <QItemDelegate>
//
class pl_texteditordelegate : public QItemDelegate
{
Q_OBJECT
public:
	pl_texteditordelegate(QObject *parent = 0);
	

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;

};
#endif
