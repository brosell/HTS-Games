#ifndef BSocket_h
#define BSocket_h

#include <windows.h>
#include <winsock.h>
#include <list>
#include <string>

using std::list;
using std::string;

class BSocket
{
public:
  BSocket(string address, int port);
  BSocket(int sock);
  ~BSocket();

  void open();
  void close();

  bool isValid();// { return !m_failed && m_socket!=-1;; }

  bool isReadReady();
  bool isWriteReady();
  int write(char* data, int count);
  int read(char* data, int max);
  void unread(char* data, int count);

protected:
  static int connect(const char* address, int port);
  bool wouldReadBlock();
  bool wouldWriteBlock();
  void drain();

private:
  string m_address;
  int m_port;
  int m_socket;
  list<char> m_readBuffer;

  bool m_failed;
  int m_errno;

  // hide
  BSocket(const BSocket&);
  operator = (const BSocket&);
};

class BServerSocket
{
public:
  BServerSocket(int port);
  ~BServerSocket();

  bool anyPendingConnections();
  BSocket* accept();

  bool isValid() { return !m_failed && m_socket!=-1; }

  void close();
protected:

private:
  int m_socket;
  int m_port;
  bool m_failed;
  int m_errno;
};


#endif
