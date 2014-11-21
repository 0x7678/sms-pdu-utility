#include "pdu.h"
#include <QTextCodec>
#include <QDebug>
Pdu::Pdu(QObject *parent)
    :QObject(parent)
{
    m_typeOfNumField = 1;
    m_numPlanIdField = 1;

    m_daTypeOfNumField = 0;
    m_daNumPlanIdField = 1;
}

Pdu::~Pdu()
{

}

QString Pdu::semiOctetRepresentation(const QString &src)
{
    QString dest;
    for(int i = 0; i < src.size(); i += 2) {
        if(i == src.size() - 1) {
            dest.append('F');
        }
        else {
            dest.append(src[i+1]);
        }
        dest.append(src[i]);
    }
    return dest;
}

QString Pdu::generate()
{
    QString smsc;

    // Address length
    smsc.append(QString("%1").arg(m_addrValue.size()/2+2, 2, 10, QLatin1Char('0')));

    // Type of address
    smsc.append(typeOfAddr());

    // Address value
    smsc.append(semiOctetRepresentation(m_addrValue));

// TPDU
    QString tpdu;
    // First-Octet
    tpdu.append("01");

    // TP-MR
    tpdu.append("00");



    //TP-Destination-Address
    tpdu.append(QString("%1").arg(m_destAddr.size(), 2, 16, QLatin1Char('0')).toUpper());
    tpdu.append(QString("%1").arg(m_daTypeOfAddrVal, 2, 16));
    tpdu.append(semiOctetRepresentation(m_destAddr));

    tpdu.append("0008");


    // TP-User Data
    tpdu.append(QString("%1").arg(m_userData.size()*2, 2, 16, QLatin1Char('0')).toUpper());
    QChar *data = m_userData.data();
    while (!data->isNull()) {
        tpdu.append(QString("%1").arg(data->unicode(), 4, 16, QLatin1Char('0')).toUpper());
        ++data;
    }

    QString temp;
    temp.append(QString("Length: %1\n").arg(tpdu.size() / 2));
    temp.append(smsc).append(tpdu);

    return temp;
}
