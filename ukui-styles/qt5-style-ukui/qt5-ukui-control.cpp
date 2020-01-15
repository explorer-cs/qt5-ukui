#include "qt5-ukui-control.h"

#include "ukui-style-settings.h"
#include "ukui-tabwidget-default-slide-animator.h"

#include <QStyleOption>
#include <QWidget>
#include <QPainter>
#include <QDialogButtonBox>
#include <QStyle>
#include <QDebug>


//QtUKUIControl::QtUKUIControl(): QProxyStyle ("gtk2")
////{

////}

    QRect QtUKUIControl::subControlRect(ComplexControl whichControl, const QStyleOptionComplex *option,
                                      SubControl whichSubControl, const QWidget *widget) const
    {
        if(whichControl==CC_SpinBox){
            int frameWidth=pixelMetric(PM_DefaultFrameWidth,option,widget);
            int buttonWidth=16;
            switch(whichSubControl){
            case SC_SpinBoxFrame:
                return option->rect;
            case SC_SpinBoxEditField:
                return option->rect.adjusted(+buttonWidth,+frameWidth,-buttonWidth,-frameWidth);
            case SC_SpinBoxDown:
                return visualRect(option->direction,option->rect, QRect(option->rect.x(),option->rect.y(),
                                                           buttonWidth,option->rect.height()));
            case SC_SpinBoxUp:
                return visualRect(option->direction,option->rect, QRect(option->rect.right()-buttonWidth,
                                             option->rect.y(), buttonWidth,option->rect.height()));
            default:
                return QRect();
            }
        }else{
            return QProxyStyle::subControlRect(whichControl,option,whichSubControl,widget);
        }

    }



    void QtUKUIControl::drawUKUISlide(const QStyleOption *option, QPainter *painter) const
    {

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(option->palette.color(QPalette::Button));
        painter->setBrush(option->palette.color(QPalette::Button));
        painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),6,6);
        painter->restore();

    }


    void QtUKUIControl::drawUKUIComboBox(const QStyleOption *option, QPainter *painter) const
    {

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(QColor(248,248,248));
        painter->setBrush(QColor(248,248,248));
        // painter->setFont(QColor(252,255,0));
        painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),4,4);
        painter->restore();

    }

    void QtUKUIControl::drawToolButton(const QStyleOption *option, QPainter *painter) const
    {

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);

        painter->setPen(QColor(252,255,0));
        //painter->setBrush(QColor(233,233,233));
        painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),10,10);
        //painter->drawImage(opi
        painter->restore();

    }



















    void QtUKUIControl::drawBronzeFrame(const QStyleOption *option, QPainter *painter) const
    {

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);

        painter->setPen(QPen(option->palette.foreground(),1.0));
        //QRect roundframRect=option->rect.adjusted(+1,+1,-1,-1);
       painter->setBrush(QColor(255,0,0));
       // painter->setFont(QColor(252,255,0));
        painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),10,10);
        painter->restore();

    }


    void QtUKUIControl::drawBronzeSpinBoxButton(SubControl which, const QStyleOptionComplex *option,QPainter *painter) const
    {
        PrimitiveElement arrow=PE_IndicatorArrowLeft;
        QRect buttonRect=option->rect;
        if((which==SC_SpinBoxUp)!=(option->direction==Qt::RightToLeft)){
            arrow=PE_IndicatorArrowRight;
            buttonRect.translate(buttonRect.width()/2,0);
        }
        buttonRect.setWidth((buttonRect.width()+1)/2);

        QStyleOption buttonOpt(*option);

        painter->save();
        painter->setClipRect(buttonRect,Qt::IntersectClip);
        if(!(option->activeSubControls&which))
            buttonOpt.state&=~(State_MouseOver|State_On|State_Sunken);
        drawBronzeBevel(&buttonOpt,painter);

        QStyleOption arrowOpt(buttonOpt);
        arrowOpt.rect=subControlRect(CC_SpinBox,option,which).adjusted(+3,+3,-3,-3);
        if(arrowOpt.rect.isValid())
            drawPrimitive(arrow,&arrowOpt,painter);
        painter->restore();
    }
















    void QtUKUIControl::drawBronzeBevel(const QStyleOption *option, QPainter *painter) const
    {
        QColor buttonColor=option->palette.button().color();

        int coeff=(option->state&State_MouseOver)?115:105;

        QLinearGradient gradient(0,0,0,option->rect.height());
        gradient.setColorAt(0.0,option->palette.light().color());
        gradient.setColorAt(0.2,buttonColor.lighter(coeff));
        gradient.setColorAt(0.8,buttonColor.darker(coeff));
        gradient.setColorAt(1.0,option->palette.dark().color());

        double penWidth=1.0;
        if(const QStyleOptionButton* buttonOpt=qstyleoption_cast<const QStyleOptionButton*>(option)){
            if(buttonOpt->features&QStyleOptionButton::DefaultButton)
                penWidth=2.0;
        }
        QRect roundRect=option->rect.adjusted(+1,+1,-1,-1);
        if(!roundRect.isValid())
            return;

        int diameter=12;
        int cx=100*diameter/roundRect.width();
        int cy=100*diameter/roundRect.height();

        painter->save();
    //    painter->setPen(Qt::NoPen);
     painter->setBrush(gradient);
    //    painter->drawRoundRect(roundRect,cx,cy);

    //   if(option->state&(State_On|State_Sunken)){
    //        QColor slightlyOpaqueBlack(0,0,0,63);
    //        painter->setBrush(slightlyOpaqueBlack);
    //        painter->drawRoundRect(roundRect,cx,cy);
    //   }

        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(QPen(option->palette.foreground(),penWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundRect(roundRect,cx,cy);
        painter->restore();
    }












    void QtUKUIControl::drawBronzeCheckBoxIndicator(const QStyleOption *option, QPainter *painter) const
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        if(option->state&State_MouseOver){
            painter->setBrush(option->palette.alternateBase());
        }else{
            painter->setBrush(option->palette.base());
        }
        painter->drawRoundRect(option->rect.adjusted(+1,+1,-1,-1));
        if(option->state&(State_On|State_NoChange)){
            QPixmap pixmap;
            if(!(option->state&State_Enabled)){
                pixmap.load(":/images/checkmark-disabled.png");
            }else if(option->state&State_NoChange){
                pixmap.load(":/images/checkmark-partial.png");
            }else{
                pixmap.load(":/images/checkmark.png");
            }
            QRect pixmapRect=pixmap.rect().translated(option->rect.topLeft()).translated(+2,-6);
            QRect painterRect=visualRect(option->direction,option->rect,pixmapRect);
            if(option->direction==Qt::RightToLeft){
                painter->scale(-1.0,+1.0);
                painterRect.moveLeft(-painterRect.right()-1);
            }
            painter->drawPixmap(painterRect,pixmap);
        }
        painter->restore();
    }





