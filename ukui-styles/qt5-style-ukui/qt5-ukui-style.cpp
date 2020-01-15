#include "qt5-ukui-style.h"
#include "ukui-style-settings.h"
#include "ukui-tabwidget-default-slide-animator.h"
#include "qt5-ukui-control.h"

#include <QStyleOption>
#include <QWidget>
#include <QPainter>

#include "tab-widget-animation-helper.h"

#include <QDialogButtonBox>
#include <QStyle>
#include <QDebug>

Qt5UKUIStyle::Qt5UKUIStyle(bool dark) : QProxyStyle ("gtk2")
{
    m_tab_animation_helper = new TabWidgetAnimationHelper(this);
    uicontrol=new QtUKUIControl();
}

void Qt5UKUIStyle::polish(QPalette &palette){
   QColor  button_background(233,233,233),
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

int Qt5UKUIStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}


void Qt5UKUIStyle::drawPrimitive(QStyle::PrimitiveElement element,const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    //qDebug()<<"draw PE"<<element;
    switch (element) {
    case PE_IndicatorCheckBox:
          //  drawBronzeCheckBoxIndicator(option,painter);
            break;
    case PE_PanelButtonCommand:break;
    case PE_FrameDefaultButton:break;
     case PE_PanelButtonBevel:break;
     case PE_PanelButtonTool:break;
     case PE_FrameButtonBevel:break;
     case PE_FrameButtonTool:break;
    case PE_IndicatorButtonDropDown:
            uicontrol->drawBronzeBevel(option,painter);
            break;
     case PE_Frame:break;
     case PE_PanelToolBar:
         //  uicontrol->drawBronzeFrame(option,painter);
            break;
        //case PE_FrameDefaultButton:
         //   break;
    case PE_FrameDockWidget:break;
   case PE_FrameGroupBox:break;
    case PE_FrameLineEdit:break;
    case PE_FrameTabWidget:break;
   case QStyle::PE_PanelMenu:break;
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
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing,true);
            painter->setPen(opt.palette.color(QPalette::Window));
            painter->setBrush(opt.palette.color(QPalette::ToolTipBase));
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





void Qt5UKUIStyle::drawControl(ControlElement element, const QStyleOption *option,QPainter *painter,const QWidget *widget) const
{
   //QtUKUIControl *ukuicontrol=new QtUKUIControl();
   switch (element) {
   case CE_PushButton:break;
   case CE_CheckBox:break;
   case CE_RadioButton:break;
   case CE_TabBarTab:break;
   case CE_ProgressBar:break;
   case CE_MenuBarItem:break;
 //  case CE_ScrollBarSlider:uicontrol->drawUKUISlide(option,painter);break;
   case CE_ToolBar:break;
   case CE_MenuTearoff:break;
   case CE_MenuBarEmptyArea:uicontrol->drawBronzeFrame(option,painter);break;

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
}



void Qt5UKUIStyle::drawComplexControl(ComplexControl which, const QStyleOptionComplex *option,
                                     QPainter *painter, const QWidget *widget) const
{

    switch (which) {
    case CC_ToolButton:break;
//    case CC_Slider:uicontrol->drawUKUISlide(option,painter);break;
    case CC_TitleBar:break;
   case CC_ScrollBar:uicontrol->drawUKUISlide(option,painter);break;
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








