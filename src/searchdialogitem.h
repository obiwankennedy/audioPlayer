#ifndef SEARCHDIALOGITEM_H
#define SEARCHDIALOGITEM_H
//
#include <QString>
//
class SearchDialogItem  
{
	QString text;
	int id;
public:
	SearchDialogItem(QString _text,int id);
	SearchDialogItem();
	void setId( int value);
	int getId();
	void setText( QString value);
	QString getText();
	
	
};
#endif
