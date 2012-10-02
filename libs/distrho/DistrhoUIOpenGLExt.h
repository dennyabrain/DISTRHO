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

#ifndef __DISTRHO_UI_OPENGL_EXT_H__
#define __DISTRHO_UI_OPENGL_EXT_H__

#include "src/DistrhoDefines.h"

#ifdef DISTRHO_UI_OPENGL

#include "DistrhoUIOpenGL.h"
#include "DistrhoPlugin.h"

START_NAMESPACE_DISTRHO

// -------------------------------------------------

class Point
{
public:
    Point(int x, int y);
    Point(const Point& pos);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    Point& operator= (const Point& pos);
    Point& operator+= (const Point& pos);
    Point& operator-= (const Point& pos);

private:
    int _x, _y;
    friend class Rectangle;
};

class Size
{
public:
    Size(int width, int height);
    Size(const Size& size);

    int getWidth() const;
    int getHeight() const;

    void setWidth(int width);
    void setHeight(int height);

    Size& operator= (const Size& size);
    Size& operator+= (const Size& size);
    Size& operator-= (const Size& size);

private:
    int _width, _height;
    friend class Rectangle;
};

class Rectangle
{
public:
    Rectangle(int x, int y, int width, int height);
    Rectangle(int x, int y, const Size& size);
    Rectangle(const Point& pos, int width, int height);
    Rectangle(const Point& pos, const Size& size);
    Rectangle(const Rectangle& rect);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    const Point& getPos() const;
    const Size&  getSize() const;

    bool contains(int x, int y) const;
    bool contains(const Point& pos) const;

    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    void setPos(const Point& pos);

    void setWidth(int width);
    void setHeight(int height);
    void setSize(int width, int height);
    void setSize(const Size& size);

    Rectangle& operator= (const Rectangle& rect);
    Rectangle& operator+= (const Rectangle& rect);
    Rectangle& operator-= (const Rectangle& rect);

private:
    Point _pos;
    Size  _size;
};

// -------------------------------------------------

struct OpenGLExtUIPrivateData;

class OpenGLExtUI : public OpenGLUI
{
public:
    OpenGLExtUI(uint32_t parameterCount);
    virtual ~OpenGLExtUI();

    // ---------------------------------------------

protected:
    // Information
    virtual const char*  d_title() = 0;
    virtual unsigned int d_width() = 0;
    virtual unsigned int d_height() = 0;

    // DSP Callbacks
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    virtual void d_programChanged(uint32_t index) = 0;
#endif
#if DISTRHO_PLUGIN_WANT_STATE
    virtual void d_stateChanged(const char* key, const char* value) = 0;
#endif

    // UI Callbacks
    virtual void d_uiIdle();

    // Extended Calls
    void setBackgroundImage(const char* imageData);
    //void addImageKnob(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& pos, const char* imageData);
    void addImageSlider(uint32_t paramIndex, const ParameterRanges& paramRanges, const Point& startPos, const Point& endPos, const Size& size, const char* imageData);

private:
    OpenGLExtUIPrivateData* data;

    // Implemented internally
    void d_parameterChanged(uint32_t index, float value);
    void d_onInit();
    void d_onDisplay();
    void d_onKeyboard(bool press, uint32_t key);
    void d_onMotion(int x, int y);
    void d_onMouse(int button, bool press, int x, int y);
    void d_onReshape(int width, int height);
    void d_onScroll(float dx, float dy);
    void d_onSpecial(bool press, Key key);
    void d_onClose();
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_OPENGL

#endif // __DISTRHO_UI_OPENGL_EXT_H__
