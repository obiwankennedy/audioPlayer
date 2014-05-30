

#ifndef STYLEHELPER_H
#define STYLEHELPER_H

//#include "core_global.h"

#include <QtCore/QRect>
#include <QtGui/QPainter>
#include <QtGui/QApplication>
#include <QtGui/QPalette>
#include <QtGui/QColor>

// Helper class holding all custom color values

class  StyleHelper
{
public:
    // Height of the project explorer navigation bar
    static int navigationWidgetHeight() { return 24; }
    static qreal sidebarFontSize();
    static QPalette sidebarFontPalette(const QPalette &original);

    // This is our color table, all colors derive from baseColor
    static QColor baseColor();
    static QColor panelTextColor();
    static QColor highlightColor();
    static QColor shadowColor();
    static QColor borderColor();
    static QColor buttonTextColor() { return QColor(0x4c4c4c); }
    static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50);

    // Sets the base color and makes sure all top level widgets are updated
    static void setBaseColor(const QColor &color);

    // Gradients used for panels
    static void horizontalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);
    static void verticalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);
    static void menuGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);

    // Pixmap cache should only be enabled for X11 due to slow gradients
    static bool usePixmapCache() { return true; }

private:
    static QColor m_baseColor;
};

#endif // STYLEHELPER_H
