#include "stdafx.h"
void read_thread(void*p)
{
    char in_buffer[1024];
    char out_buffer[1024];
    DWORD dwRetval;
    do{
        if (!DeviceIoControl(hNetWorkdev,
         IOCTL_NETVMINI_READ_DATA, NULL,
          0, out_buffer, 1024, &dwRetval, NULL))
	    {
		    printf("虚拟网卡读设备失败\r\n");
            continue;
	    }
        if(pcap_sendpacket(h_cap,(u_char *)out_buffer,
        dwRetval)!=0)
        {
            printf("物理网卡发送包失败\r\n");

        }
        else
        {
            printf("虚拟网卡=>物理网卡 %d 字节\r\n",
            dwRetval);
        }

    }while(1);

}