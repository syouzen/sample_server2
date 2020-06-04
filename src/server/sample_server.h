#pragma once

namespace Server {

class SampleServer {
 public:
  SampleServer();
  ~SampleServer();

 public:
  void OpenServer();
  void ReceiveMessage();

 private:
  int server_fd;
};

}  // namespace server
