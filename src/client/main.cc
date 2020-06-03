#include "client/sample_client.h"

int main() {
  Client::SampleClient sc;

  sc.AddSocket();
  sc.SendAndReceiveMessage();
  sc.CloseClient();

  return 0;
}
