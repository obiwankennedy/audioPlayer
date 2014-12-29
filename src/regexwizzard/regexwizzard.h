#ifndef REGEXWIZZARD_H
#define REGEXWIZZARD_H

#include "ui_regexwizzard.h"
#include <QDialog>
#include "playlistitem.h"

namespace Ui {
class regexwizzard;
}

/**
 * @brief The RegexWizzard class
 */
class RegexWizzard : public QDialog
{
    Q_OBJECT
public:
    RegexWizzard(QList<PlaylistItem*>* m);


private slots:
    void updateInputList();
    void appendField();
    void updateRegexToEdit();
    void updateEditToRegex();

private:
    Ui::regexwizzard *m_ui;
    QString m_regex;

    QList<PlaylistItem*>* m_selection;
};

#endif // REGEXWIZZARD_H
