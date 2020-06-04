#pragma once

namespace Client {

class SampleClient {
 public:
  SampleClient();
  ~SampleClient();

 public:
  void AddSocket();
  void SendMessage();
  void CloseClient();

 private:
  int sock_fd;
};

}  // namespace Client
