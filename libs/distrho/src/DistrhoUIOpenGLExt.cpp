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
#include <cmath>
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
    return (x >= _pos._x && y >= _pos._y && x <= _pos._x+_size._width && y <= _pos._y+_size._height);
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

struct ImageKnob {
    uint32_t        paramIndex;
    ParameterRanges range;
    Point pos;
    Size  size;
    Rectangle area;
    const char* imageData;
};

struct ImageVerticalSlider {
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

    int32_t curMouseParam;
    int initialPosX;
    int initialPosY;

    const char* bgImage;
    std::vector<ImageKnob> imageKnobs;
    std::vector<ImageVerticalSlider> imageSliders;


    OpenGLExtUIPrivateData(uint32_t parameterCount)
        : paramValues(nullptr),
          curMouseParam(-1),
          initialPosX(0),
          initialPosY(0),
          bgImage(nullptr)
    {
        this->parameterCount = parameterCount;

        if (parameterCount > 0)
            paramValues = new float [parameterCount];
    }

    ~OpenGLExtUIPrivateData()
    {
        imageKnobs.clear();
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

void OpenGLExtUI::setParameterValue(uint32_t index, float value)
{
    d_parameterChanged(index, value);
}

void OpenGLExtUI::setBackgroundImage(const char* imageData)
{
    assert(imageData);
    data->bgImage = imageData;
}

void OpenGLExtUI::addImageKnob(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& pos, const Size& size, const char* imageData)
{
    assert(paramIndex < data->parameterCount);
    assert(imageData);

    if (paramIndex >= data->parameterCount || ! imageData)
        return;

    int imageSize = size.getWidth() < size.getHeight() ? size.getWidth() : size.getHeight();

    Rectangle area(pos, size);
    area.setY(pos.getY() - imageSize);

    ImageKnob imageKnob = { paramIndex, paramRanges, pos, size, area, imageData };
    data->imageKnobs.push_back(imageKnob);

    data->paramValues[paramIndex] = paramRanges.def;
}

void OpenGLExtUI::addImageVerticalSlider(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& startPos, const Point& endPos, const Size& size, const char* imageData)
{
    assert(paramIndex < data->parameterCount);
    assert(imageData);

    if (paramIndex >= data->parameterCount || ! imageData)
        return;

    Rectangle area(startPos.getX(), startPos.getY() - size.getHeight()/2, size.getWidth(), endPos.getY() - startPos.getY());

    ImageVerticalSlider imageSlider = { paramIndex, paramRanges, startPos, endPos, size, area, imageData };
    data->imageSliders.push_back(imageSlider);

    data->paramValues[paramIndex] = paramRanges.def;
}

// -------------------------------------------------
// Implemented internally

void OpenGLExtUI::d_parameterChanged(uint32_t index, float value)
{
    if (index >= data->parameterCount)
        return;

    if (data->paramValues[index] == value)
        return;

    data->paramValues[index] = value;

    d_uiRepaint();
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

    // image knobs
    if (data->imageKnobs.size() > 0)
    {
        for (auto it = data->imageKnobs.begin(); it != data->imageKnobs.end(); it++)
        {
            const ImageKnob& imageKnob(*it);

            assert(imageKnob.paramIndex < data->parameterCount);

            if (imageKnob.paramIndex >= data->parameterCount)
                continue;

            float vper = (data->paramValues[imageKnob.paramIndex] - imageKnob.range.min) / (imageKnob.range.max - imageKnob.range.min);

            int layers, imageSize;

            if (imageKnob.size.getWidth() > imageKnob.size.getHeight())
            {
                layers    = imageKnob.size.getWidth() / imageKnob.size.getHeight();
                imageSize = imageKnob.size.getHeight();
            }
            else
            {
                layers    = imageKnob.size.getHeight() / imageKnob.size.getWidth();
                imageSize = imageKnob.size.getWidth();
            }

            int layerSize = imageSize * imageSize * 4;
            int imageDataSize   = layerSize * layers;
            int imageDataOffset = imageDataSize - layerSize - layerSize * rint(vper*(layers-1));

            glRasterPos2i(imageKnob.pos.getX(), imageKnob.pos.getY());
            glDrawPixels(imageSize, imageSize, GL_BGRA, GL_UNSIGNED_BYTE, imageKnob.imageData + imageDataOffset);
        }
    }

    // image sliders
    if (data->imageSliders.size() > 0)
    {
        for (auto it = data->imageSliders.begin(); it != data->imageSliders.end(); it++)
        {
            const ImageVerticalSlider& imageSlider(*it);

            assert(imageSlider.paramIndex < data->parameterCount);

            if (imageSlider.paramIndex >= data->parameterCount)
                continue;

            float vper = (data->paramValues[imageSlider.paramIndex] - imageSlider.range.min) / (imageSlider.range.max - imageSlider.range.min);
            int x = imageSlider.startPos.getX() + rint(float(imageSlider.endPos.getX() - imageSlider.startPos.getX()) * vper);
            int y = imageSlider.startPos.getY() + rint(float(imageSlider.endPos.getY() - imageSlider.startPos.getY()) * vper);

            glRasterPos2i(x, y);
            glDrawPixels(imageSlider.size.getWidth(), imageSlider.size.getHeight(), GL_BGRA, GL_UNSIGNED_BYTE, imageSlider.imageData);
        }
    }
}

void OpenGLExtUI::d_onKeyboard(bool press, uint32_t key)
{
    (void)press;
    (void)key;
}

void OpenGLExtUI::d_onMotion(int x, int y)
{
    if (data->curMouseParam <= -1)
        return;

    // image knobs
    if (data->imageKnobs.size() > 0)
    {
        for (auto it = data->imageKnobs.begin(); it != data->imageKnobs.end(); it++)
        {
            const ImageKnob& imageKnob(*it);

            if (int32_t(imageKnob.paramIndex) != data->curMouseParam)
                continue;

            //int movX = x - data->initialPosX;
            int movY = data->initialPosY - y;

            //if (movX != 0)
            //{
            //    float oldValue = data->paramValues[imageKnob.paramIndex];
            //    float newValue = oldValue + imageKnob.range.step * movX;
            //    imageKnob.range.fixRange(newValue);

            //    if (oldValue != newValue)
            //    {
            //        d_parameterChanged(imageKnob.paramIndex, newValue);
            //        d_setParameterValue(imageKnob.paramIndex, newValue);
            //    }
            //}

            if (movY != 0)
            {
                float oldValue = data->paramValues[imageKnob.paramIndex];
                float newValue = oldValue + imageKnob.range.step * movY;
                imageKnob.range.fixRange(newValue);

                if (oldValue != newValue)
                {
                    d_parameterChanged(imageKnob.paramIndex, newValue);
                    d_setParameterValue(imageKnob.paramIndex, newValue);
                }
            }

            data->initialPosX = x;
            data->initialPosY = y;

            return;
        }
    }

    // image sliders
    if (data->imageSliders.size() > 0)
    {
        for (auto it = data->imageSliders.begin(); it != data->imageSliders.end(); it++)
        {
            const ImageVerticalSlider& imageSlider(*it);

            if (int32_t(imageSlider.paramIndex) != data->curMouseParam)
                continue;

            if (imageSlider.area.contains(x, y))
            {
                data->curMouseParam = imageSlider.paramIndex;

                float vper  = float(y - imageSlider.area.getY()) / imageSlider.area.getHeight();
                float value = imageSlider.range.min + vper * (imageSlider.range.max - imageSlider.range.min);
                imageSlider.range.fixRange(value);

                d_parameterChanged(imageSlider.paramIndex, value);
                d_setParameterValue(imageSlider.paramIndex, value);
            }
            else if (y < imageSlider.area.getY())
            {
                if (data->paramValues[imageSlider.paramIndex] != imageSlider.range.min)
                {
                    d_parameterChanged(imageSlider.paramIndex, imageSlider.range.min);
                    d_setParameterValue(imageSlider.paramIndex, imageSlider.range.min);
                }
            }
            else
            {
                if (data->paramValues[imageSlider.paramIndex] != imageSlider.range.max)
                {
                    d_parameterChanged(imageSlider.paramIndex, imageSlider.range.max);
                    d_setParameterValue(imageSlider.paramIndex, imageSlider.range.max);
                }
            }

            return;
        }
    }
}

void OpenGLExtUI::d_onMouse(int button, bool press, int x, int y)
{
    if (button != 1)
        return;

    if (data->curMouseParam >= 0 && ! press)
    {
        data->curMouseParam = -1;
        return;
    }

    if (! press)
        return;

    // image knobs
    if (data->imageKnobs.size() > 0)
    {
        for (auto it = data->imageKnobs.begin(); it != data->imageKnobs.end(); it++)
        {
            const ImageKnob& imageKnob(*it);

            assert(imageKnob.paramIndex < data->parameterCount);

            if (imageKnob.paramIndex >= data->parameterCount)
                continue;

            if (imageKnob.area.contains(x, y))
            {
                data->curMouseParam = imageKnob.paramIndex;
                data->initialPosX   = x;
                data->initialPosY   = y;
                return;
            }
        }
    }

    // image sliders
    if (data->imageSliders.size() > 0)
    {
        for (auto it = data->imageSliders.begin(); it != data->imageSliders.end(); it++)
        {
            const ImageVerticalSlider& imageSlider(*it);

            assert(imageSlider.paramIndex < data->parameterCount);

            if (imageSlider.paramIndex >= data->parameterCount)
                continue;

            if (imageSlider.area.contains(x, y))
            {
                data->curMouseParam = imageSlider.paramIndex;
                data->initialPosX   = x;
                data->initialPosY   = y;

                float vper  = float(y - imageSlider.area.getY()) / imageSlider.area.getHeight();
                float value = imageSlider.range.min + vper * (imageSlider.range.max - imageSlider.range.min);
                imageSlider.range.fixRange(value);

                d_parameterChanged(imageSlider.paramIndex, value);
                d_setParameterValue(imageSlider.paramIndex, value);

                return;
            }
        }
    }
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
