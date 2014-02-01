#include "regexwizzard.h"

RegexWizzard::RegexWizzard()
{
    setupUi(this);
    FieldsSelector->addItem(tr("Number"),"(\\d+)");
    FieldsSelector->addItem(tr("Anything"),"(.*)");

    connect(addButton,SIGNAL(pressed()),this,SLOT(appendField()));
    connect(regexEdit,SIGNAL(editingFinished()),this,SLOT(updateEditToRegex()));
}
void RegexWizzard::appendField()
{
   m_regex += FieldsSelector->itemData(FieldsSelector->currentIndex()).toString();
   updateRegexToEdit();
}
void RegexWizzard::updateRegexToEdit()
{
regexEdit->setText(m_regex);


}
void RegexWizzard::updateEditToRegex()
{
m_regex = regexEdit->text();
}
