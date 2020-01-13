#include "qt5-ukui-style.h"
#include "ukui-style-settings.h"
#include "ukui-tabwidget-default-slide-animator.h"

#include <QStyleOption>
#include <QWidget>
#include <QPainter>

#include "tab-widget-animation-helper.h"

#include <QDialogButtonBox>
#include <QStyle>
#include <QDebug>

Qt5UKUIStyle::Qt5UKUIStyle(bool dark) : QProxyStyle ("oxygen")
{
    m_tab_animation_helper = new TabWidgetAnimationHelper(this);
}

void Qt5UKUIStyle::polish(QPalette &palette){
   QColor  button_background(248,248,248),
           tipbase(61, 107, 229),
           unfont(193,193,193),
           unbase(233, 233, 233);

    palette.setBrush(QPalette::Base,Qt::white);
    palette.setBrush(QPalette::Inactive,QPalette::Base,Qt::white);
    palette.setBrush(QPalette::Disabled,QPalette::Base,unbase);
    palette.setBrush(QPalette::Text,Qt::black);
    palette.setBrush(QPalette::Inactive,QPalette::Text,Qt::black);
    palette.setBrush(QPalette::Disabled,QPalette::Text,unfont);

    palette.setBrush(QPalette::Button,button_background);
    palette.setBrush(QPalette::Inactive,QPalette::Button,button_background);
    palette.setBrush(QPalette::Disabled,QPalette::Button,unbase);
    palette.setBrush(QPalette::ButtonText,Qt::black);
    palette.setBrush(QPalette::Inactive,QPalette::ButtonText,Qt::black);
    palette.setBrush(QPalette::Disabled,QPalette::ButtonText,unfont);

    palette.setBrush(QPalette::Window,Qt::white);
    palette.setBrush(QPalette::Inactive,QPalette::Window,Qt::white);
    palette.setBrush(QPalette::Disabled,QPalette::Window,unbase);
    palette.setBrush(QPalette::WindowText,Qt::black);
    palette.setBrush(QPalette::Inactive,QPalette::WindowText,Qt::black);
    palette.setBrush(QPalette::Disabled,QPalette::WindowText,unfont);

    palette.setBrush(QPalette::ToolTipBase,tipbase);
    palette.setBrush(QPalette::ToolTipText,Qt::white);

    palette.setBrush(QPalette::AlternateBase,button_background);
    palette.setBrush(QPalette::Inactive,QPalette::AlternateBase,button_background);
    palette.setBrush(QPalette::Disabled,QPalette::AlternateBase,unbase);

    palette.setBrush(QPalette::BrightText,Qt::black);
    palette.setBrush(QPalette::Inactive,QPalette::BrightText,Qt::black);
    palette.setBrush(QPalette::Disabled,QPalette::BrightText,unfont);

}


int Qt5UKUIStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

void Qt5UKUIStyle::polish(QWidget *widget)
{

    if (widget->inherits("QMenu")) {
        widget->setAttribute(Qt::WA_TranslucentBackground);
    }

    if (widget->inherits("QTabWidget")) {
        //FIXME: unpolish, extensiable.
        m_tab_animation_helper->registerWidget(widget);
    }

    return QProxyStyle::polish(widget);
}

void Qt5UKUIStyle::unpolish(QWidget *widget)
{
    if (widget->inherits("QMenu")) {
        widget->setAttribute(Qt::WA_TranslucentBackground, false);
    }

    if (widget->inherits("QTabWidget")) {
        m_tab_animation_helper->unregisterWidget(widget);
    }

    return QProxyStyle::unpolish(widget);
}

