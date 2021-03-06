#ifndef MRIMACCOUNT_H
#define MRIMACCOUNT_H

#include <kopete/kopeteaccount.h>
#include "mra/mraprotocol.h"

class MrimProtocol;
class MRAProtocol;
class MRAContactList;
class MRAOfflineMessage;
class TransferRequestInfo;
class KActionMenu;

namespace Kopete {
    class Message;
}

class MrimAccount : public Kopete::Account
{
    Q_OBJECT
public:
    explicit MrimAccount( MrimProtocol *parent, const QString& accountID );
    ~MrimAccount();

    /**
     * @brief Create a New Contact
     *
     * Creates a protocol specific Kopete::Contact subclass and adds it to the supplied
     * Kopete::MetaContact
     * This is called internally only, as contacts cannot be added manually
     *
     * @return @c true if the contact is created, @c false otherwise
     */
    virtual bool createContact(const QString& contactId, Kopete::MetaContact* parentContact);

    /**
     * @brief Called when Kopete is set globally away
     *
     * @todo FIXME: This Doesn't Do Anything Right Now
     */
    virtual void setAway(bool away, const QString& reason);

    /**
     * @brief Parse The Config File
     *
     * This Function parses the appropriate group in the kopeterc
     * It sets come internally used constants like @ref username, @ref emailAddress
     */
    void parseConfig();

    /**
     * @brief Called when Kopete status is changed globally
     *
     * @todo FIXME: This Only Makes us go online or offline, we cannot go away
     */
    virtual void setOnlineStatus(const Kopete::OnlineStatus& status , const Kopete::StatusMessage &reason = Kopete::StatusMessage(),
                                 const OnlineStatusOptions& options = None);
    virtual void setStatusMessage(const Kopete::StatusMessage& statusMessage);

    /**
     * @brief Custom action menu
     */
    void fillActionMenu( KActionMenu *actionMenu );

    /**
     * @brief 'Connect' to the MRIM service.
     *
     * This the one stop call to do everything, like starting server, publishing, discovery, etc
     * This will clear the contact list in the beginning, and start re populating it
     * @todo Do something with initialStatus
     *
     * @param initialStatus
     */
    virtual void connect( const Kopete::OnlineStatus& initialStatus = Kopete::OnlineStatus() );

    /**
     * @brief Disconnect from the service.
     *
     * This will disconnect from the service. It will stop everything started in connect
     * It cleans out the contact list after it is finished
     */
    virtual void disconnect();



    Q_PROPERTY(QByteArray username READ getUsername WRITE setUsername)

    void setUsername(const QByteArray &arg);
    const QByteArray getUsername() const;


    Q_PROPERTY(QByteArray password READ getPassword WRITE setPassword)

    void setPassword(const QByteArray &arg);
    const QByteArray getPassword() const;


    Q_PROPERTY(QByteArray protocolVersion READ getProtocolVersion WRITE setProtocolVersion)

    void setProtocolVersion(const QByteArray &arg);
    const QByteArray getProtocolVersion() const;


    void sendMessage(const QString &to, const QString &text);

    void loadChatMembersList(const QString &to);

    void inviteMemberToChat(const QString &to, const QString &contactIdToInvite);

    void removeMemberFromChat(const QString &to, const QString &contactIdToInvite);

    void contactTypingAMessage( const QString &to );

    void loadAvatar( const QString &email );

    void loadPhoto( const QString &email, QObject *receiver, const char *member );

    void loadUserInfo( const QString &email );

    void deleteContact( const QString &email );

    void renameContact( const QString &email, const QString &newName );

    void moveContactToGroup( const QString &email, const QString &newGroupName );

    int getGroupIdByName( const QString &groupName );

    int addGroupAndReturnId(const QString groupName);

    MRAProtocol *getMraProtocol();



signals:

public slots:

    /**
     * @brief Change the account's status.  Called by KActions and internally.
     */
    void slotGoOnline();
    /**
     * @brief Change the account's status.  Called by KActions and internally.
     *
     * @todo FIXME: This Does Nothing Useful
     */
    void slotGoAway();

    /**
     * @brief Change the account's status.  Called by KActions and internally.
     */
    void slotGoOffline();

    void slotGoBusy();

    void slotReceivedMessage( const QString &from, const QString &text );
    void slotReceivedOfflineMessage( const MRAOfflineMessage &message );
    void slotTypingAMessage( const QString &from );

    void requestForAuthorization( const QString &contact );

    /**
     * @brief Trggers add group task. Called from status menu.
     */
    void addGroup();

    /**
     * @brief Trggers create a new conference task. Called from status menu.
     */
    void addConference();

private slots:

    void slotReceivedContactList(const MRAContactList &list);

    void slotConnected();
    void slotDisconnected(const QString &reason);
    void slotLoginFailed(const QString &reason);

    void authorizeRequestReceived(const QString &from, const QString &text);

    void slotUserStatusChanged(const QString &user, int newStatus);

    void slotAvatarLoaded(const QString &contact, const QImage &image);

    void slotUserInfoLoaded(const QString &contact, const MRAContactInfo &info);

    void slotAddContactAckReceived(int status, int contactId);

    void slotChatSettingsReceived(const QString &chat, const MRAConferenceSettings &settings);
    void slotChatInvitationReceived(const QString &chat, const QString &title, const QString &from);

    void slotTransferRequest(const TransferRequestInfo &transferInfo);
    void slotTransferRequestCancelled(const TransferRequestInfo &transferInfo);
private:
    class Private;
    Private *d;

    Kopete::OnlineStatus mrimStatusToKopete(int mrimStatus);
};

#endif // MRIMACCOUNT_H
