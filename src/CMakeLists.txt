#add_subdirectory (directoryFacade)
#add_subdirectory (factory)
#add_subdirectory (document)
#add_subdirectory (deleguate)

FIND_PROGRAM(CMAKE_PKGCONFIG_EXECUTABLE pkg-config)
MARK_AS_ADVANCED(CMAKE_PKGCONFIG_EXECUTABLE)


SET (ID3TAG -lid3)


SET(CMAKE_PKGCONFIG_CXX_FLAGS -lid3)

SET (QAssistant /usr/local/Trolltech/Qt-4.4.0/include/QtAssistantClient /usr/local/Trolltech/Qt-4.4.0/include/QtAssistant)

SET( PlayListGenerator_SRCS defaultdecorator.h edittagbox.h itemdecorator.h mediatype.h mp3decorator.h pl_tableview.h pl_taggerid3.h pl_taglibfile.h  playlist.h playlistgenerator.h playlistitem.h playlistmodel.h playlistviewer.h  data.h amendtag.h visitormedia.h thread.h visitormediaseeker.h  wizzardexport.h  pl_command.h  pl_removecommand.h pl_defaultaudio.h  pl_sortcommand.h  pl_itemcompare.h  sortdialog.h  importparser.h  plsimport.h  xmlimport.h  pl_titlewritingcommand.h  preferences_Impl.h preference_data.h  cmd_thread.h  player.h  pl_treeview.h  pl_treemodel.h pl_treeitem.h pl_texteditordelegate.h defaultdecorator.cpp  edittagbox.cpp itemdecorator.cpp mp3decorator.cpp  pl_tableview.cpp  pl_taggerid3.cpp  pl_taglibfile.cpp  playlist.cpp  playlistgenerator.cpp  playlistitem.cpp playlistmodel.cpp  playlistviewer.cpp  amendtag.cpp  visitormedia.cpp  thread.cpp  visitormediaseeker.cpp  wizzardexport.cpp  pl_command.cpp  pl_removecommand.cpp pl_defaultaudio.cpp  pl_sortcommand.cpp  pl_itemcompare.cpp  sortdialog.cpp  importparser.cpp  plsimport.cpp  xmlimport.cpp  pl_titlewritingcommand.cpp  preferences_Impl.cpp  preference_data.cpp  cmd_thread.cpp  player.cpp  pl_treeview.cpp pl_treemodel.cpp  pl_treeitem.cpp  pl_texteditordelegate.cpp main.cpp directoryFacade/directory.h directoryFacade/file.h  directoryFacade/node.h directoryFacade/pl_directoryfacade.h  directoryFacade/visitorfinder.h  directoryFacade/visitornode.h  directoryFacade/directory.cpp  directoryFacade/file.cpp  directoryFacade/pl_directoryfacade.cpp  directoryFacade/visitorfinder.cpp  directoryFacade/visitornode.cpp deleguate/trackdelegate.h deleguate/trackdelegate.cpp document/pl_document.cpp document/pl_documentmodel.cpp document/pl_impldocmodel.cpp document/pl_htmldoc.cpp document/pl_cvsdoc.cpp  document/pl_plsdoc.cpp  document/pl_pdfdoc.cpp  document/pl_xmldoc.cpp document/pl_document.h  document/pl_documentmodel.h  document/pl_impldocmodel.h  document/pl_htmldoc.h  document/pl_cvsdoc.h  document/pl_plsdoc.h  document/pl_pdfdoc.h document/pl_xmldoc.h  factory/factoryother.cpp factory/factoryother.h factory/factorymedia.cpp  factory/factorymp3.cpp  factory/mediafacade.cpp  factory/pl_audiofile.cpp  factory/pl_mediafile.cpp  factory/pl_mp3file.cpp  factory/factorymedia.h  factory/factorymp3.h  factory/mediafacade.h  factory/pl_audiofile.h  factory/pl_mediafile.h factory/pl_mp3file.h )



SET( PlayListGenerator_HEADERS player.h  amendtag.h cmd_thread.h  deleguate/trackdelegate.h playlistgenerator.h playlistviewer.h playlistmodel.h edittagbox.h pl_command.h pl_tableview.h pl_texteditordelegate.h pl_treeview.h pl_treemodel.h preferences_Impl.h thread.h visitormediaseeker.h wizzardexport.h)

SET(PlayListGenerator_RSSC playlistgenerator.qrc)



QT4_ADD_RESOURCES(PlayListGenerator_SRCS ${PlayListGenerator_RSSC})

QT4_WRAP_CPP( PlayListGenerator_MOC_SRCS   ${PlayListGenerator_MOC_HEADERS} )


ADD_EXECUTABLE( PlayListGenerator ${PlayListGenerator_SRCS} ${PlayListGenerator_MOC_SRCS})

TARGET_LINK_LIBRARIES( PlayListGenerator ${QT_LIBRARIES} ${ID3TAG} ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY} ${QT_PHONON_LIBRARY} ${QT_QTASSISTANT_LIBRARY})

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIRS} ${CMAKE_PKGCONFIG_C_FLAGS} ${QT_PHONON_INCLUDE_DIR} ${QT_QTXML_INCLUDE_DIR} ${QT_QTASSISTANT_INCLUDE_DIR} ${QAssistant} directoryFacade factory document deleguate)
LINK_DIRECTORIES(${QT_LIBRARY_DIRS} ${PKGCONFIG_LIBRARIES} ${QT_PHONON_LIBRARY_DIR} ${QT_QTXML_LIBRARY_DIR} ${QT_QTASSISTANT_LIBRARY_DIR} ${QAssistant} directoryFacade factory document deleguate)
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories (${PlayListGenerator_SOURCE_DIR}/src)
link_directories (${PlayListGenerator_BINARY_DIR}/bin)



