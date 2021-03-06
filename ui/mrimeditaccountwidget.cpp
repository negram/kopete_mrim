#include <kdebug.h>
#include <kopeteaccount.h>
#include <kuser.h>
#include <kpimidentities/identity.h>
#include <kpimidentities/identitymanager.h>

#include "../debug.h"
#include "mrimaccount.h"
#include "mrimprotocol.h"
#include "mrimeditaccountwidget.h"

MrimEditAccountWidget::MrimEditAccountWidget( QWidget* parent, Kopete::Account* account )
    : QWidget(parent)
    , KopeteEditAccountWidget(account)
{
    mrimDebug() << __PRETTY_FUNCTION__;


    QVBoxLayout *layout = new QVBoxLayout( this );
    QWidget *widget = new QWidget( this );

    m_preferencesWidget.setupUi( widget );

    if (account) {
        group = account->configGroup();

        m_preferencesWidget.kcfg_username->setText(group->readEntry("username"));
        m_preferencesWidget.kcfg_password->setText(group->readEntry("password"));
        m_preferencesWidget.kcfg_protoVersion->setCurrentIndex(
                            m_preferencesWidget.kcfg_protoVersion->findText(group->readEntry("protoVersion"))
                         );
    } else {

        // In this block, we populate the default values
        QString password, login;
        QStringList names;

        // Create a KUser object with default values
        // We May be able to get username and Real Name from here
        KUser user = KUser();

        if (user.isValid()) {
            // Get the login name from KUser
            login = user.loginName();

            // First Get the Names from KUser
            names = user.property(KUser::FullName).toString().split(' ');
        }

        // Next try via the default identity
        KPIMIdentities::IdentityManager manager(true);
        const KPIMIdentities::Identity & ident = manager.defaultIdentity();

        if (! ident.isNull()) {
            // Get the full name from identity (only if not available via KUser)
            if ( names.isEmpty() )
                names = ident.fullName().split(' ');
        }

        if (! login.isEmpty())
            m_preferencesWidget.kcfg_username->setText(login);
        if (! password.isEmpty())
            m_preferencesWidget.kcfg_password->setText(password);

    }
    layout->addWidget( widget );
}

MrimEditAccountWidget::~MrimEditAccountWidget()
{
    mrimDebug() << __PRETTY_FUNCTION__;
}

Kopete::Account* MrimEditAccountWidget::apply() {
    mrimDebug() << __PRETTY_FUNCTION__;

    if (! account() ) {
        setAccount( new MrimAccount ( MrimProtocol::protocol(), m_preferencesWidget.kcfg_username->text()));
        mrimDebug() << "Write Group!";
    }

    account()->configGroup()->writeEntry("username", m_preferencesWidget.kcfg_username->text());
    account()->configGroup()->writeEntry("password", m_preferencesWidget.kcfg_password->text());
    account()->configGroup()->writeEntry("protoVersion", m_preferencesWidget.kcfg_protoVersion->currentText());
    ((MrimAccount *)account())->parseConfig();

    return account();
}

bool MrimEditAccountWidget::validateData() {
    mrimDebug() << __PRETTY_FUNCTION__;
    return true;
}
