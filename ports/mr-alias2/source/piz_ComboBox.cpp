/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "piz_ComboBox.h"
#include "piz_LookAndFeel.h"

//==============================================================================
PizComboBox::PizComboBox (const String& name)
    : Component (name),
      items (4),
      currentIndex (-1),
      isButtonDown (false),
      separatorPending (false),
      menuActive (false),
      listeners (2),
      label (0)
{
    noChoicesMessage = TRANS("(no choices)");
    setRepaintsOnMouseActivity (true);

    lookAndFeelChanged();
}

PizComboBox::~PizComboBox()
{
    if (menuActive)
        PopupMenu::dismissAllActiveMenus();

    deleteAllChildren();
}

//==============================================================================
void PizComboBox::setEditableText (const bool isEditable)
{
    label->setEditable (isEditable, isEditable, false);

    setWantsKeyboardFocus (! isEditable);
    resized();
}

bool PizComboBox::isTextEditable() const throw()
{
    return label->isEditable();
}

void PizComboBox::setJustificationType (const Justification& justification) throw()
{
    label->setJustificationType (justification);
}

const Justification PizComboBox::getJustificationType() const throw()
{
    return label->getJustificationType();
}

void PizComboBox::setTooltip (const String& newTooltip)
{
    SettableTooltipClient::setTooltip (newTooltip);
    label->setTooltip (newTooltip);
}

//==============================================================================
void PizComboBox::addItem (const String& newItemText,
                        const int newItemId) throw()
{
    // you can't add empty strings to the list..
    jassert (newItemText.isNotEmpty());

    // IDs must be non-zero, as zero is used to indicate a lack of selecion.
    jassert (newItemId != 0);

    // you shouldn't use duplicate item IDs!
    jassert (getItemForId (newItemId) == 0);

    if (newItemText.isNotEmpty() && newItemId != 0)
    {
        if (separatorPending)
        {
            separatorPending = false;

            ItemInfo* const item = new ItemInfo();
            item->itemId = 0;
            item->isEnabled = false;
            item->isHeading = false;
            items.add (item);
        }

        ItemInfo* const item = new ItemInfo();
        item->name = newItemText;
        item->itemId = newItemId;
        item->isEnabled = true;
        item->isHeading = false;
        items.add (item);
    }
}

void PizComboBox::addSeparator() throw()
{
    separatorPending = (items.size() > 0);
}

void PizComboBox::addSectionHeading (const String& headingName) throw()
{
    // you can't add empty strings to the list..
    jassert (headingName.isNotEmpty());

    if (headingName.isNotEmpty())
    {
        if (separatorPending)
        {
            separatorPending = false;

            ItemInfo* const item = new ItemInfo();
            item->itemId = 0;
            item->isEnabled = false;
            item->isHeading = false;
            items.add (item);
        }

        ItemInfo* const item = new ItemInfo();
        item->name = headingName;
        item->itemId = 0;
        item->isEnabled = true;
        item->isHeading = true;
        items.add (item);
    }
}

void PizComboBox::setItemEnabled (const int itemId,
                               const bool isEnabled) throw()
{
    ItemInfo* const item = getItemForId (itemId);

    if (item != 0)
        item->isEnabled = isEnabled;
}

void PizComboBox::changeItemText (const int itemId,
                               const String& newText) throw()
{
    ItemInfo* const item = getItemForId (itemId);

    jassert (item != 0);

    if (item != 0)
        item->name = newText;
}

void PizComboBox::clear (const bool dontSendChangeMessage)
{
    items.clear();
    separatorPending = false;

    if (! label->isEditable())
        setSelectedItemIndex (-1, dontSendChangeMessage);
}

//==============================================================================
PizComboBox::ItemInfo* PizComboBox::getItemForId (const int itemId) const throw()
{
    jassert (itemId != 0);

    if (itemId != 0)
    {
        for (int i = items.size(); --i >= 0;)
            if (items.getUnchecked(i)->itemId == itemId)
                return items.getUnchecked(i);
    }

    return 0;
}

PizComboBox::ItemInfo* PizComboBox::getItemForIndex (const int index) const throw()
{
    int n = 0;

    for (int i = 0; i < items.size(); ++i)
    {
        ItemInfo* const item = items.getUnchecked(i);

        if (item->isRealItem())
        {
            if (n++ == index)
                return item;
        }
    }

    return 0;
}

int PizComboBox::getNumItems() const throw()
{
    int n = 0;

    for (int i = items.size(); --i >= 0;)
    {
        ItemInfo* const item = items.getUnchecked(i);

        if (item->isRealItem())
            ++n;
    }

    return n;
}

const String PizComboBox::getItemText (const int index) const throw()
{
    ItemInfo* const item = getItemForIndex (index);

    if (item != 0)
        return item->name;

    return String::empty;
}

