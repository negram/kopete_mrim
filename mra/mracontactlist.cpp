#include "mracontactlist.h"

MRAContactList::MRAContactList()
{
}

MRAContactList::~MRAContactList()
{
}

const MRAContactListEntry& MRAContactList::operator [] (int index) const
{
    return m_items[index];
}

int MRAContactList::count() const
{
    return m_items.size();
}

void MRAContactList::addEntry(const MRAContactListEntry& newEntry)
{
    m_items.append(newEntry);
}

void MRAContactList::setStatus(int status) {
    m_status = status;
}

int MRAContactList::status() const {
    return m_status;
}

const MRAContactListEntry *MRAContactList::getByAddress(const QString &address) const {
    foreach( const MRAContactListEntry &entry, m_items ) {
        if ( entry.address() == address ) {
            return &entry;
        }
    }
    return 0;
}

void MRAContactList::deleteContact(const QString &address) {
    for(int i = 0; i < m_items.size(); ++i) {
        if (m_items[i].address() == address) {
            m_items.remove(i, 1);
        }
    }
}


