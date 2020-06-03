#include "server/sample_server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Server {

const int BUFF_SIZE = 1024;

SampleServer::SampleServer() : server_fd(-1) {
}
SampleServer::~SampleServer() {
}

void SampleServer::OpenServer() {
  struct sockaddr_in server_addr;

  server_fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (server_fd == -1) {
    printf("[Server] Can't open stream socket.\n");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr = {.sin_family = AF_INET,
                 .sin_port = htons(4000),
                 .sin_addr.s_addr = inet_addr("127.0.0.1")};

  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("[Server] Failed to bind.\n");
  }
}

void SampleServer::ReceiveAndSendMessage() {
  struct sockaddr_in client_addr;
  int client_addr_size = sizeof(client_addr);

  char buff_rcv[BUFF_SIZE + 5];
  char buff_snd[BUFF_SIZE + 5];

  recvfrom(server_fd, buff_rcv, BUFF_SIZE, 0,
           (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);
  printf("[Server] Receive Data : %s\n", buff_rcv);

  sprintf(buff_snd, "I got this : %s", buff_rcv);
  sendto(server_fd, buff_snd, strlen(buff_snd) + 1, 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr));
}

}  // namespace Server
