# C++ Console Executable Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`

ifndef CONFIG
  CONFIG=Release
endif

# if multiple archs are defined turn off automated dependency generation
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Release)
  BINDIR := ../../../bin
  LIBDIR := ../../../bin
  OBJDIR := intermediate/Release
  OUTDIR := ../../../bin
  CPPFLAGS := $(DEPFLAGS) -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=0" -D "JucePlugin_Build_Standalone=1" -D "LINUX=1" -D "NDEBUG=1" -I "../source" -I "../../../libs/juce-153/standalone" -I "../../../libs/juce-153/source"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3 `pkg-config --cflags freetype2` -O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -s `pkg-config --libs freetype2` -L"../../../libs" -lfreetype -lpthread -lasound -ldl -lrt -lX11 -lXext -ljuce-standalone-153
  LDDEPS :=
  RESFLAGS := -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=0" -D "JucePlugin_Build_Standalone=1" -D "LINUX=1" -D "NDEBUG=1" -I "../source" -I "../../../libs/juce-153/standalone" -I "../../../libs/juce-153/source"
  TARGET := ThePilgrim
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Debug)
  BINDIR := ../../../bin
  LIBDIR := ../../../bin
  OBJDIR := intermediate/Debug
  OUTDIR := ../../../bin
  CPPFLAGS := $(DEPFLAGS) -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=0" -D "JucePlugin_Build_Standalone=1" -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -I "../source" -I "../../../libs/juce-153/standalone" -I "../../../libs/juce-153/source"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g `pkg-config --cflags freetype2` -O0 -ggdb -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) `pkg-config --libs freetype2` -L"../../../libs" -lfreetype -lpthread -lasound -ldl -lrt -lX11 -lXext -ljuce-standalone-153_debug
  LDDEPS :=
  RESFLAGS := -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=0" -D "JucePlugin_Build_Standalone=1" -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -I "../source" -I "../../../libs/juce-153/standalone" -I "../../../libs/juce-153/source"
  TARGET := ThePilgrim_debug
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/PluginEditor.o \
	$(OBJDIR)/PluginProcessor.o \
	$(OBJDIR)/Knob.o \
	$(OBJDIR)/thepilgrimbackground.o \
	$(OBJDIR)/knobs.o \
	$(OBJDIR)/juce_StandaloneFilterApplication.o \
	$(OBJDIR)/juce_StandaloneFilterWindow.o \

MKDIR_TYPE := msdos
CMD := $(subst \,\\,$(ComSpec)$(COMSPEC))
ifeq (,$(CMD))
  MKDIR_TYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  MKDIR_TYPE := posix
endif
ifeq ($(MKDIR_TYPE),posix)
  CMD_MKBINDIR := mkdir -p $(BINDIR)
  CMD_MKLIBDIR := mkdir -p $(LIBDIR)
  CMD_MKOUTDIR := mkdir -p $(OUTDIR)
  CMD_MKOBJDIR := mkdir -p $(OBJDIR)
else
  CMD_MKBINDIR := $(CMD) /c if not exist $(subst /,\\,$(BINDIR)) mkdir $(subst /,\\,$(BINDIR))
  CMD_MKLIBDIR := $(CMD) /c if not exist $(subst /,\\,$(LIBDIR)) mkdir $(subst /,\\,$(LIBDIR))
  CMD_MKOUTDIR := $(CMD) /c if not exist $(subst /,\\,$(OUTDIR)) mkdir $(subst /,\\,$(OUTDIR))
  CMD_MKOBJDIR := $(CMD) /c if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking ThePilgrim
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning ThePilgrim
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/PluginEditor.o: ../source/PluginEditor.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginProcessor.o: ../source/PluginProcessor.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Knob.o: ../source/Headers/UI/Knob.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/thepilgrimbackground.o: ../source/Headers/Binary\ Data/Backgrounds/thepilgrimbackground.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/knobs.o: ../source/Headers/Binary\ Data/UI/knobs.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_StandaloneFilterApplication.o: ../../../libs/juce-custom/Standalone/juce_StandaloneFilterApplication.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_StandaloneFilterWindow.o: ../../../libs/juce-custom/Standalone/juce_StandaloneFilterWindow.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

