#ifndef LIBQT5UKUISTYLE_GLOBAL_H
#define LIBQT5UKUISTYLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBQT5UKUISTYLE_LIBRARY)
#  define LIBQT5UKUISTYLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBQT5UKUISTYLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBQT5UKUISTYLE_GLOBAL_H
