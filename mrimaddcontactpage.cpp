#include <kdebug.h>
#include <kopeteaccount.h>
#include <kopetemetacontact.h>
#include <kopetegroup.h>

#include "mrimaccount.h"

#include "mrimaddcontactpage.h"

MrimAddContactPage::MrimAddContactPage(QWidget *parent) :
    AddContactPage(parent)
{
    kWarning() << __PRETTY_FUNCTION__;
    QVBoxLayout* l = new QVBoxLayout( this );
    QWidget* w = new QWidget();
    m_mrimAddUI.setupUi( w );
    l->addWidget( w );
}

MrimAddContactPage::~MrimAddContactPage()
{
    kWarning() << __PRETTY_FUNCTION__;
}

bool MrimAddContactPage::apply( Kopete::Account* a, Kopete::MetaContact* m )
{
    kWarning() << __PRETTY_FUNCTION__;
    MrimAccount *ma = dynamic_cast<MrimAccount *>(a);
    ma->addNewContactToServerList( m_mrimAddUI.lineEdit->text(), m->groups()[0]->displayName() );
    return false;
}

bool MrimAddContactPage::validateData()
{
    kWarning() << __PRETTY_FUNCTION__;
    return true;
}


#include "mrimaddcontactpage.moc"