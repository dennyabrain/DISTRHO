# C++ Shared Library Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`

ifndef CONFIG
  CONFIG=Release
endif

# if multiple archs are defined turn off automated dependency generation
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Release)
  BINDIR := ../../../../bin
  LIBDIR := ../../../../bin
  OBJDIR := intermediate/Release
  OUTDIR := ../../../../bin
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "__cdecl=""" -D "NDEBUG=1" -I "../../source/midiOverlappingNoteKiller" -I "../../../../sdks/vstsdk2.4"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 -Wall -Wno-multichar -O2 -mtune=generic -msse -ffast-math -fomit-frame-pointer -fmessage-length=0 -finline-functions -fvisibility=hidden -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -s
  LDDEPS :=
  RESFLAGS := -D "LINUX=1" -D "__cdecl=""" -D "NDEBUG=1" -I "../../source/midiOverlappingNoteKiller" -I "../../../../sdks/vstsdk2.4"
  TARGET := midiOverlappingNoteKiller.so
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Debug)
  BINDIR := ../../../../bin
  LIBDIR := ../../../../bin
  OBJDIR := intermediate/Debug
  OUTDIR := ../../../../bin
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "__cdecl=""" -D "DEBUG=1" -D "_DEBUG=1" -I "../../source/midiOverlappingNoteKiller" -I "../../../../sdks/vstsdk2.4"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -g -O0 -ggdb -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared
  LDDEPS :=
  RESFLAGS := -D "LINUX=1" -D "__cdecl=""" -D "DEBUG=1" -D "_DEBUG=1" -I "../../source/midiOverlappingNoteKiller" -I "../../../../sdks/vstsdk2.4"
  TARGET := midiOverlappingNoteKiller_debug.so
 BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/midiOverlappingNoteKiller.o \
	$(OBJDIR)/PizMidi.o \
	$(OBJDIR)/vstplugmain.o \
	$(OBJDIR)/audioeffect.o \
	$(OBJDIR)/audioeffectx.o \

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
	@echo Linking midiOverlappingNoteKiller
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning midiOverlappingNoteKiller
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/midiOverlappingNoteKiller.o: ../../source/midiOverlappingNoteKiller/midiOverlappingNoteKiller.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PizMidi.o: ../../source/common/PizMidi.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vstplugmain.o: ../../source/common/vstplugmain.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/audioeffect.o: ../../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffect.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/audioeffectx.o: ../../../../sdks/vstsdk2.4/public.sdk/source/vst2.x/audioeffectx.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