int PizComboBox::getItemId (const int index) const throw()
{
    ItemInfo* const item = getItemForIndex (index);

    return (item != 0) ? item->itemId : 0;
}


//==============================================================================
bool PizComboBox::ItemInfo::isSeparator() const throw()
{
    return name.isEmpty();
}

bool PizComboBox::ItemInfo::isRealItem() const throw()
{
    return ! (isHeading || name.isEmpty());
}

//==============================================================================
int PizComboBox::getSelectedItemIndex() const throw()
{
    return (currentIndex >= 0 && getText() == getItemText (currentIndex))
                ? currentIndex
                : -1;
}

void PizComboBox::setSelectedItemIndex (const int index,
                                     const bool dontSendChangeMessage) throw()
{
    if (currentIndex != index || label->getText() != getItemText (currentIndex))
    {
        if (((unsigned int) index) < (unsigned int) getNumItems())
            currentIndex = index;
        else
            currentIndex = -1;

        label->setText (getItemText (currentIndex), false);

        if (! dontSendChangeMessage)
            triggerAsyncUpdate();
    }
}

void PizComboBox::setSelectedId (const int newItemId,
                              const bool dontSendChangeMessage) throw()
{
    for (int i = getNumItems(); --i >= 0;)
    {
        if (getItemId(i) == newItemId)
        {
            setSelectedItemIndex (i, dontSendChangeMessage);
            break;
        }
    }
}

int PizComboBox::getSelectedId() const throw()
{
    const ItemInfo* const item = getItemForIndex (currentIndex);

    return (item != 0 && getText() == item->name)
                ? item->itemId
                : 0;
}

//==============================================================================
void PizComboBox::addListener (PizComboBoxListener* const listener) throw()
{
    jassert (listener != 0);
    if (listener != 0)
        listeners.add (listener);
}

void PizComboBox::removeListener (PizComboBoxListener* const listener) throw()
{
    listeners.removeValue (listener);
}

void PizComboBox::handleAsyncUpdate()
{
    for (int i = listeners.size(); --i >= 0;)
    {
        ((PizComboBoxListener*) listeners.getUnchecked (i))->comboBoxChanged ((ComboBox*)this);
        i = jmin (i, listeners.size());
    }
}

//==============================================================================
const String PizComboBox::getText() const throw()
{
    return label->getText();
}

void PizComboBox::setText (const String& newText,
                        const bool dontSendChangeMessage) throw()
{
    for (int i = items.size(); --i >= 0;)
    {
        ItemInfo* const item = items.getUnchecked(i);

        if (item->isRealItem()
             && item->name == newText)
        {
            setSelectedId (item->itemId, dontSendChangeMessage);
            return;
        }
    }

    currentIndex = -1;

    if (label->getText() != newText)
    {
        label->setText (newText, false);

        if (! dontSendChangeMessage)
            triggerAsyncUpdate();
    }

    repaint();
}

void PizComboBox::showEditor()
{
    jassert (isTextEditable()); // you probably shouldn't do this to a non-editable combo box?

    label->showEditor();
}

//==============================================================================
void PizComboBox::setTextWhenNothingSelected (const String& newMessage) throw()
{
    textWhenNothingSelected = newMessage;
    repaint();
}

const String PizComboBox::getTextWhenNothingSelected() const throw()
{
    return textWhenNothingSelected;
}

void PizComboBox::setTextWhenNoChoicesAvailable (const String& newMessage) throw()
{
    noChoicesMessage = newMessage;
}

const String PizComboBox::getTextWhenNoChoicesAvailable() const throw()
{
    return noChoicesMessage;
}

//==============================================================================
void PizComboBox::paint (Graphics& g)
{
    getLookAndFeel().drawComboBox (g,
                                   getWidth(),
                                   getHeight(),
                                   isButtonDown,
                                   label->getRight(),
                                   0,
                                   getWidth() - label->getRight(),
                                   getHeight(),
                                   (ComboBox&)*this);

    if (textWhenNothingSelected.isNotEmpty()
        && label->getText().isEmpty()
        && ! label->isBeingEdited())
    {
        g.setColour (findColour (textColourId).withMultipliedAlpha (0.5f));
        g.setFont (label->getFont());
        g.drawFittedText (textWhenNothingSelected,
                          label->getX() + 2, label->getY() + 1,
                          label->getWidth() - 4, label->getHeight() - 2,
                          label->getJustificationType(),
                          jmax (1, (int) (label->getHeight() / label->getFont().getHeight())));
    }
}

void PizComboBox::resized()
{
    if (getHeight() > 0 && getWidth() > 0)
        getLookAndFeel().positionComboBoxText ((ComboBox&)*this, *label);
}

