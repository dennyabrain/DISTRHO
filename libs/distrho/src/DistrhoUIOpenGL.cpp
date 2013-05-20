/*
 * DISTRHO Plugin Toolkit (DPT)
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the LGPL.txt file
 */

#include "DistrhoUIInternal.hpp"

START_NAMESPACE_DGL
extern Window* dgl_lastUiParent;
END_NAMESPACE_DGL

START_NAMESPACE_DISTRHO

// -------------------------------------------------
// OpenGL UI

OpenGLUI::OpenGLUI()
    : UI(),
      Widget(dgl_lastUiParent)
{
    assert(dgl_lastUiParent != nullptr);

    dgl_lastUiParent = nullptr;
}

OpenGLUI::~OpenGLUI()
{
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO
