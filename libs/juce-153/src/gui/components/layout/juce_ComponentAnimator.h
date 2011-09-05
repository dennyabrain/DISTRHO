/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_COMPONENTANIMATOR_JUCEHEADER__
#define __JUCE_COMPONENTANIMATOR_JUCEHEADER__

#include "../juce_Component.h"
#include "../../../events/juce_ChangeBroadcaster.h"
#include "../../../events/juce_Timer.h"


//==============================================================================
/**
    Animates a set of components, moving them to a new position and/or fading their
    alpha levels.

    To animate a component, create a ComponentAnimator instance or (preferably) use the
    global animator object provided by Desktop::getAnimator(), and call its animateComponent()
    method to commence the movement.

    If you're using your own ComponentAnimator instance, you'll need to make sure it isn't
    deleted before it finishes moving the components, or they'll be abandoned before reaching their
    destinations.

    It's ok to delete components while they're being animated - the animator will detect this
    and safely stop using them.

    The class is a ChangeBroadcaster and sends a notification when any components
    start or finish being animated.

    @see Desktop::getAnimator
*/
class JUCE_API  ComponentAnimator  : public ChangeBroadcaster,
                                     private Timer
{
public:
    //==============================================================================
    /** Creates a ComponentAnimator. */
    ComponentAnimator();

    /** Destructor. */
    ~ComponentAnimator();

    //==============================================================================
    /** Starts a component moving from its current position to a specified position.

        If the component is already in the middle of an animation, that will be abandoned,
        and a new animation will begin, moving the component from its current location.

        The start and end speed parameters let you apply some acceleration to the component's
        movement.

        @param component            the component to move
        @param finalBounds          the destination bounds to which the component should move. To leave the
                                    component in the same place, just pass component->getBounds() for this value
        @param finalAlpha           the alpha value that the component should have at the end of the animation
        @param animationDurationMilliseconds    how long the animation should last, in milliseconds
        @param useProxyComponent    if true, this means the component should be replaced by an internally
                                    managed temporary component which is a snapshot of the original component.
                                    This avoids the component having to paint itself as it moves, so may
                                    be more efficient. This option also allows you to delete the original
                                    component immediately after starting the animation, because the animation
                                    can proceed without it. If you use a proxy, the original component will be
                                    made invisible by this call, and then will become visible again at the end
                                    of the animation. It'll also mean that the proxy component will be temporarily
                                    added to the component's parent, so avoid it if this might confuse the parent
                                    component, or if there's a chance the parent might decide to delete its children.
        @param startSpeed           a value to indicate the relative start speed of the animation. If this is 0,
                                    the component will start by accelerating from rest; higher values mean that it
                                    will have an initial speed greater than zero. If the value if greater than 1, it
                                    will decelerate towards the middle of its journey. To move the component at a
                                    constant rate for its entire animation, set both the start and end speeds to 1.0
        @param endSpeed             a relative speed at which the component should be moving when the animation finishes.
                                    If this is 0, the component will decelerate to a standstill at its final position;
                                    higher values mean the component will still be moving when it stops. To move the component
                                    at a constant rate for its entire animation, set both the start and end speeds to 1.0
    */
    void animateComponent (Component* component,
                           const Rectangle<int>& finalBounds,
                           float finalAlpha,
                           int animationDurationMilliseconds,
                           bool useProxyComponent,
                           double startSpeed,
                           double endSpeed);

    /** Begins a fade-out of this components alpha level.
        This is a quick way of invoking animateComponent() with a target alpha value of 0.0f, using
        a proxy. You're safe to delete the component after calling this method, and this won't
        interfere with the animation's progress.
    */
    void fadeOut (Component* component, int millisecondsToTake);

    /** Begins a fade-in of a component.
        This is a quick way of invoking animateComponent() with a target alpha value of 1.0f.
    */
    void fadeIn (Component* component, int millisecondsToTake);

    /** Stops a component if it's currently being animated.

        If moveComponentToItsFinalPosition is true, then the component will
        be immediately moved to its destination position and size. If false, it will be
        left in whatever location it currently occupies.
    */
    void cancelAnimation (Component* component,
                          bool moveComponentToItsFinalPosition);

    /** Clears all of the active animations.

        If moveComponentsToTheirFinalPositions is true, all the components will
        be immediately set to their final positions. If false, they will be
        left in whatever locations they currently occupy.
    */
    void cancelAllAnimations (bool moveComponentsToTheirFinalPositions);

    /** Returns the destination position for a component.

        If the component is being animated, this will return the target position that
        was specified when animateComponent() was called.

        If the specified component isn't currently being animated, this method will just
        return its current position.
    */
    const Rectangle<int> getComponentDestination (Component* component);

    /** Returns true if the specified component is currently being animated. */
    bool isAnimating (Component* component) const;

private:
    //==============================================================================
    class AnimationTask;
    OwnedArray <AnimationTask> tasks;
    uint32 lastTime;

    AnimationTask* findTaskFor (Component* component) const;
    void timerCallback();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentAnimator);
};


#endif   // __JUCE_COMPONENTANIMATOR_JUCEHEADER__
