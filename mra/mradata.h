#ifndef MRADATA_H
#define MRADATA_H

#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <QObject>
#include <QByteArray>

class MRAData : public QObject {
    Q_OBJECT
public:
    MRAData(QObject * parent = 0);
    MRAData(const QByteArray &data, QObject * parent = 0);

    ~MRAData();
    void addString(const QString &str);
    QString getString();

    void addUnicodeString(const QString &str);
    QString getUnicodeString();

    void addUint32(quint32 value);
    quint32 getUint32();

    const char *getData();
    int getSize() const;
    void addData(const void *data_, ssize_t size);
    void addBinaryString(const QByteArray &data);
    QByteArray getBinaryString();
    void addData(const QByteArray &data);

    void addUIDL(const QByteArray &str);
    QByteArray getUIDL();

    bool eof() const;

    void clear();
    void dumpData();
    QString toBase64() const;
    const QByteArray &toByteArray() const;

    QByteArray getNBytes(int n);
    void addNBytes(int n, const QByteArray &data);

private:
private:
    QByteArray m_data;
    int m_pointer;
};

#endif
