#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QHash>
#include "audiofilemodel.h"
#include "constants.h"
#include <QJsonObject>

namespace factory
{

QByteArray buildMessage(const QString& service, const QString& action, const QHash<QString, QVariant> &parameter);
QJsonArray model2Parameter(AudioFileModel* model);

QJsonObject messageToObject(const QString& message);
constants::Action actionToEnum(const QJsonObject& obj);

QByteArray fileToArray(const QString& file);
QByteArray imageToArray(const QImage& img);
};

#endif // MESSAGEFACTORY_H
