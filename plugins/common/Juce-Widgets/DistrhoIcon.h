
#include "DistrhoIconArtwork.h"

class AboutWindow : public DocumentWindow
{
public:
    AboutWindow()
      : DocumentWindow("About Plugin", Colours::white, 0, false)
    {
        setDropShadowEnabled(false);
        setOpaque(true);
        setSize(300, 300);

        logo = ImageCache::getFromMemory (DistrhoIconArtwork::logo_png, DistrhoIconArtwork::logo_pngSize);
    }

    ~AboutWindow()
    {
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::black);

        g.drawImage (logo,
              30, 30, logo.getWidth(), logo.getHeight(),
              0, 0, logo.getWidth(), logo.getHeight(),
              false);

        g.setColour (Colours::white);
        g.setFont (18.0f);
        g.drawSingleLineText ("DISTRHO " JucePlugin_Name, 90, 50);

        g.setFont (15.0f);
#if JucePlugin_Build_AU
        g.drawSingleLineText ("AU Plugin Version", 90, 72);
#elif JucePlugin_Build_LV2
        g.drawSingleLineText ("LV2 Plugin Version", 90, 72);
#elif JucePlugin_Build_RTAS
        g.drawSingleLineText ("RTAS Plugin Version", 90, 72);
#elif JucePlugin_Build_VST
#if JucePlugin_IsSynth
        g.drawSingleLineText ("VSTi Plugin Version", 90, 72);
#else
        g.drawSingleLineText ("VST Plugin Version", 90, 72);
#endif
#elif JucePlugin_Build_Standalone
        g.drawSingleLineText ("Standalone Version", 90, 72);
#else
        g.drawSingleLineText ("Unknown Version", 90, 72);
#endif

        int posY = 130;
#if JucePlugin_Build_VST
        posY = 115;
#endif

        g.setFont (12.0f);
        g.drawMultiLineText (CharPointer_UTF8(""
            "Plugin developed by falkTX,\n"
            "Artwork by nieee.\n"
            "\n"
            "May use portions of code by Patrick Kunz (TAL-Plugins) and Michael Gruhn (LOSER-Development).\n"
            "Heavily based on the Juce toolkit.\n"
            "\n"
            "Many thanks to Ant\u00f3nio Saraiva, Colin Barry, David Robillard, Jules, Patrick Kunz and the Linux audio community.\n"
#if JucePlugin_Build_VST
            "\n"
            "VST is a trademark of Steinberg Media Technologies GmbH. VST Plug-In Technology by Steinberg.\n"
#endif
            ""), 25, posY, 250);
    }

    void quit()
    {
        removeFromDesktop();
        exitModalState(0);
    }

    void userTriedToCloseWindow()
    {
        quit();
    }

    bool keyPressed (const KeyPress& key)
    {
        quit();
        return true;
    }

    void mouseDown (const MouseEvent& e)
    {
        quit();
    }

private:
    Image logo;
};

class DistrhoIcon : public Button
{
public:
    enum IconColour {
        ICON_LIGHT,
        ICON_DARK
    };

    DistrhoIcon(IconColour colour_)
      : Button("DistrhoIcon"),
        colour(colour_)
    {
        if (colour == ICON_LIGHT)
        {
            bNormal = ImageCache::getFromMemory (DistrhoIconArtwork::aboutnormal_light_png, DistrhoIconArtwork::aboutnormal_light_pngSize);
            bHover  = ImageCache::getFromMemory (DistrhoIconArtwork::abouthover_light_png,  DistrhoIconArtwork::abouthover_light_pngSize);
        }
        else
        {
            bNormal = ImageCache::getFromMemory (DistrhoIconArtwork::aboutnormal_dark_png, DistrhoIconArtwork::aboutnormal_dark_pngSize);
            bHover  = ImageCache::getFromMemory (DistrhoIconArtwork::abouthover_dark_png,  DistrhoIconArtwork::abouthover_dark_pngSize);
        }

        bWidth  = bNormal.getWidth();
        bHeight = bNormal.getHeight();

        aboutDialog = new AboutWindow();

        setSize(bWidth, bHeight);
    }

    ~DistrhoIcon()
    {
        delete aboutDialog;
    }

    void paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
    {
        g.drawImage(isMouseOverButton ? bHover : bNormal,
              0, 0, bWidth, bHeight,
              0, 0, bWidth, bHeight,
              false);
    }

    void clicked()
    {
        Point<int> pos = getPosition();

        if (colour == ICON_LIGHT)
            aboutDialog->setTopLeftPosition(getScreenX()-200, getScreenY()-250);
        else
            aboutDialog->setTopLeftPosition(getScreenX(), getScreenY()-100);

        aboutDialog->addToDesktop();
        aboutDialog->enterModalState(true);
    }

private:
    IconColour colour;
    Image bNormal;
    Image bHover;
    AboutWindow* aboutDialog;

    int bWidth, bHeight;
};
