#ifndef PDU_H
#define PDU_H

#include <QObject>
class Pdu : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString typeOfAddr READ typeOfAddr)
    Q_PROPERTY(QString addrValue MEMBER  m_addrValue)
    Q_PROPERTY(int typeOfNum READ typeOfNum WRITE setTypeOfNum)
    Q_PROPERTY(int numPlanId READ numPlanId WRITE setNumPlanId)

    Q_PROPERTY(int daTypeOfNum READ daTypeOfNum WRITE setDaTypeOfNum)
    Q_PROPERTY(int daNumPlanId READ daNumPlanId WRITE setDaNumPlanId)

    Q_PROPERTY(QString destAddr MEMBER  m_destAddr)
    Q_PROPERTY(QString userData MEMBER  m_userData)



public:
    Pdu(QObject *parent = 0);
    ~Pdu();

    QString typeOfAddr()const { return QString("%1").arg(m_typeOfAddrVal, 0, 16); }

    int typeOfNum()const { return m_typeOfNumField;}
    void setTypeOfNum(int val)
    {
        m_typeOfNumField = val;
        updateTypeOfAddr();
    }

    int numPlanId()const { return m_numPlanIdField;}
    void setNumPlanId(int val)
    {
        m_numPlanIdField = val;
        updateTypeOfAddr();
    }

    int daTypeOfNum()const { return m_daTypeOfNumField;}
    void setDaTypeOfNum(int val)
    {
        m_daTypeOfNumField = val;
        updateDaTypeOfAddr();
    }

    int daNumPlanId()const { return m_daNumPlanIdField;}
    void setDaNumPlanId(int val)
    {
        m_daNumPlanIdField = val;
        updateDaTypeOfAddr();
    }

    Q_INVOKABLE QString generate();

signals:
    void typeOfNumChange(void);

private:

    void updateTypeOfAddr() { m_typeOfAddrVal = (8+m_typeOfNumField)*16 + m_numPlanIdField; }
    void updateDaTypeOfAddr() { m_daTypeOfAddrVal = (8+m_daTypeOfNumField)*16 + m_daNumPlanIdField; }
    QString semiOctetRepresentation(const QString &src);


    int m_typeOfAddrVal;
    int m_typeOfNumField;
    int m_numPlanIdField;

    int m_daTypeOfAddrVal;
    int m_daTypeOfNumField;
    int m_daNumPlanIdField;

    QString m_addrValue;
    QString m_destAddr;
    QString m_userData;
};

#endif // PDU_H
