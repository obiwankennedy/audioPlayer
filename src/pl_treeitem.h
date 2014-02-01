#ifndef PL_TREEITEM_H
#define PL_TREEITEM_H
//
 #include <QList>
 #include <QMap>
 #include <QVariant>

#include "playlist.h"
//
class PL_treeitem  
{
	void findChildrendeep();
 	void initHeaders();
public:
	void setItemData( PlaylistItem* value);
	PlaylistItem* getItemData();
        PL_treeitem(PlaylistItem* item);
    
     ~PL_treeitem();

     void appendChild(PlaylistItem/*PL_treeitem*/ *child,headerlistview* q);

     PL_treeitem *child(int row);
     int childCount() const;
     int columnCount() const;
     QVariant data(int column) const;
     int row() const;
     PL_treeitem *parent();
     void addData(PlaylistItem* a);
     bool present(PlaylistItem* p,PL_treeitem *&wood);
     void reset();
     void amend(QVariant &value,headerlistview* _deep);
     void sort(PL_treeitem * a);
     void setParent(PL_treeitem * a);

     bool hasChildren();
     bool canFetchMore ( ) const ;
     void addFetchableItem(PlaylistItem* a);
     void setFetchableItems(QList<PlaylistItem*>* a);
     void fetchMore (  );
     void setDeep(headerlistview* p);
     int removeChild(QVariant q);
 private:
     headerlistview* getHeader(headerlistview* k);
     QMap<QString,PL_treeitem*> childItems;
     PlaylistItem* itemData;
     bool root;
     PL_treeitem *parentItem;
     static QList<headerlistview*>* mapheader;
	
	 
    bool lastdeep;
    int intdeep;
    int intCdeep;
    int maxdeep;
    headerlistview* deep;
    static headerlistview* childrendeep;
    static headerlistview *headerYear;
    static headerlistview *headerGenre;
    static  headerlistview *headerAlbum;
    static headerlistview* headerartist;
    static headerlistview* headertitle;
    Playlist* myPlaylist;
    int m_fetchableCount;
    QList<PlaylistItem*>* m_fetchableIndex;
	
};
#endif
