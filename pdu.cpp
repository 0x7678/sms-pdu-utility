#include "pdu.h"
#include <QTextCodec>
#include <QDebug>
Pdu::Pdu(QObject *parent)
    :QObject(parent)
{
    m_addrValue = "8613800592500";
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

QString Pdu::analyzeSemiOctet(const QString &src)
{
    QString dest;

    if(src.size() % 2 != 0) {
        return dest;
    }

    for(int i = 0; i < src.size(); i += 2) {

        dest.append(src[i+1]);

        if(src[i] != QChar('F')) {
            dest.append(src[i]);
        }
    }
    return dest;
}


QString Pdu::analyzeAlphanumeric(QString &src)
{
    QString result;
    quint8 leftValue = 0, leftBits = 0;
    bool ok;

    while(src.size() >= 2) {
        quint8 byteValue = src.left(2).toInt(&ok, 16);
        quint8 integerValue;
        src.remove(0, 2);

        integerValue = ((byteValue & (0x07F >> leftBits)) << leftBits) + leftValue ;
        result.append(QChar(integerValue));


        leftValue = byteValue >> (7 - leftBits);
        leftBits++;

        if(leftBits == 7) {
            integerValue = byteValue >> 1;
            leftBits = 0;
            leftValue = 0;
            result.append(QChar(integerValue));
        }
    }
    return result;
}



QString Pdu::generate()
{
    QString smsc;

    // Address length
    smsc.append(QString("%1").arg(m_addrValue.size()/2+2, 2, 10, QLatin1Char('0')));

    // Type of address
    smsc.append("91");

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
    tpdu.append("81");
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

void Pdu::analyze()
{
    bool ok;
    QString text = qvariant_cast<QString>(resultTextArea->property("text"));

    int smscAddrLen = text.left(2).toInt();
    text.remove(0, 2);

    text.remove(0, 2);

    QString smscAddrValue = text.left(2*(smscAddrLen-1));
    text.remove(0, 2*(smscAddrLen-1));

    m_addrValue = analyzeSemiOctet(smscAddrValue);
    emit addrValueChange();

    int firstOctet = text.left(2).toInt(&ok, 16);
    text.remove(0, 2);

    if((firstOctet & 0x03) == SMS_SUBMIT) {
        text.remove(0, 2); //TP-MR
    }

    int destAddrLen = text.left(2).toInt(&ok, 16);
    if(destAddrLen%2 == 1) destAddrLen++;
    text.remove(0, 2);

    text.remove(0, 2);

    QString destAddrValue = text.left(destAddrLen);
    text.remove(0, destAddrLen);
    m_destAddr = analyzeSemiOctet(destAddrValue);
    emit destAddrChange();

    text.remove(0, 2);

    int dcs = text.left(2).toInt(&ok, 16);
    text.remove(0,2);

    if((firstOctet & 0x03) == SMS_DELIVER) {
        text.remove(0, 2*7); //TP-SCTS
    }

    int dataLen = text.left(2).toInt(&ok, 16);
    text.remove(0, 2);


    QByteArray byteArray = QByteArray::fromHex(text.toLatin1());
    if(dcs == 0x08) {
        /*we need to convert endianness*/
        QDataStream ds(&byteArray, QIODevice::ReadOnly);
        QVector<ushort> buf(byteArray.size()/2 + 1);
        int n = 0;
        ds.setByteOrder(QDataStream::BigEndian);
        while(!ds.atEnd()) {
          ushort s;
          ds >> s;
          buf[n++] = s;
        }
        buf[n] = 0;
        m_userData = QString::fromUtf16(buf.constData());

    } else {
        m_userData = analyzeAlphanumeric(text);
    }
    emit userDataChange();

}
