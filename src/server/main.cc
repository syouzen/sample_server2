#include <unistd.h>
#include "sample_server.h"

int main(int argc, char* argv[]) {
  Server::SampleServer ss;

  ss.OpenServer();
  while (1) {
    ss.ReceiveMessage();
    sleep(1);
  }

  return 0;
}
