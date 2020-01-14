#ifndef QTUKUICONTROL_H
#define QTUKUICONTROL_H

#include <QProxyStyle>

class QtUKUIControl: public QProxyStyle
{
public:
    QtUKUIControl();
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *w=0) const;
    void drawBronzeFrame(const QStyleOption* option,QPainter* painter) const;
    void drawBronzeBevel(const QStyleOption* option,QPainter* painter)const;
    void drawBronzeCheckBoxIndicator(const QStyleOption* option,QPainter* painter)const;
    void drawBronzeSpinBoxButton(SubControl which,const QStyleOptionComplex* option,QPainter* painter)const;
};

#endif // QTUKUICONTROL_H
