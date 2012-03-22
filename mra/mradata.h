/***************************************************************************
 *   Copyright (C) 2007 by netgr@am   *
 *   a@localhost   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MRADATA_H
#define MRADATA_H

#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <QObject>
#include <QByteArray>

class MRAData {
public:
    MRAData();

    ~MRAData();
    void addString(const QString &str);
    QString getString();
    
    void addInt32(quint32 value);
    quint32 getInt32();

    const char *getData();
    unsigned long int getSize() const;
    void addData(const void *data_, ssize_t size);
    bool eof() const;
    
    void clear();
    
private:
private:
    QByteArray m_data;
	// unsigned char *data;
	// unsigned long int  dataSize;
	unsigned long int m_pointer;
};

#endif