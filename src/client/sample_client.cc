#include "client/sample_client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Client {

const int BUFF_SIZE = 1024;

SampleClient::SampleClient() : sock_fd(-1) {
}

SampleClient::~SampleClient() {
}

void SampleClient::AddSocket() {
  sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    printf("[Client] Can't open stream socket.\n");
  }
}

void SampleClient::SendAndReceiveMessage() {
  struct sockaddr_in client_addr;
  int client_addr_size;
  char buff_rcv[BUFF_SIZE + 5];
  char data[BUFF_SIZE + 5];

  memset(&client_addr, 0, sizeof(client_addr));
  client_addr = {.sin_family = AF_INET,
                 .sin_port = htons(4000),
                 .sin_addr.s_addr = inet_addr("127.0.0.1")};

  scanf("%s", data);

  sendto(sock_fd, data, strlen(data) + 1, 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr));

  client_addr_size = sizeof(client_addr);

  recvfrom(sock_fd, buff_rcv, BUFF_SIZE, 0,
           (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);

  printf("[Client] \"%s\" From Server.\n", buff_rcv);
}

void SampleClient::CloseClient() {
  if (sock_fd != -1) {
    close(sock_fd);
    sock_fd = -1;
    printf("[Client] Client closed.\n");
  }
}

}  // namespace Client
