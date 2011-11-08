# C++ Shared Library Makefile autogenerated by premake
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
  CPPFLAGS := $(DEPFLAGS) -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=1" -D "JucePlugin_Build_Standalone=0" -D "JUCE_USE_VSTSDK_2_4=1" -D "LINUX=1" -D "NDEBUG=1" -I "../source" -I "../source/soundtouch" -I "../../../libs/juce-153/plugin" -I "../../../libs/juce-153/source" -I "../../../sdks/vstsdk2.4"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 `pkg-config --cflags freetype2` -O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -s `pkg-config --libs freetype2` -L"../../../libs" -lfreetype -lpthread -lrt -lm -lX11 -lXext -ljuce-plugin-153
  LDDEPS :=
  RESFLAGS := -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=1" -D "JucePlugin_Build_Standalone=0" -D "JUCE_USE_VSTSDK_2_4=1" -D "LINUX=1" -D "NDEBUG=1" -I "../source" -I "../source/soundtouch" -I "../../../libs/juce-153/plugin" -I "../../../libs/juce-153/source" -I "../../../sdks/vstsdk2.4"
  TARGET := juce_pitcher.so
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Debug)
  BINDIR := ../../../bin
  LIBDIR := ../../../bin
  OBJDIR := intermediate/Debug
  OUTDIR := ../../../bin
  CPPFLAGS := $(DEPFLAGS) -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=1" -D "JucePlugin_Build_Standalone=0" -D "JUCE_USE_VSTSDK_2_4=1" -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -I "../source" -I "../source/soundtouch" -I "../../../libs/juce-153/plugin" -I "../../../libs/juce-153/source" -I "../../../sdks/vstsdk2.4"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -g `pkg-config --cflags freetype2` -O0 -ggdb -msse -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared `pkg-config --libs freetype2` -L"../../../libs" -lfreetype -lpthread -lrt -lm -lX11 -lXext -ljuce-plugin-153_debug
  LDDEPS :=
  RESFLAGS := -D "JucePlugin_Build_AU=0" -D "JucePlugin_Build_LV2=0" -D "JucePlugin_Build_RTAS=0" -D "JucePlugin_Build_VST=1" -D "JucePlugin_Build_Standalone=0" -D "JUCE_USE_VSTSDK_2_4=1" -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -I "../source" -I "../source/soundtouch" -I "../../../libs/juce-153/plugin" -I "../../../libs/juce-153/source" -I "../../../sdks/vstsdk2.4"
  TARGET := juce_pitcher_debug.so
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/JucePitcherFilter.o \
	$(OBJDIR)/JucePitcherComponent.o \
	$(OBJDIR)/cpu_detect_x86_gcc.o \
	$(OBJDIR)/FIRFilter.o \
	$(OBJDIR)/sse_optimized.o \
	$(OBJDIR)/FIFOSampleBuffer.o \
	$(OBJDIR)/TDStretch.o \
	$(OBJDIR)/mmx_optimized.o \
	$(OBJDIR)/AAFilter.o \
	$(OBJDIR)/RateTransposer.o \
	$(OBJDIR)/SoundTouch.o \
	$(OBJDIR)/juce_VST_Wrapper.o \

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
	@echo Linking juce_pitcher
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning juce_pitcher
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/JucePitcherFilter.o: ../source/JucePitcherFilter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/JucePitcherComponent.o: ../source/JucePitcherComponent.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpu_detect_x86_gcc.o: ../source/soundtouch/cpu_detect_x86_gcc.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FIRFilter.o: ../source/soundtouch/FIRFilter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sse_optimized.o: ../source/soundtouch/sse_optimized.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FIFOSampleBuffer.o: ../source/soundtouch/FIFOSampleBuffer.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TDStretch.o: ../source/soundtouch/TDStretch.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/mmx_optimized.o: ../source/soundtouch/mmx_optimized.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AAFilter.o: ../source/soundtouch/AAFilter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RateTransposer.o: ../source/soundtouch/RateTransposer.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SoundTouch.o: ../source/soundtouch/SoundTouch.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper.o: ../../../libs/juce-153/source/src/audio/plugin_client/VST/juce_VST_Wrapper.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

