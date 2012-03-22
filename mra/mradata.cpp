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
#include <QtCore>
#include <string>
#include "mradata.h"


class CodecHolder {
public:
    CodecHolder(QByteArray name): m_oldCodec( QTextCodec::codecForCStrings() ) {
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName(name));
    }
    ~CodecHolder() {
        QTextCodec::setCodecForCStrings(m_oldCodec);
    }
private:
    QTextCodec *m_oldCodec;
};



MRAData::MRAData()
    : m_pointer(0)
{
}


MRAData::~MRAData()
{
}

void MRAData::clear()
{
    m_data.clear();
	this->m_pointer  = 0;
	
}

/*!
    \fn MRAData::addString()
 */
void MRAData::addString(const QString &str)
{
    CodecHolder holder("Windows-1251");
    
    QByteArray ba = str.toAscii();
    
	addInt32(ba.size());
	addData(ba.constData(), ba.size());
}


/*!
    \fn MRAData::addData(ubsigned char *data, unsigned int size)
 */
void MRAData::addData(const void *data_, ssize_t size)
{
    m_data.append(static_cast<const char*>(data_), size);
}


/*!
    \fn MRAData::addInt32(long int value)
 */
void MRAData::addInt32(quint32 value)
{
	this->addData(&value, sizeof(value));
}


/*!
    \fn MRAData::getData()
 */
const char *MRAData::getData()
{
	return m_data.constData();
}


/*!
    \fn MRAData::getSize()
 */
unsigned long int MRAData::getSize() const
{
	return m_data.size();
}


/*!
    \fn MRAData::getInt32()
 */
quint32 MRAData::getInt32()
{
    quint32 result = 0;
	if (m_pointer <= (getSize() - sizeof(result))) {
		result     = *(quint32*)(getData() + m_pointer) ;
        std::cout << std::hex << static_cast< unsigned int >( *(getData() + m_pointer) )<< " " <<
                     static_cast< unsigned int >( *(getData() + m_pointer+1) )<< " " <<
                     static_cast< unsigned int >( *(getData() + m_pointer+2) )<< " " <<
                     static_cast< unsigned int >( *(getData() + m_pointer+3) ) << " = " << std::dec << result
                     << std::endl;
		m_pointer +=  sizeof(result);
	}
    return result;
}

QString MRAData::getString()
{
	int len = getInt32();
	
	if (m_pointer <= (getSize() - len)) {
        CodecHolder holder("Windows-1251");
        QString result = QString::fromAscii(getData() + m_pointer, len);		
        
		m_pointer += len;
        
		return result;
	} else {
        return QString();
	}
}

bool MRAData::eof() const
{
	return (m_pointer >= getSize());
}
