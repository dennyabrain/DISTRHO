/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_A301CBEF__
#define __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_A301CBEF__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "../ParamPreferences.h"

// forward declarations
class MasterAndCommander;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabPreferences  : public Component,
                        public TextEditorListener,
                        public ButtonListener,
                        public ComboBoxListener
{
public:
    //==============================================================================
    TabPreferences (MasterAndCommander *m);
    ~TabPreferences();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPreferences(const ParamPreferences & param);
    String getFileChooserResult(String dir);
    void textEditorTextChanged (TextEditor &editor);
    void textEditorReturnKeyPressed (TextEditor &editor);
    void textEditorEscapeKeyPressed (TextEditor &editor);
    void textEditorFocusLost (TextEditor &editor);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* directivity2_svg;
    static const int directivity2_svgSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    ParamPreferences paramPreferences;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponentHelp;
    Label* labelPreset;
    TextEditor* textEditorPreset;
    GroupComponent* groupComponentStrategy;
    ToggleButton* toggleButtonUniform;
    ToggleButton* toggleButtonLowest;
    Label* labelLatency;
    ComboBox* comboBoxLatency;
    TextEditor* textEditorHelp;
    TextButton* textButton;
    Label* label;
    Drawable* drawable1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabPreferences (const TabPreferences&);
    const TabPreferences& operator= (const TabPreferences&);
};


#endif   // __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_A301CBEF__
