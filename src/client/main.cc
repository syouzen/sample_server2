#include "client/sample_client.h"

int main() {
  Client::SampleClient sc;

  sc.AddSocket();
  while(1) {
    sc.SendMessage();
  }
  sc.CloseClient();

  return 0;
}
