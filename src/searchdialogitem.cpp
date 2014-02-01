#include "searchdialogitem.h"
//
SearchDialogItem::SearchDialogItem(  ) 
{
	// TODO
}
//
SearchDialogItem::SearchDialogItem(  QString _text,int id)
: text(_text),id(id) 
{
	
}
void SearchDialogItem::setText( QString value) 
{ 
	text = value; 
}
QString SearchDialogItem::getText()
{ 
	return text;
}
int SearchDialogItem::getId()
{
	return id;
}


void SearchDialogItem::setId(int value)
{
	id = value;
}