void Qt5UKUIStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    //qDebug()<<"draw PE"<<element;
    switch (element) {
    case PE_IndicatorCheckBox:
          //  drawBronzeCheckBoxIndicator(option,painter);
            break;
    case PE_PanelButtonCommand:
    case PE_FrameDefaultButton:
     case PE_PanelButtonBevel:
     case PE_PanelButtonTool:
     case PE_FrameButtonBevel:
     case PE_FrameButtonTool:
    case PE_IndicatorButtonDropDown:
            drawBronzeBevel(option,painter);
            break;
     case PE_Frame:
     case PE_PanelToolBar:
            drawBronzeFrame(option,painter);
            break;
        //case PE_FrameDefaultButton:
         //   break;
    case PE_FrameDockWidget:
   case PE_FrameGroupBox:
    case PE_FrameLineEdit:
    case PE_FrameTabWidget:
   case QStyle::PE_PanelMenu:
    case QStyle::PE_FrameMenu:
    {
        /*!
          \bug
          a "disabled" menu paint and blur in error, i have no idea about that.
          */
        if (widget->isEnabled()) {
            //qDebug()<<"draw menu frame"<<option->styleObject<<option->palette;
            QStyleOption opt = *option;
            auto color = opt.palette.color(QPalette::Base);
            if (UKUIStyleSettings::isSchemaInstalled("org.ukui.style")) {
                auto opacity = UKUIStyleSettings::globalInstance()->get("menuTransparency").toInt()/100.0;
                //qDebug()<<opacity;
                color.setAlphaF(opacity);
            }
            opt.palette.setColor(QPalette::Base, color);
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing,true);
            painter->setPen(opt.palette.color(QPalette::Window));
            painter->setBrush(color);
           // painter->drawRect(opt.rect.adjusted(0, 0, -1, -1));
            painter->drawRoundRect(opt.rect.adjusted(0, 0, -1, -1),10,10);
            painter->restore();
            return;
        }

        return QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
    default:
        break;
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}







void Qt5UKUIStyle::drawComplexControl(ComplexControl which, const QStyleOptionComplex *option,
                                     QPainter *painter, const QWidget *widget) const
{

    switch (which) {
    case CC_ToolButton:
    case CC_Slider:
    case CC_TitleBar:
   case CC_ScrollBar:
    case CC_ComboBox:
   { painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(QPen(option->palette.foreground(),1.0));
    //QRect roundframRect=option->rect.adjusted(+1,+1,-1,-1);
    painter->setBrush(QColor(252,255,0));
   // painter->setFont(QColor(252,255,0));
    painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),10,10);
    painter->restore();
}break;

    default:
        QProxyStyle::drawComplexControl(which, option, painter, widget);
    }

}




QRect Qt5UKUIStyle::subControlRect(ComplexControl whichControl, const QStyleOptionComplex *option,
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



void Qt5UKUIStyle::drawBronzeFrame(const QStyleOption *option, QPainter *painter) const
{

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);

    painter->setPen(QPen(option->palette.foreground(),1.0));
    //QRect roundframRect=option->rect.adjusted(+1,+1,-1,-1);
   painter->setBrush(QColor(255,0,0));
   // painter->setFont(QColor(252,255,0));
    painter->drawRoundedRect(option->rect.adjusted(+1,+1,-1,-1),10,10);
    painter->restore();



//    QRect rec= option->rect;
//    painter->save();
//    painter->setRenderHint();
//    painter->setBrush(option->palette.window().color());
//    painter->drawRoundedRect(rec,20,20);
//    painter->restore();
}

void Qt5UKUIStyle::drawBronzeBevel(const QStyleOption *option, QPainter *painter) const
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



void Qt5UKUIStyle::drawBronzeSpinBoxButton(SubControl which, const QStyleOptionComplex *option,QPainter *painter) const
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




void Qt5UKUIStyle::drawBronzeCheckBoxIndicator(const QStyleOption *option, QPainter *painter) const
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

void Qt5UKUIStyle::drawControl(ControlElement element, const QStyleOption *option,QPainter *painter,const QWidget *widget) const
{
   switch (element) {
   case CE_PushButton:
   case CE_CheckBox:
   case CE_RadioButton:
   case CE_TabBarTab:
   case CE_ProgressBar:
   case CE_MenuBarItem:
   case CE_ScrollBarSlider:
   case CE_ToolBar:
   case CE_MenuTearoff:
   case CE_MenuBarEmptyArea:
   drawBronzeFrame(option,painter);break;


   case CE_PushButtonLabel:
       {
           QStyleOptionButton myButtonOption;
           const QStyleOptionButton *buttonOption =
                   qstyleoption_cast<const QStyleOptionButton *>(option);
           if (buttonOption) {
               myButtonOption = *buttonOption;
               if (myButtonOption.palette.currentColorGroup()
                       != QPalette::Disabled) {
                   if (myButtonOption.state & (State_Sunken | State_On)) {
                       myButtonOption.palette.setBrush(QPalette::ButtonText,
                               myButtonOption.palette.brightText());
                   }
               }
           }
           QProxyStyle::drawControl(element, &myButtonOption, painter, widget);
       }
       break;
   default:
       QProxyStyle::drawControl(element, option, painter, widget);
   }
