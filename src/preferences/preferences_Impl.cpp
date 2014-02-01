#include "preferences_Impl.h"

#include <QFileDialog>
//
Preferences_Impl_Dialog::Preferences_Impl_Dialog(PlayListViewer* tabs , QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent, f),m_tabs(tabs)
{
	
	setupUi(this);

	findCodecs();
	setCodecList(codecs);
	//nb_recentfiles
	setWindowTitle(tr("%1[*] - %2").arg("Preferences").arg(tr("PlayListGenerator")));
	mypreference = Preference_data::getInstance();
	uridisplayer->setText(mypreference->getUri_default());
	uri_adp->setText(mypreference->getUri_documentation());
	nb_recentfiles->setValue(mypreference->getNb_recentfiles());
	readmode->setCurrentIndex(mypreference->getSelectedReadMode());

	disableAll->setDisabled(mypreference->getDisableAudioPlayer());
	disableAll->setCheckable(!mypreference->getDisableAudioPlayer());
	info_disable_phonon->setVisible(mypreference->getDisableAudioPlayer());
	
        nb_history->setValue(mypreference->getHistorySong());
	OpenLast_cb->setChecked(mypreference->getLoadlastfile());
	
	connect(Browser,SIGNAL(clicked()),this,SLOT(defaultfolderchooser()));
	connect(doc_browser,SIGNAL(clicked()),this,SLOT(doc_browserchooser()));
	
	connect(Apply_cancel,SIGNAL(clicked(QAbstractButton* )),this,SLOT(apply(QAbstractButton *)));
	
	connect(this, SIGNAL(Modify()),this,SLOT(Modified()));
	connect(Apply_cancel, SIGNAL(rejected()), this, SLOT(reject()));
	connect(charsetcombo, SIGNAL(currentIndexChanged ( int )),this,SLOT(Modified()));
	connect(readmode, SIGNAL(currentIndexChanged ( int )),this,SLOT(Modified()));
	connect(nb_recentfiles,SIGNAL(valueChanged ( int  )),this,SLOT(Modified()));
	connect(OpenLast_cb,SIGNAL(stateChanged ( int)),this,SLOT(Modified()));
	connect(showDockWidget,SIGNAL(stateChanged ( int)),this,SLOT(Modified()));
	connect(disableAll,SIGNAL(stateChanged ( int)),this,SLOT(Modified()));
	connect(ShowPlayeratstart,SIGNAL(stateChanged ( int)),this,SLOT(Modified()));
	
	filterscb <<  cb_mp3 <<   cb_ogg<<    cb_mid<<    cb_mpc<< cb_wav<< cb_flac<< cb_ape<< cb_alf<< cb_aac<< cb_mp4<<cb_m4a<<   cb_wma<<cb_vqf<<    cb_vqe<<cb_vql<<   cb_au;
	foreach(QCheckBox* p, filterscb)
 		{
 			p->setChecked(false);
 			foreach(QString a,mypreference->getFilters())
 			{
 				if(a==p->text())
 				{
 					p->setChecked(true);
				}
			}
 			
		}
        for(int i = 0 ; i< m_tabs->getListViewer()->size() ; i++)
        {
            ListViewers->addItem(m_tabs->getListViewer()->at(i)->tabTitle());
        }
        connect(ListViewers,SIGNAL(currentRowChanged(int)),this,SLOT(onCurrentViewerChanged(int)));
        connect(behaviourList,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentBehaviourChanged(int)));
}
//
void Preferences_Impl_Dialog::defaultfolderchooser()
{
   QString* fileName = new QString;
   
  
	
	
  *fileName= QFileDialog::getExistingDirectory(this,tr("Play List Generator"),mypreference->getUri_default());
  if (!fileName->isEmpty())
  {
	
	uridisplayer->setText(*fileName);
	emit Modify();
  }
 	
}
void Preferences_Impl_Dialog::onCurrentBehaviourChanged(int index)
{
    m_tabs->getListViewer()->at(ListViewers->currentIndex().row())->setBehaviour(static_cast<ViewerBehaviour>(index));
}
void Preferences_Impl_Dialog::onCurrentViewerChanged(int  index)
{
    behaviourList->setCurrentIndex(m_tabs->getListViewer()->at(index)->Behaviour());
}
void Preferences_Impl_Dialog::findCodecs()
{
     QMap<QString, QTextCodec *> codecMap;
     QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

     foreach (int mib, QTextCodec::availableMibs()) {
         QTextCodec *codec = QTextCodec::codecForMib(mib);

         QString sortKey = codec->name().toUpper();
         int rank;

         if (sortKey.startsWith("UTF-8")) {
             rank = 1;
         } else if (sortKey.startsWith("UTF-16")) {
             rank = 2;
         } else if (iso8859RegExp.exactMatch(sortKey)) {
             if (iso8859RegExp.cap(1).size() == 1)
                 rank = 3;
             else
                 rank = 4;
         } else {
             rank = 5;
         }
         sortKey.prepend(QChar('0' + rank));

         codecMap.insert(sortKey, codec);
     }
     codecs = codecMap.values();
}
 
void Preferences_Impl_Dialog::setCodecList(const QList<QTextCodec *> &list)
{
     charsetcombo->clear();
     foreach (QTextCodec *codec, list)
         charsetcombo->addItem(codec->name(), codec->mibEnum());
}
 
void Preferences_Impl_Dialog::apply( QAbstractButton * button )
{
 	if( Apply_cancel->buttonRole ( button )==QDialogButtonBox::ApplyRole) 
 	{
 		mypreference->setNb_recentfiles(nb_recentfiles->value());
 		mypreference->setUri_default(uridisplayer->text());
 		mypreference->setCodecs(codecs[charsetcombo->currentIndex()]);
 		mypreference->setUri_documentation(uri_adp->text());
 		mypreference->setLoadlastfile(OpenLast_cb->isChecked());
 		mypreference->setDisableAudioPlayer(disableAll->isChecked());
 		mypreference->setSelectedReadMode(readmode->currentIndex());
 		mypreference->setShowPlayerOnStartReading(showDockWidget->isChecked());
 		mypreference->setShowPlayerOnStarting(ShowPlayeratstart->isChecked());
                mypreference->setHistorySong(nb_history->value());

 		QStringList a;
 		foreach(QCheckBox* p, filterscb)
 		{
 			if(p->isChecked())
 			{
 				a << p->text();
			}
 			
		}
		mypreference->setFilters(a);
	}
 		
 	
 	this->setWindowModified ( false );
 }
void Preferences_Impl_Dialog::Modified()
{
	this->setWindowModified ( true );
}
void Preferences_Impl_Dialog::doc_browserchooser()
{
	 QString* fileName = new QString;
   
  
	
	
         
  *fileName= QFileDialog::getOpenFileName(this,tr("Play List Generator"),mypreference->getUri_documentation(),tr(
            "Documentation Profile (*.adp)"));
  if (!fileName->isEmpty())
  {
	
	uri_adp->setText(*fileName);
	emit Modify();
  }
	
}
