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

#include "../ImageAboutWindow.hpp"

// FIXME: 32bit hack
#if ! (defined (__LP64__) || defined (_LP64) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
# define PAD_SIZE +1
#else
# define PAD_SIZE
#endif

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

ImageAboutWindow::ImageAboutWindow(App& app, Window& parent, const Image& image)
    : Window(app, parent),
      Widget((Window&)*this),
      fImgBackground(image)
{
    Window::setSize(image.getWidth(), image.getHeight() PAD_SIZE);
    Window::setTitle("About");
}

ImageAboutWindow::ImageAboutWindow(Widget* widget, const Image& image)
    : Window(widget->getParentApp(), widget->getParentWindow()),
      Widget((Window&)*this),
      fImgBackground(image)
{
    Window::setSize(image.getWidth(), image.getHeight() PAD_SIZE);
    Window::setTitle("About");
}

void ImageAboutWindow::setImage(const Image& image)
{
    fImgBackground = image;
    Window::setSize(image.getWidth(), image.getHeight() PAD_SIZE);
}

void ImageAboutWindow::onDisplay()
{
    fImgBackground.draw();
}

bool ImageAboutWindow::onMouse(int, bool press, int, int)
{
    if (press)
    {
        Window::close();
        return true;
    }

    return false;
}

bool ImageAboutWindow::onKeyboard(bool press, uint32_t key)
{
    if (press && key == CHAR_ESCAPE)
    {
        Window::close();
        return true;
    }

    return false;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DGL
