#include "qt5-ukui-style.h"
#include "ukui-style-settings.h"
#include "ukui-tabwidget-default-slide-animator.h"

#include <QStyleOption>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QDebug>

Qt5UKUIStyle::Qt5UKUIStyle(bool dark) : QProxyStyle ("oxygen")
{

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
        auto w = qobject_cast<QTabWidget *>(widget);
        auto animator = new UKUI::TabWidget::DefaultSlideAnimator(w);
        animator->bindTabWidget(w);
    }

    return QProxyStyle::polish(widget);
}

void Qt5UKUIStyle::unpolish(QWidget *widget)
{
    if (widget->inherits("QMenu")) {
        widget->setAttribute(Qt::WA_TranslucentBackground, false);
    }

    return QProxyStyle::unpolish(widget);
}

void Qt5UKUIStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    //qDebug()<<"draw PE"<<element;
    switch (element) {
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
            painter->setPen(opt.palette.color(QPalette::Window));
            painter->setBrush(color);
            painter->drawRect(opt.rect.adjusted(0, 0, -1, -1));
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
