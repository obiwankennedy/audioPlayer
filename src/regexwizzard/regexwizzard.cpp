#include "regexwizzard.h"

RegexWizzard::RegexWizzard(QList<PlaylistItem*>* m)
    : m_selection(m),m_ui(new Ui::regexwizzard)
{
    m_ui->setupUi(this);

    connect(m_ui->m_regexpEdit,SIGNAL(editingFinished()),this,SLOT(updateEditToRegex()));
}
void RegexWizzard::appendField()
{

}
void RegexWizzard::updateRegexToEdit()
{



}
void RegexWizzard::updateEditToRegex()
{

}

void RegexWizzard::updateInputList()
{
    m_ui->m_inputField->currentData();
}
