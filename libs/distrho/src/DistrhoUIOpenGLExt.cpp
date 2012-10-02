/*
 * DISTHRO Plugin Toolkit (DPT)
 * Copyright (C) 2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the GPL.txt file
 */

#include "DistrhoDefines.h"

#ifdef DISTRHO_UI_OPENGL

#include "DistrhoUIInternal.h"

#include <cassert>
#include <vector>

START_NAMESPACE_DISTRHO

// -------------------------------------------------
// Point

Point::Point(int x, int y)
    : _x(x),
      _y(y)
{
}

Point::Point(const Point& pos)
    : _x(pos._x),
      _y(pos._y)
{
}

int Point::getX() const
{
    return _x;
}

int Point::getY() const
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}

Point& Point::operator= (const Point& pos)
{
    _x = pos._x;
    _y = pos._y;
    return *this;
}

Point& Point::operator+= (const Point& pos)
{
    _x += pos._x;
    _y += pos._y;
    return *this;
}

Point& Point::operator-= (const Point& pos)
{
    _x -= pos._x;
    _y -= pos._y;
    return *this;
}

// -------------------------------------------------
// Point

Size::Size(int width, int height)
    : _width(width),
      _height(height)
{
}

Size::Size(const Size& size)
    : _width(size._width),
      _height(size._height)
{
}

int Size::getWidth() const
{
    return _width;
}

int Size::getHeight() const
{
    return _height;
}

void Size::setWidth(int width)
{
    _width = width;
}

void Size::setHeight(int height)
{
    _height = height;
}

Size& Size::operator= (const Size& size)
{
    _width  = size._width;
    _height = size._height;
    return *this;
}

Size& Size::operator+= (const Size& size)
{
    _width  += size._width;
    _height += size._height;
    return *this;
}

Size& Size::operator-= (const Size& size)
{
    _width  -= size._width;
    _height -= size._height;
    return *this;
}

// -------------------------------------------------
// Rectangle

Rectangle::Rectangle(int x, int y, int width, int height)
    : _pos(x, y),
      _size(width, height)
{
}

Rectangle::Rectangle(int x, int y, const Size& size)
    : _pos(x, y),
      _size(size)
{
}

Rectangle::Rectangle(const Point& pos, int width, int height)
    : _pos(pos),
      _size(width, height)
{
}

Rectangle::Rectangle(const Point& pos, const Size& size)
    : _pos(pos),
      _size(size)
{
}

Rectangle::Rectangle(const Rectangle& rect)
    : _pos(rect._pos),
      _size(rect._size)
{
}

int Rectangle::getX() const
{
    return _pos.getX();
}

int Rectangle::getY() const
{
    return _pos.getY();
}

int Rectangle::getWidth() const
{
    return _size.getWidth();
}

int Rectangle::getHeight() const
{
    return _size.getHeight();
}

const Point& Rectangle::getPos() const
{
    return _pos;
}

const Size& Rectangle::getSize() const
{
    return _size;
}

bool Rectangle::contains(int x, int y) const
{
    return (_pos._x >= x && _pos._y >= y && _pos._x+_size._width <= x && _pos._y+_size._height <= y);
}

bool Rectangle::contains(const Point& pos) const
{
    return contains(pos._x, pos._y);
}

void Rectangle::setX(int x)
{
    _pos.setX(x);
}

void Rectangle::setY(int y)
{
    _pos.setY(y);
}

void Rectangle::setPos(int x, int y)
{
    _pos.setX(x);
    _pos.setY(y);
}

void Rectangle::setPos(const Point& pos)
{
    _pos = pos;
}

void Rectangle::setWidth(int width)
{
    _size.setWidth(width);
}

void Rectangle::setHeight(int height)
{
    _size.setHeight(height);
}

void Rectangle::setSize(int width, int height)
{
    _size.setWidth(width);
    _size.setHeight(height);
}

void Rectangle::setSize(const Size& size)
{
    _size = size;
}

Rectangle& Rectangle::operator= (const Rectangle& rect)
{
    _pos  = rect._pos;
    _size = rect._size;
    return *this;
}

Rectangle& Rectangle::operator+= (const Rectangle& rect)
{
    _pos  += rect._pos;
    _size += rect._size;
    return *this;
}

Rectangle& Rectangle::operator-= (const Rectangle& rect)
{
    _pos  -= rect._pos;
    _size -= rect._size;
    return *this;
}

// -------------------------------------------------

struct ImageSlider {
    uint32_t        paramIndex;
    ParameterRanges range;
    Point startPos, endPos;
    Size  size;
    Rectangle area;
    const char* imageData;
};

struct OpenGLExtUIPrivateData {
    uint32_t parameterCount;
    float*   paramValues;

    const char* bgImage;
    std::vector<ImageSlider> imageSliders;

    OpenGLExtUIPrivateData(uint32_t parameterCount)
        : paramValues(nullptr),
          bgImage(nullptr)
    {
        this->parameterCount = parameterCount;

        if (parameterCount > 0)
            paramValues = new float [parameterCount];
    }

