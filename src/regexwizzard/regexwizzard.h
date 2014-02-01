#ifndef REGEXWIZZARD_H
#define REGEXWIZZARD_H

#include "ui_regexwizzard.h"
#include <QDialog>
class RegexWizzard : public QDialog,private Ui_regexwizzard
{
    Q_OBJECT
public:
    RegexWizzard();


private slots:
    void appendField();
    void updateRegexToEdit();
    void updateEditToRegex();

private:
    QString m_regex;
};

#endif // REGEXWIZZARD_H
