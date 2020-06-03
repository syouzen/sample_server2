#pragma once

namespace Server {

class SampleServer {
 public:
  SampleServer();
  ~SampleServer();

 public:
  void OpenServer();
  void ReceiveAndSendMessage();

 private:
  int server_fd;
};

}  // namespace server
