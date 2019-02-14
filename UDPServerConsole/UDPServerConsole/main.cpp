//
//  main.cpp
//  UDPServerConsole
//
//  Created by KenUchida on 2019/02/15.
//  Copyright © 2019 KenUchida. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>      //  inet_addr
#include <unistd.h>         //  close

#include <chrono>
/*
 
 //  http://www.ryusuke.net/archives/643
 */

int main()
{
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("sock = %d/ bind = %d\n",sock, ret);
    
    while(true)
    {
        // 開発途中
        char buf[25] = {0};
        recv(sock, buf, sizeof(buf), 0);

        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        printf("%lld:%s\n", millis, buf);
    }

    close(sock);
    
    return 0;
}


