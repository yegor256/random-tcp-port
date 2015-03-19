//
// Copyright 2013 Yegor Bugayenko
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Allocate a new TCP server socket, and return
// its handler
int allocate() {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        if (errno == EMFILE) {
            /* too many open files */
            return 0;
        }
        perror("socket()");
        exit(-1);
    }
    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    return sock;
}

// Check whether the provided TCP port is available
// at the moment and return 1 if it's avaiable, zero otherwise
int available(int port) {
    int sock = allocate();
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(inet_addr("0.0.0.0"));
    int error = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
    return error == 0;
}

// Main entry point to the tool. It tries to allocate a new
// port in 5000-5099 interval. If all ports are busy in this interval,
// it will try to allocate any port available in 1024-65535 range.
int main() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    srand(tv.tv_usec);
    struct sockaddr_in addr;
    int attempts;
    int port;
    unsigned int seed = 0;
    for (attempts = 0; attempts < 100; ++attempts) {
        port = 5000 + rand_r(&seed) % 100;
        if (available(port)) {
            printf("%d\n", port);
            return 0;
        }
    }
    socklen_t len = sizeof(addr);
    addr.sin_port = 0;
    while (addr.sin_port < 1024) {
        usleep(10);
        if (++attempts > 500) {
            fprintf(stderr, "failed to reseve a port\n");
            return -1;
        }
        int sock = allocate();
        if (sock == 0) {
            continue;
        }
        if (bind(sock, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
            if (errno == EADDRINUSE) {
                /* address already in use */
                continue;
            }
            perror("bind()");
            return -1;
        }
        if (getsockname(sock, (struct sockaddr*) &addr, &len) != 0) {
            perror("getsockname()");
            return -1;
        }
    }
    printf("%d\n", addr.sin_port);
    return 0;
}
