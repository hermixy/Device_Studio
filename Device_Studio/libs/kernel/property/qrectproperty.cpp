#include "qrectproperty.h"

#include "qintproperty.h"
#include "../xmlnode.h"

QRectProperty::QRectProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{
    setType("Rect");

    m_x = new QIntProperty(this);
    m_x->setShowName(tr("x"));
    m_x->setName("x");

    m_y = new QIntProperty(this);
    m_y->setShowName(tr("y"));
    m_y->setName("y");

    m_width = new QIntProperty(this);
    m_width->setShowName(tr("width"));
    m_width->setName("width");

    m_height = new QIntProperty(this);
    m_height->setShowName(tr("height"));
    m_height->setName("height");


    setValue(QRect(0,0,0,0));

    connectUpdateValue();
}

QString QRectProperty::getValueText()
{
    if(m_x->getVisible())
    {
        return QString("[%1,%2],%3 x %4")
                .arg(m_x->getValue().toInt())
                .arg(m_y->getValue().toInt())
                .arg(m_width->getValue().toInt())
                .arg(m_height->getValue().toInt());
    }
    else
    {
        return QString("%1 x %2")
                .arg(m_width->getValue().toInt())
                .arg(m_height->getValue().toInt());
    }
}

QIcon QRectProperty::getValueIcon()
{
    return QIcon();
}

void QRectProperty::setValue(const QVariant &value)
{
    disconnectUpdateValue();
    QRect re = value.toRect();

    if(m_x->getVisible())
    {
        m_x->setValue(re.x());
        m_y->setValue(re.y());
    }
    else
    {
        m_x->setValue(0);
        m_y->setValue(0);
    }
    m_width->setValue(re.width());
    m_height->setValue(re.height());

    re.setRect(m_x->getValue().toInt(),m_y->getValue().toInt(),
               m_width->getValue().toInt(),m_height->getValue().toInt());

    QAbstractProperty::setValue(re);

    disconnectUpdateValue();
}

QVariant QRectProperty::getValue()
{
    QVariant v = QAbstractProperty::getValue();
    if(!m_x->getVisible())
    {
        QRect re;
        re.setRect(0,0,m_width->getValue().toInt(),m_height->getValue().toInt());
        v=re;
    }
    return v;
}

void QRectProperty::updateValue()
{
    QRect rect;
    rect.setRect(m_x->getValue().toInt(),m_y->getValue().toInt(),
               m_width->getValue().toInt(),m_height->getValue().toInt());
    setValue(rect);
}

void QRectProperty::writeValue(XmlNode *xml)
{
    xml->setProperty("name",getName());
    xml->setProperty("type",getType());
}

void QRectProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
    setType(xml->getProperty("type"));
}

void QRectProperty::setSizeType(bool sizeType)
{
    m_x->setVisible(!sizeType);
    m_y->setVisible(!sizeType);
}
