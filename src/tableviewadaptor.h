/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c TableViewAdaptor -a tableviewadaptor.h:tableviewadaptor.cpp ../resources/dbus/eu.playview.renaudguezennec.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef TABLEVIEWADAPTOR_H_1418672002
#define TABLEVIEWADAPTOR_H_1418672002

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface local.qdbuscpp2xml.PL_TableView
 */
class TableViewAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.qdbuscpp2xml.PL_TableView")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"local.qdbuscpp2xml.PL_TableView\">\n"
"    <signal name=\"actiondone\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"a\"/>\n"
"    </signal>\n"
"    <signal name=\"dataChanged\"/>\n"
"    <signal name=\"Maximum\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"M\"/>\n"
"    </signal>\n"
"    <signal name=\"Minimum\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"m\"/>\n"
"    </signal>\n"
"    <signal name=\"valueChanged\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"v\"/>\n"
"    </signal>\n"
"    <signal name=\"CommandStart\"/>\n"
"    <signal name=\"done\"/>\n"
"    <signal name=\"isCutable\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"a\"/>\n"
"    </signal>\n"
"    <signal name=\"isCopiable\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"a\"/>\n"
"    </signal>\n"
"    <signal name=\"isPastable\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"a\"/>\n"
"    </signal>\n"
"    <signal name=\"dataModelChanged\"/>\n"
"    <signal name=\"sendFileToPhone\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"uri\"/>\n"
"    </signal>\n"
"    <method name=\"PopupMenurequested\">\n"
"      <arg direction=\"in\" type=\"(ii)\" name=\"pos\"/>\n"
"      <annotation value=\"QPoint\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"    </method>\n"
"    <method name=\"onModify\"/>\n"
"    <method name=\"onRemove\"/>\n"
"    <method name=\"onForce\"/>\n"
"    <method name=\"OnSort\"/>\n"
"    <method name=\"cancel\"/>\n"
"    <method name=\"OnForceWriting\"/>\n"
"    <method name=\"OnUpdate\"/>\n"
"    <method name=\"onSelect\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"p\"/>\n"
"    </method>\n"
"    <method name=\"onremoveFile\"/>\n"
"    <method name=\"OnRegex\"/>\n"
"    <method name=\"onMoveSelection\"/>\n"
"    <method name=\"cut\"/>\n"
"    <method name=\"copy\"/>\n"
"    <method name=\"paste\"/>\n"
"    <method name=\"onFileNameAsTitle\"/>\n"
"    <method name=\"sendSelectedFileToDevice\"/>\n"
"    <method name=\"sendFile\"/>\n"
"  </interface>\n"
        "")
public:
    TableViewAdaptor(QObject *parent);
    virtual ~TableViewAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void OnForceWriting();
    void OnRegex();
    void OnSort();
    void OnUpdate();
    void PopupMenurequested(const QPoint &pos);
    void cancel();
    void copy();
    void cut();
    void onFileNameAsTitle();
    void onForce();
    void onModify();
    void onMoveSelection();
    void onRemove();
    void onSelect(int p);
    void onremoveFile();
    void paste();
    void sendFile();
    void sendSelectedFileToDevice();
Q_SIGNALS: // SIGNALS
    void CommandStart();
    void Maximum(int M);
    void Minimum(int m);
    void actiondone(int a);
    void dataChanged();
    void dataModelChanged();
    void done();
    void isCopiable(bool a);
    void isCutable(bool a);
    void isPastable(bool a);
    void sendFileToPhone(const QString &uri);
    void valueChanged(int v);
};

#endif