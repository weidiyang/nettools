# Makefile : Illustrates the effective use of precompiled
#            headers in a project
# Usage:     NMAKE option
# option:    DEBUG=[0|1]
#            (DEBUG not defined is equivalent to DEBUG=0)
#
# •libcmt.lib: static CRT link library for a release build (/MT)
# •libcmtd.lib: static CRT link library for a debug build (/MTd)
# •msvcrt.lib: import library for the release DLL version of the CRT (/MD)
# •msvcrtd.lib: import library for the debug DLL version of the CRT (/MDd)

OBJS = trans.obj read_thread.obj write_thread.obj
SRCS = trans.cpp read_thread.cpp write_thread.cpp
CLFLAGS = /c /DWIN32
# List all linker options common to both debug and final
# versions of your code here:
LINKLIB = wpcap.lib Packet.lib
LINKFLAGS = /MACHINE:X86 /SUBSYSTEM:CONSOLE /LIBPATH:WpdPack\Lib 
CINCLUDEPATH = /I.\WpdPack\Include /I.\ WpdPack\Include\pcap
!IF "$(DEBUG)" == "1"
CLFLAGS   = /D_DEBUG $(CLFLAGS) /EHsc /Od /Zi  /MDd
LINKFLAGS = $(LINKFLAGS)  /DEBUG  msvcrtd.lib
LIBS      = 
!ELSE
CLFLAGS   = $(CLFLAGS) /EHsc /Os /Gs  /MD
LINKFLAGS = $(LINKFLAGS)  /RELEASE msvcrt.lib
LIBS      = 
!ENDIF

all:myapp.exe
	-mkdir out
	-move *.exe      out\ 
	-move *.obj      out\ 
	-move *.pdb      out\ 
	-move *.ilk      out\ 
	-move *.manifest out\ 

clean:
	-del /F /Q /S   out
	-del /S /Q /F *.obj
	-del /S /Q /F *.pdb
	-del /S /Q /F *.ilk
	-del /S /Q /F *.manifest out\ 
	-rmdir out

$(OBJS):$*.cpp
	cl /DWIN32  $(CLFLAGS)  $*.cpp /Fo$*.obj

myapp.exe:$(OBJS)
	link $(LINKFLAGS) $(LINKLIB) $(OBJS) /OUT:myapp.exe



