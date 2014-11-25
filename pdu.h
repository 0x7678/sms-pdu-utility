#ifndef PDU_H
#define PDU_H

#include <QObject>
class Pdu : public QObject
{
    Q_OBJECT


    Q_PROPERTY(QString addrValue MEMBER  m_addrValue NOTIFY addrValueChange)
    Q_PROPERTY(QString destAddr MEMBER  m_destAddr NOTIFY destAddrChange)
    Q_PROPERTY(QString userData MEMBER  m_userData NOTIFY userDataChange)



public:
    Pdu(QObject *parent = 0);
    ~Pdu();



    Q_INVOKABLE QString generate();
    Q_INVOKABLE void analyze();

signals:

    void addrValueChange(void);
    void userDataChange(void);
    void destAddrChange(void);

public:
    QObject *resultTextArea;

private:
    enum {
        SMS_DELIVER = 0,
        SMS_SUBMIT,
    };



    QString semiOctetRepresentation(const QString &src);
    QString analyzeSemiOctet(const QString &src);

    QString analyzeAlphanumeric(QString &src);



    QString m_addrValue;
    QString m_destAddr;
    QString m_userData;


};

#endif // PDU_H
