#include "lyricsviewerdock.h"

LyricsViewerDock::LyricsViewerDock()
{
    setupUi(this);

    connect(onlineButton,SIGNAL(clicked()),this,SIGNAL(clickOnOnline()));

    connect(startEditionButton,SIGNAL(clicked()),this,SIGNAL(clickOneditable()));

    connect(saveButton,SIGNAL(clicked()),this,SIGNAL(clickOnSave()));

}
void LyricsViewerDock::setLyrics(const QString& a)
{
    lyricsTextViewer->setText(a);
}
QString LyricsViewerDock::getLyrics()
{
    return lyricsTextViewer->document()->toHtml();
}

void LyricsViewerDock::setEditatble(bool iseditable)
{
    lyricsTextViewer->setReadOnly(!iseditable);
}
void LyricsViewerDock::clearData()
{
    lyricsTextViewer->clear();
}
