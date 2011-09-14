# Microsoft Developer Studio Project File - Name="sklepSeq" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sklepSeq - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sklepSeq.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sklepSeq.mak" CFG="sklepSeq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sklepSeq - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sklepSeq - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sklepSeq - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sklepSeq___Win32_Release"
# PROP BASE Intermediate_Dir "sklepSeq___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sklepSeq_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sklepSeq_EXPORTS" /YX /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/sklepSeq_release_vst.dll"

!ELSEIF  "$(CFG)" == "sklepSeq - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sklepSeq___Win32_Debug"
# PROP BASE Intermediate_Dir "sklepSeq___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sklepSeq_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "sklepSeq_EXPORTS" /YX /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/sklepSeq_debug_vst.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "sklepSeq - Win32 Release"
# Name "sklepSeq - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\myMidiKeyboardComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqCursorComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqTransportComponent.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\myMidiKeyboardComponent.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqCursorComponent.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqTransportComponent.h
# End Source File
# End Group
# Begin Group "wrapper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wrapper\juce_IncludeCharacteristics.h
# End Source File
# Begin Source File

SOURCE=.\wrapper\formats\VST\juce_VstWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqCharacteristics.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqEditor.h
# End Source File
# End Group
# Begin Group "playlist"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqPlaylist.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylist.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistComponent.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistStep.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistStep.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistView.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistView.h
# End Source File
# End Group
# Begin Group "pattern"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPattern.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPatternControl.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPatternControl.h
# End Source File
# End Group
# Begin Group "step"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqStep.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqStep.h
# End Source File
# Begin Source File

SOURCE=.\stepEditController.cpp
# End Source File
# Begin Source File

SOURCE=.\stepEditController.h
# End Source File
# Begin Source File

SOURCE=.\stepEditNote.cpp
# End Source File
# Begin Source File

SOURCE=.\stepEditNote.h
# End Source File
# Begin Source File

SOURCE=.\stepEditSysex.cpp
# End Source File
# Begin Source File

SOURCE=.\stepEditSysex.h
# End Source File
# Begin Source File

SOURCE=.\stepQuickEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\stepQuickEdit.h
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqMain.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqMain.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqMainComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqMainComponent.h
# End Source File
# End Group
# Begin Group "skin "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqSkin.h
# End Source File
# End Group
# Begin Group "midi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\midiDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\midiDevice.h
# End Source File
# Begin Source File

SOURCE=.\midiMessageManager.cpp
# End Source File
# Begin Source File

SOURCE=.\midiMessageManager.h
# End Source File
# Begin Source File

SOURCE=.\myMidiMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\myMidiMessage.h
# End Source File
# Begin Source File

SOURCE=.\xsync.cpp
# End Source File
# Begin Source File

SOURCE=.\xsync.h
# End Source File
# End Group
# End Target
# End Project
