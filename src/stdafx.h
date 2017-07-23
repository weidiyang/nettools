// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#pragma once
#define _WIN32_WINNT _WIN32_WINNT_WIN2K
//#include "targetver.h"
#include <stdio.h>
#include <tchar.h>




// TODO: reference additional headers your program requires here

#include "WpdPack/Include/pcap.h"
#include <conio.h>
#include <windows.h>
#include <string>
#include <process.h>


#define IOCTL_NETVMINI_READ_DATA \
    CTL_CODE (FILE_DEVICE_UNKNOWN, 0, METHOD_BUFFERED, FILE_READ_ACCESS)

#define IOCTL_NETVMINI_WRITE_DATA \
    CTL_CODE (FILE_DEVICE_UNKNOWN, 1, METHOD_BUFFERED, FILE_WRITE_ACCESS)

extern char* pcap_networkname;//pcap网卡名称
extern char errbuff[];
extern char pcap_buffer[];
extern HANDLE hHandle;
extern HANDLE hNetWorkdev;
extern pcap_t* h_cap;//pcap句柄

void read_thread(void*p);
void write_thread(void*p);

