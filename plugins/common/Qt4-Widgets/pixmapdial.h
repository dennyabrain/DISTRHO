/*
 * Pixmap Dial, a custom Qt4 widget
 * Copyright (C) 2011-2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the COPYING file
 */

#ifndef PIXMAPDIAL_H
#define PIXMAPDIAL_H

#include <QtGui/QDial>
#include <QtGui/QPixmap>

class PixmapDial : public QDial
{
    Q_OBJECT

public:
    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL   = 1
    };

    PixmapDial(QWidget* parent);
    ~PixmapDial();

    int getSize() const;
    void setEnabled(bool enabled);
    void setLabel(QString label);
    void setPixmap(int pixmap_id);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void updateSizes();

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    QPixmap m_pixmap;
    QString m_pixmap_n_str;

    Orientation m_orientation;

    QString m_label;
    QPointF m_label_pos;
    int     m_label_width;
    int     m_label_height;

    QLinearGradient m_label_gradient;
    QRectF m_label_gradient_rect;

    QColor m_color1;
    QColor m_color2;
    QColor m_colorT[2];

    int p_width, p_height, p_size, p_count;
};

#endif // PIXMAPDIAL_H
