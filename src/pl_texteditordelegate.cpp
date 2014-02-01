#include "pl_texteditordelegate.h"
#include "pl_treeitem.h"
#include <QLineEdit>
//
pl_texteditordelegate::pl_texteditordelegate( QObject *parent) 
	: QItemDelegate(parent)
{
	// TODO
}
//
QWidget* pl_texteditordelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex &/* index */) const
 {
     QLineEdit *editor = new QLineEdit(parent);
     
     

     return editor;
 }
  void pl_texteditordelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     //QString value = index.model()->data(index, Qt::EditRole).toString();
		PL_treeitem *item = static_cast<PL_treeitem*>(index.internalPointer());
		
     QLineEdit *texteditor = static_cast<QLineEdit*>(editor);
     texteditor->setText(item->data(0).toString());
 }

 void pl_texteditordelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
     
     QString value = spinBox->text();

     model->setData(index, value, Qt::EditRole);
 }
 void pl_texteditordelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }
