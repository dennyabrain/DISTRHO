# Microsoft Developer Studio Project File - Name="sklepSeq_standalone" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sklepSeq_standalone - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sklepSeq_standalone.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sklepSeq_standalone.mak" CFG="sklepSeq_standalone - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sklepSeq_standalone - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "sklepSeq_standalone - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sklepSeq_standalone - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G6 /MT /W3 /GR /GX /O2 /Op /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /Zm1000 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wldap32.lib ws2_32.lib /nologo /subsystem:windows /machine:I386 /libpath:"../../bin"

!ELSEIF  "$(CFG)" == "sklepSeq_standalone - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /Zm1000 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wldap32.lib winmm.lib ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../bin"

!ENDIF 

# Begin Target

# Name "sklepSeq_standalone - Win32 Release"
# Name "sklepSeq_standalone - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sklepSeqCursorComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqTransportComponent.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\sklepSeqCharacteristics.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqCursorComponent.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqEditor.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqTransportComponent.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "wrapper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wrapper\formats\Standalone\juce_AudioFilterStreamer.cpp
# End Source File
# Begin Source File

SOURCE=.\wrapper\formats\Standalone\juce_AudioFilterStreamer.h
# End Source File
# Begin Source File

SOURCE=.\wrapper\formats\Standalone\juce_StandaloneFilterWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\wrapper\formats\Standalone\juce_StandaloneFilterWindow.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqStandaloneMain.cpp
# End Source File
# End Group
# Begin Group "playlist"

# PROP Default_Filter ""
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqPlaylist.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistStep.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistView.cpp
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqPlaylist.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistComponent.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistStep.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqPlaylistView.h
# End Source File
# End Group
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
# Begin Group "skin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\myMidiKeyboardComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\myMidiKeyboardComponent.h
# End Source File
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
# Begin Group "step"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sklepSeqStep.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqStep.h
# End Source File
# Begin Source File

SOURCE=.\sklepSeqStepComponentEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\sklepSeqStepComponentEditor.h
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
# End Target
# End Project