    ~OpenGLExtUIPrivateData()
    {
        imageSliders.clear();

        if (paramValues)
            delete[] paramValues;
    }
};

// -------------------------------------------------

OpenGLExtUI::OpenGLExtUI(uint32_t parameterCount)
    : OpenGLUI(parameterCount)
{
    data = new OpenGLExtUIPrivateData(parameterCount);
}

OpenGLExtUI::~OpenGLExtUI()
{
    delete data;
}

// -------------------------------------------------
// UI Callbacks

void OpenGLExtUI::d_uiIdle()
{
    OpenGLUI::d_uiIdle();
}

// -------------------------------------------------
// Extended Calls

void OpenGLExtUI::setBackgroundImage(const char* imageData)
{
    assert(imageData);
    data->bgImage = imageData;
}

//void OpenGLExtUI::addImageKnob(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& pos, const char* imageData)
//{
//}

void OpenGLExtUI::addImageSlider(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& startPos, const Point& endPos, const Size& size, const char* imageData)
{
    assert(paramIndex < data->parameterCount);

    if (paramIndex >= data->parameterCount)
        return;

    Rectangle area(startPos.getX(), startPos.getY(), endPos.getX()+size.getWidth(), endPos.getY()/*+size.getHeight()*/);

    ImageSlider imageSlider = { paramIndex, paramRanges, startPos, endPos, size, area, imageData };
    data->imageSliders.push_back(imageSlider);

    data->paramValues[paramIndex] = paramRanges.def;
}

// -------------------------------------------------
// Implemented internally

void OpenGLExtUI::d_parameterChanged(uint32_t index, float value)
{
    if (index < data->parameterCount)
    {
        if (data->paramValues[index] != value)
            d_uiRepaint();

        data->paramValues[index] = value;
    }
}

void OpenGLExtUI::d_onInit()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, d_width(), d_height(), 0, 0, 1);
    glViewport(0, 0, d_width(), d_height());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLExtUI::d_onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // background image
    if (data->bgImage)
    {
        glRasterPos2i(0, d_height());
        glDrawPixels(d_width(), d_height(), GL_BGR, GL_UNSIGNED_BYTE, data->bgImage);
    }

    // image sliders
    if (data->imageSliders.size() > 0)
    {
        for (auto it = data->imageSliders.begin(); it != data->imageSliders.end(); it++)
        {
            const ImageSlider& imageSlider(*it);

            assert(imageSlider.paramIndex < data->parameterCount);

            if (imageSlider.paramIndex >= data->parameterCount)
                continue;

            float vper = (data->paramValues[imageSlider.paramIndex] - imageSlider.range.min) / (imageSlider.range.max - imageSlider.range.min);
            int x = imageSlider.startPos.getX() + float(imageSlider.endPos.getX()-imageSlider.startPos.getX())*vper;
            int y = imageSlider.startPos.getY() + float(imageSlider.endPos.getY()-imageSlider.startPos.getY())*vper;

            glRasterPos2i(x, y);
            glDrawPixels(imageSlider.size.getWidth(), imageSlider.size.getHeight(), GL_BGRA, GL_UNSIGNED_BYTE, imageSlider.imageData);
        }
    }

#if 0
    // knobs
    glRasterPos2i(66, 330);
    glDrawPixels(DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::knobData);

    glRasterPos2i(160, 330);
    glDrawPixels(DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight, GL_BGRA, GL_UNSIGNED_BYTE, DistrhoArtwork::knobData);
#endif
}

void OpenGLExtUI::d_onKeyboard(bool press, uint32_t key)
{
    (void)press;
    (void)key;
}

void OpenGLExtUI::d_onMotion(int x, int y)
{
    (void)x;
    (void)y;
}

void OpenGLExtUI::d_onMouse(int button, bool press, int x, int y)
{
    printf("Mouse %i %i %i %i\n", button, press, x, y);

    // image sliders
    if (data->imageSliders.size() > 0)
    {
        for (auto it = data->imageSliders.begin(); it != data->imageSliders.end(); it++)
        {
            const ImageSlider& imageSlider(*it);

            assert(imageSlider.paramIndex < data->parameterCount);

            if (imageSlider.paramIndex >= data->parameterCount)
                continue;

            if (imageSlider.area.contains(x, y))
            {
                printf("Mouse %i %i %i %i------ YES FOR %i\n", button, press, x, y, imageSlider.paramIndex);
            }
        }
    }

    (void)button;
    (void)press;
    (void)x;
    (void)y;
}

void OpenGLExtUI::d_onReshape(int width, int height)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLExtUI::d_onScroll(float dx, float dy)
{
    (void)dx;
    (void)dy;
}

void OpenGLExtUI::d_onSpecial(bool press, Key key)
{
    (void)press;
    (void)key;
}

void OpenGLExtUI::d_onClose()
{
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_OPENGL
