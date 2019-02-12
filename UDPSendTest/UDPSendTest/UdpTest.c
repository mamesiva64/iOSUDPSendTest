//
//  UdpTest.c
//  UDPSendTest
//
//  Created by KenUchida on 2019/02/09.
//  Copyright © 2019 KenUchida. All rights reserved.
//

#include "UdpTest.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>      //  inet_addr
#include <unistd.h>         //  close

//  http://www.geekpage.jp/programming/linux-network/udp.php

static int g_sock = 0;
static struct sockaddr_in g_addr;

/*
addr.sin_family = AF_INET;
addr.sin_port = htons(12345);
addr.sin_addr.s_addr = INADDR_ANY;
bind(sock, (struct sockaddr *)&addr, sizeof(addr));
memset(buf, 0, sizeof(buf));
recv(sock, buf, sizeof(buf), 0);
printf("%s\n", buf);
close(sock);
*/

void ut_open(const char* ip, int port)
{
    g_sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    printf("sock=%d\n",g_sock);
    
    g_addr.sin_family = AF_INET;
    g_addr.sin_port = htons(port);
    g_addr.sin_addr.s_addr = inet_addr(ip);
}

void ut_close()
{
    close(g_sock);
    g_sock = 0;
}

void ut_test(double x,double y,double z)
{
    if(g_sock==0){
        return;
    }
    double v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    sendto(g_sock, v, sizeof(double)*3, 0, (struct sockaddr *)&g_addr, sizeof(g_addr));
}

