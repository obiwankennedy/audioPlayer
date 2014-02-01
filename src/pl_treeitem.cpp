#include "pl_treeitem.h"
#include <QDebug>
//
PL_treeitem::PL_treeitem(PlaylistItem* _item)
        : deep(NULL)
{
   // static int countdown= 0;
m_fetchableCount=0;

//    qDebug() <<"# of instance" <<countdown++;
       // maxdeep = 2;

        //intdeep = _vraideep;
        m_fetchableIndex = new QList<PlaylistItem*>;
        //this->deep = _deep;
        //parentItem = parent;
	root = false;
	if(mapheader == NULL)
	{
		mapheader = new QList<headerlistview*>;  
		initHeaders();
	}
	
		if(_item!=NULL)
			itemData = _item;
		else 
			root = true;
        //	findChildrendeep();


}
bool PL_treeitem::canFetchMore ( ) const
{

    return m_fetchableCount;
}
void PL_treeitem::fetchMore (  )
{

int startpoint = m_fetchableIndex->size()-m_fetchableCount;
    headerlistview* key = headerartist;
    if(deep != NULL)
        key = getHeader(deep);

    for(int i = 0; (m_fetchableCount!=0) && (m_fetchableIndex->size()>i); i++)
     {

         this->appendChild(/*new PL_treeitem(*/m_fetchableIndex->at(startpoint+i)/*,headerartist,parent,0)*/,key);
            m_fetchableCount--;
     }

}
void PL_treeitem::reset()
{
	
	this->childItems.clear();
}
void PL_treeitem::setDeep(headerlistview * a)
{
deep = a;
}
void PL_treeitem::initHeaders()
{
  headerYear= new headerlistview;
  headerYear->name = QObject::tr("Year");
  headerYear->x = YEAR;
  
  
  headerGenre= new headerlistview;
  headerGenre->name = QObject::tr("Genre");
  headerGenre->x = GENRE;
  
  headertitle = new headerlistview;
  headertitle->x = TITLE;
  headertitle->name = QObject::tr ( "Title" );
        
  headerartist= new headerlistview;
  headerartist->x = ARTIST;
  headerartist->name = QObject::tr ( "Artist" );
        
        
  headerAlbum= new headerlistview;
 headerAlbum->x = ALBUM;
 headerAlbum->name = QObject::tr( "Album Name" );
 

 mapheader->append(headerartist);
 mapheader->append(headerAlbum);
 mapheader->append(headertitle);
}
PL_treeitem::~PL_treeitem()
 {
     qDeleteAll(childItems);
 }
void PL_treeitem::setParent(PL_treeitem * a)
{
parentItem = a;

}
bool PL_treeitem::hasChildren()
{

if(deep == mapheader->last())
    return false;
else
    return true;



}
headerlistview*  PL_treeitem::getHeader(headerlistview* k)
{
    for(int a = 0 ; a+1 < mapheader->size() ; a++)
    {
        if(mapheader->at(a) == k)
            return mapheader->at(a+1);
    }
            return mapheader->last();
}
 void PL_treeitem::appendChild(PlaylistItem *item,headerlistview* key)
 {

            ItemDecorator* a=NULL;
            a = item->getKey();
            if(a == NULL)
                return;



        if(childItems.contains(a->getMember(key->x).toString()))
        {

            PL_treeitem* t = childItems.value(a->getMember(key->x).toString());
                  if(t)
                {

                    t->addFetchableItem(item);

                }

        }
        else
        {
            
            PL_treeitem* p = new PL_treeitem(item);
            p->setParent(this);
            p->setDeep(key);

                QMap<QString,PL_treeitem*>::Iterator q = childItems.insert(a->getMember(key->x).toString(), p);//replace this line to create new Pl_TreeItem
                if(key != mapheader->last())
                (q.value())->addFetchableItem(item);
        }

     
     
 }
void PL_treeitem::addFetchableItem(PlaylistItem* a)
{
    m_fetchableCount++;
    m_fetchableIndex->append(a);
}
 void PL_treeitem::setFetchableItems(QList<PlaylistItem*>* a)
 {
    m_fetchableCount = a->size();
    m_fetchableIndex = a;
 }
void PL_treeitem::amend(QVariant &value,headerlistview* _deep)
{
	if(_deep == NULL)
		_deep = deep;
			ItemDecorator* b=NULL;
			
			b = itemData->getKey();
			

			b->setValue(_deep->x,value,true);
                        foreach(PL_treeitem* item, childItems)
			{
				
				item->amend(value,_deep);
			}
}
int PL_treeitem::removeChild(QVariant q)
{

   return childItems.remove(q.toString());
}
 PL_treeitem *PL_treeitem::child(int row)
 {

     return childItems.value(childItems.keys().value(row));
 }

 int PL_treeitem::childCount() const
 {
     return childItems.keys().count();
 }
void PL_treeitem::sort(PL_treeitem* a)
{
	PL_treeitem* temp = NULL;
        ItemDecorator* b=NULL;
        b = a->itemData->getKey();
        if(childItems.contains(b->getMember(a->deep->x).toString()))
        {
             temp = childItems.value(b->getMember(a->deep->x).toString());

		foreach(PL_treeitem* av, a->childItems)
                        temp->addFetchableItem(av->itemData);


        }
        else
        {
                        a->setParent(this);
                       //a->setDeep(key);

childItems.insert(b->getMember(a->deep->x).toString(), a);

                    }
	
}
 int PL_treeitem::columnCount() const
 {

     return 1;
 }

 QVariant PL_treeitem::data(int column) const
 {
 	if(root)
 		return QVariant();
	if(column == 0)
	{
		ItemDecorator* a=NULL;
		a = itemData->getKey();
		return a->getMember(deep->x);
    }
    return QVariant();
 }

 PL_treeitem* PL_treeitem::parent()
 {
     return parentItem;
 }

 int PL_treeitem::row() const
 {
     if (parentItem)
         return parentItem->childItems.keys().indexOf(itemData->getKey()->getMember(deep->x).toString());

     return 0;
 }

QList<headerlistview*>* PL_treeitem::mapheader = NULL;
headerlistview* PL_treeitem::childrendeep = NULL;
headerlistview* PL_treeitem::headerYear = NULL;
headerlistview* PL_treeitem::headerGenre = NULL;
headerlistview* PL_treeitem::headerAlbum = NULL;
headerlistview* PL_treeitem::headerartist = NULL;
headerlistview* PL_treeitem::headertitle = NULL;

bool PL_treeitem::present(PlaylistItem* p,PL_treeitem *&wood)
{

	ItemDecorator* a=p->getKey();


        if(a == NULL)
            return false;

                    if(deep == NULL)
                deep=headerartist;
               if( childItems.contains(a->getMember(this->deep->x).toString()))
                {
                   if(wood!=NULL)
                    wood= childItems.value(a->getMember(this->deep->x).toString());
                    return true;
                }
                else
                    return false;


}

PlaylistItem* PL_treeitem::getItemData()
{
	return itemData;
}


void PL_treeitem::setItemData(PlaylistItem* value)
{
	itemData = value;
}

