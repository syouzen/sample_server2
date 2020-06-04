#include "client/sample_client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Client {

const int BUFF_SIZE = 1024;
static const char* SOCKET_PATH = "/tmp/sample_server2.socket";

SampleClient::SampleClient() : sock_fd(-1) {
}

SampleClient::~SampleClient() {
}

void SampleClient::AddSocket() {
  sock_fd = socket(PF_LOCAL, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    printf("[Client] Can't open stream socket.\n");
  }
}

void SampleClient::SendMessage() {
  struct sockaddr_un client_addr;
  int client_addr_size;
  char buff_rcv[BUFF_SIZE + 5];
  char data[BUFF_SIZE + 5];

  memset(&client_addr, 0, sizeof(client_addr));
  client_addr = {.sun_family = AF_LOCAL};
  strcpy(client_addr.sun_path, SOCKET_PATH);

  scanf("%s", data);

  sendto(sock_fd, data, strlen(data) + 1, 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr));
}

void SampleClient::CloseClient() {
  if (sock_fd != -1) {
    close(sock_fd);
    sock_fd = -1;
    printf("[Client] Client closed.\n");
  }
}

}  // namespace Client