void PizComboBox::enablementChanged()
{
    repaint();
}

void PizComboBox::lookAndFeelChanged()
{
    repaint();

    Label* const newLabel = getLookAndFeel().createComboBoxTextBox ((ComboBox&)*this);

    if (label != 0)
    {
        newLabel->setEditable (label->isEditable());
        newLabel->setJustificationType (label->getJustificationType());
        newLabel->setTooltip (label->getTooltip());
        newLabel->setText (label->getText(), false);
    }

    delete label;
    label = newLabel;

    addAndMakeVisible (newLabel);

    newLabel->addListener (this);
    newLabel->addMouseListener (this, false);

    newLabel->setColour (Label::backgroundColourId, Colours::transparentBlack);
    newLabel->setColour (Label::textColourId, findColour (PizComboBox::textColourId));

    newLabel->setColour (TextEditor::textColourId, findColour (PizComboBox::textColourId));
    newLabel->setColour (TextEditor::backgroundColourId, Colours::transparentBlack);
    newLabel->setColour (TextEditor::highlightColourId, findColour (TextEditor::highlightColourId));
    newLabel->setColour (TextEditor::outlineColourId, Colours::transparentBlack);

    resized();
}

void PizComboBox::colourChanged()
{
    lookAndFeelChanged();
}

//==============================================================================
bool PizComboBox::keyPressed (const KeyPress& key)
{
    bool used = false;

    if (key.isKeyCode (KeyPress::upKey)
        || key.isKeyCode (KeyPress::leftKey))
    {
        setSelectedItemIndex (jmax (0, currentIndex - 1));
        used = true;
    }
    else if (key.isKeyCode (KeyPress::downKey)
              || key.isKeyCode (KeyPress::rightKey))
    {
        setSelectedItemIndex (jmin (currentIndex + 1, getNumItems() - 1));
        used = true;
    }
    else if (key.isKeyCode (KeyPress::returnKey))
    {
        showPopup();
        used = true;
    }

    return used;
}

bool PizComboBox::keyStateChanged (const bool isKeyDown)
{
    // only forward key events that aren't used by this component
    return isKeyDown
            && (KeyPress::isKeyCurrentlyDown (KeyPress::upKey)
                || KeyPress::isKeyCurrentlyDown (KeyPress::leftKey)
                || KeyPress::isKeyCurrentlyDown (KeyPress::downKey)
                || KeyPress::isKeyCurrentlyDown (KeyPress::rightKey));
}

//==============================================================================
void PizComboBox::focusGained (FocusChangeType)
{
    repaint();
}

void PizComboBox::focusLost (FocusChangeType)
{
    repaint();
}

//==============================================================================
void PizComboBox::labelTextChanged (Label*)
{
    triggerAsyncUpdate();
}


//==============================================================================
void PizComboBox::showPopup()
{
    if (! menuActive)
    {
        const int currentId = getSelectedId();
        ComponentDeletionWatcher deletionWatcher (this);

        PopupMenu menu;

        menu.setLookAndFeel (&getLookAndFeel());

        for (int i = 0; i < items.size(); ++i)
        {
            const ItemInfo* const item = items.getUnchecked(i);

            if (item->isSeparator())
                menu.addSeparator();
            else if (item->isHeading)
                menu.addSectionHeader (item->name);
            else
                menu.addItem (item->itemId, item->name,
                              item->isEnabled, item->itemId == currentId);
        }

        if (items.size() == 0)
            menu.addItem (1, noChoicesMessage, false);

        const int itemHeight = jlimit (12, 24, getHeight());

        menuActive = true;
        const int resultId = menu.showAt (this, currentId,
                                          getWidth(), 0, itemHeight);

        if (deletionWatcher.hasBeenDeleted())
            return;

        menuActive = false;

        if (resultId != 0)
            setSelectedId (resultId);
    }
}

//==============================================================================
void PizComboBox::mouseDown (const MouseEvent& e)
{
    beginDragAutoRepeat (300);

    isButtonDown = isEnabled();

    if (isButtonDown
         && (e.eventComponent == this || ! label->isEditable()))
    {
        showPopup();
    }
}

void PizComboBox::mouseDrag (const MouseEvent& e)
{
    beginDragAutoRepeat (50);

    if (isButtonDown && ! e.mouseWasClicked())
        showPopup();
}

void PizComboBox::mouseUp (const MouseEvent& e2)
{
    if (isButtonDown)
    {
        isButtonDown = false;
        repaint();

        const MouseEvent e (e2.getEventRelativeTo (this));

        if (reallyContains (e.x, e.y, true)
             && (e2.eventComponent == this || ! label->isEditable()))
        {
            showPopup();
        }
    }
}

