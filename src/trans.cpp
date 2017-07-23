// trans.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



//#pragma comment(lib,"../WpdPack/Lib/wpcap.lib")

char* pcap_networkname;
char errbuff[128];
char pcap_buffer[65536];
HANDLE hHandle;
HANDLE hNetWorkdev;
DWORD dwRetval;
pcap_t* h_cap;
void list_dev(OUT char*);


//////////////////////////////////////////////////
//此函数输出使用方法
//////////////////////////////////////////////////
void usage()
{//TODO: 添加使用方法
	list_dev(NULL);

}

void list_dev(OUT char *selected_device_name)
{//列出网络设备
	int node_index=0;

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int count = 0;
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		printf("查找设备失败!错误描述:%s\r\n", errbuf);
	}
	for (d = alldevs; d; d = d->next)
	{
		printf("名称：%s\r\n",d->name);
		printf("\t描述%s\r\n\r\n", d->description);
		count++;
	}
	printf("输入:");
	scanf("%d",&node_index);
	d=alldevs;
	while(node_index)
	{
		if(d->next)
			d=d->next;
	}
	strcpy(selected_device_name,d->name);

	pcap_freealldevs(alldevs);
}

int main( int argc ,TCHAR *argv[])
{
	DWORD dwRetval;

#if 0	
	if (argc != 3)
	{
		usage();
		return 0;
	}
	
	if (!_tcscmp(argv[1],TEXT("1")))
	{
		//初始化com或者命名管道
		hHandle = CreateFile(argv[2],
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);//异步IO
	}
	else
	{
		hHandle = CreateFile(argv[2],
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);//异步IO
		
	}
#else

	hNetWorkdev = CreateFile(TEXT("\\\\.\\NETVMINI"),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hNetWorkdev)
	{
	//	printf("test");
		printf("打开网络设备失败\r\n");
		_getch();
		return 0;
	}
	printf("打开网络设备成功");
	if (!DeviceIoControl(hNetWorkdev, IOCTL_NETVMINI_READ_DATA, NULL, 0, NULL, 0, &dwRetval, NULL))
	{
		printf("读设备失败\r\n");
	}
	else
	{
		printf("读设备成功\r\n");
	}
	if (!DeviceIoControl(hNetWorkdev, IOCTL_NETVMINI_WRITE_DATA, NULL, 0, NULL, 0, &dwRetval, NULL))
	{
		printf("写设备失败\r\n");
	}
	else
	{
		printf("写设备成功\r\n");
	}
	
	CloseHandle(hNetWorkdev);
#endif
	char mytapname[1024];
	list_dev(mytapname);
	h_cap = pcap_open_live(mytapname, 65536, 1, 0, errbuff);
	if (h_cap == NULL)
	{
		printf("winpcap打开失败\r\n");
		return 0;
	}
	_beginthread(write_thread, 0, NULL);
	_beginthread(read_thread, 0, NULL);
	while (1)
		Sleep(0);
}

