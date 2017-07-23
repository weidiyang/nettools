#include "stdafx.h"
void write_thread(void*p)
{
    char in_buffer[1024];
    char out_buffer[1024];
    DWORD dwRetval;

    struct pcap_pkthdr *header;
	const u_char *pkt_data;
    do{
        if(pcap_next_ex(h_cap,&header,&pkt_data)!=1)
        {
            printf("物理网卡读取失败\r\n");
            continue;
        }
        if (!DeviceIoControl(hNetWorkdev, IOCTL_NETVMINI_WRITE_DATA
        , (LPVOID)pkt_data, header->caplen, NULL, 0, &dwRetval, NULL))
        {
            printf("虚拟网卡写设备失败\r\n");
            continue;
        }
        printf("物理网卡=>虚拟网卡 %d 字节\r\n",
            dwRetval);

    }while(1);
}
