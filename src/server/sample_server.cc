#include "server/sample_server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Server {

const int BUFF_SIZE = 1024;
static const char* SOCKET_PATH = "/tmp/sample_server2.socket";

SampleServer::SampleServer() : server_fd(-1) {
}
SampleServer::~SampleServer() {
}

void SampleServer::OpenServer() {
  struct sockaddr_un server_addr;

  unlink(SOCKET_PATH);

  server_fd = socket(PF_LOCAL, SOCK_DGRAM, 0);
  if (server_fd == -1) {
    printf("[Server] Can't open stream socket.\n");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr = {.sun_family = AF_LOCAL};
  strcpy(server_addr.sun_path, SOCKET_PATH);

  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("[Server] Failed to bind.\n");
  }
}

void SampleServer::ReceiveMessage() {
  struct sockaddr_un client_addr;
  int client_addr_size = sizeof(client_addr);

  char buff_rcv[BUFF_SIZE + 5];
  char buff_snd[BUFF_SIZE + 5];

  recvfrom(server_fd, buff_rcv, BUFF_SIZE, 0,
           (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);
  printf("[Server] Receive Data : %s\n", buff_rcv);
}

}  // namespace Server
