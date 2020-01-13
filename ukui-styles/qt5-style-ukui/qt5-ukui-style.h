#ifndef QT5UKUISTYLE_H
#define QT5UKUISTYLE_H

#include <QProxyStyle>

class TabWidgetAnimationHelper;

class Qt5UKUIStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit Qt5UKUIStyle(bool dark = false);

    int styleHint(StyleHint hint,const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const;
    void polish(QWidget *widget) ;
    void unpolish(QWidget *widget) ;
    void polish(QPalette& palette) ;
    //void unpolish(QPalette& palette);
    void drawComplexControl(ComplexControl which,const QStyleOptionComplex* option,QPainter* painter,const QWidget* widget=0)const;
    void drawPrimitive(QStyle::PrimitiveElement element,const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const;
    void drawControl(ControlElement element,const QStyleOption *option,QPainter *painter,const QWidget *widget) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *w=0) const;

 public slots:
     QIcon standardIconImplementation(StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget=0) const;

 private:
     void drawBronzeFrame(const QStyleOption* option,QPainter* painter)const;
     void drawBronzeBevel(const QStyleOption* option,QPainter* painter)const;
     void drawBronzeCheckBoxIndicator(const QStyleOption* option,QPainter* painter)const;
     void drawBronzeSpinBoxButton(SubControl which,const QStyleOptionComplex* option,QPainter* painter)const;
    
     TabWidgetAnimationHelper *m_tab_animation_helper;
};


#endif // QT5UKUISTYLE_H
