#
# Put the binaries and DLL's in a folder called release and run the NSIS script
# in the parent folder.
#

# define installer name
OutFile "setup.exe"

# set Program Files as install directory
InstallDir $PROGRAMFILES\youtube-dl-qt

DirText "This will install youtube-dl-qt on your computer. Choose a directory"

RequestExecutionLevel admin # Admin rights

# default section start
Section

SetShellVarContext all

# define output path
SetOutPath $INSTDIR

# specify file to go in output path
File /r release\*

CreateDirectory "$SMPROGRAMS\youtube-dl-qt"
CreateShortCut "$SMPROGRAMS\youtube-dl-qt\Uninstall.lnk" "$INSTDIR\uninstaller.exe"
CreateShortCut "$SMPROGRAMS\youtube-dl-qt\youtube-dl-qt.lnk" "$INSTDIR\youtube-dl-qt.exe"

# define uninstaller name
WriteUninstaller $INSTDIR\uninstaller.exe



#-------
# default section end
SectionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"

SetShellVarContext all

# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

# Delete installed folder
RMDir /r $INSTDIR\platforms
Delete $INSTDIR\Qt*.dll
Delete $INSTDIR\youtube-dl*
Delete $INSTDIR\libwinpthread-1.dll
Delete $INSTDIR\libstdc++-6.dll
Delete $INSTDIR\libgcc_s_dw2-1.dll

# Delete shortcut
RMDIR /r "$SMPROGRAMS\youtube-dl-qt"

SectionEnd
