/*
 * DISTRHO Plugin Toolkit (DPT)
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoUIInternal.hpp"

#include <QtGui/QResizeEvent>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Qt UI

QtUI::QtUI()
    : UI(),
      QWidget(nullptr)
{
}

QtUI::~QtUI()
{
}

// -----------------------------------------------------------------------

void QtUI::setSize(unsigned int width, unsigned int height)
{
    if (d_isResizable())
        resize(width, height);
    else
        setFixedSize(width, height);

    d_uiResize(width, height);
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
