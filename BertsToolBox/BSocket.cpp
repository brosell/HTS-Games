#include "BSocket.h"
#include "ipc.h"

#include <assert.h>
#include "Log.h"


extern int errno;


//////////////////////////////////////
// boot strap NT sockets
//////////////////////////////////////
static class StaticSocketInit
{
public:
  StaticSocketInit()
  {
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD( 1, 1 );
    WSAStartup( wVersionRequested, &wsaData );
  }
  ~StaticSocketInit()
  {
    WSACleanup();
  }
} staticSocketInit;
////////////////////////////////////////



BSocket::BSocket(int sock): 
m_socket(sock), 
m_address(""), 
m_port(-1), 
m_failed(false)
{
}

BSocket::BSocket(string address, int port): 
m_socket(-1), 
m_address(address), 
m_port(port), 
m_failed(false)
{
  open();
}

BSocket::~BSocket()
{
  if (m_socket != -1)
  {
    close();
  }
  m_socket = -1;
}

void BSocket::open()
{
  assert(m_socket == -1);
  if (m_socket == -1)
  {
    if (m_address != "" && m_port != -1)
    {
      m_socket = connect(m_address.c_str(), m_port);
      if (m_socket < 0)
      {
        m_errno = errno;
        m_failed = true;
      }
      else
      {
        m_failed = false;
      }
    }
    else
    {
      m_failed = true;
      m_socket = -1;
    }
  }
}

void BSocket::close()
{
  assert(m_socket != -1);
  int ret = ::closesocket(m_socket);
  m_socket = -1;
}

bool BSocket::isValid() 
{ 
  return !m_failed && m_socket!=-1;
}

//static
int BSocket::connect(const char* address, int port)
{
  int err;  
  long ip_addr = -1;
	ip_addr  = inet_addr((char *)(const char *)address);
	
  sockaddr_in sin;
  sin.sin_family=PF_INET;
  sin.sin_port=htons(port);
  sin.sin_addr.s_addr = ip_addr;
  
  int sock_fd = socket(AF_INET,SOCK_STREAM,6);
  ::connect(sock_fd, (struct sockaddr *) &sin, sizeof (struct sockaddr_in));

  err=WSAGetLastError();
  if (err == 0) 
  {
    return sock_fd;
  }

  return err;
}

bool BSocket::isReadReady()
{
  if(m_readBuffer.size() > 0)
  {
    return true;
  }
  return !wouldReadBlock();
}

bool BSocket::isWriteReady()
{
  return !wouldWriteBlock();
}
  
bool BSocket::wouldReadBlock()
{
  struct timeval timeout;
  fd_set fdSet;

  FD_ZERO(&fdSet);
  int max_fd = m_socket;
  FD_SET(m_socket, &fdSet);

  timeout.tv_sec = 0;
  timeout.tv_usec = 1;
  
  int ret = select(max_fd+1, &fdSet, 0, 0, &timeout);
  
  if (ret < 0)
  {
    m_failed = true;
    m_errno = errno;
    return true;
  }
  if (ret == 0)
  {
    return true;
  }
  return false;
}

bool BSocket::wouldWriteBlock()
{
  struct timeval timeout;
  fd_set fdSet;

  FD_ZERO(&fdSet);
  int max_fd = m_socket;
  FD_SET(m_socket, &fdSet);

  timeout.tv_sec = 0;
  timeout.tv_usec = 1;
  
  int ret = select(max_fd+1, 0, &fdSet, 0, &timeout);
  
  if (ret < 0)
  {
    m_failed = true;
    m_errno = errno;
    return true;
  }
  if (ret == 0)
  {
    return true;
  }
  return false;
}

int BSocket::write(char* data, int count)
{
  int ret = 0;
  int sent = 0;
  while (ret != count)
  {
    sent = ::send(m_socket, &(data[ret]), count-ret, 0);
    if (sent < 0)
    {
      m_failed = true;
      m_errno = errno;
      return sent;
    }
    ret += sent;
  } 
  return ret;
}

int BSocket::read(char* data, int max)
{
  int toRead = max;
  int read = 0;
  int ret;
  
  UBYTE* ptr = (UBYTE*)data;

  int ss = m_readBuffer.size();
  int fromBuffer = (ss<max)?ss:max; //min(m_readBuffer.size(), max);
  toRead = fromBuffer;
  while (toRead > 0)
  {
    *ptr = m_readBuffer.front();
    m_readBuffer.pop_front();
    ptr++;
    toRead--;
    read++;
  }

  toRead = max - fromBuffer;
  assert(toRead>=0);
  if ((toRead > 0) && !wouldReadBlock())
  {
    ret = ::recv(m_socket, (char*)ptr, toRead, 0);
    if (ret <= 0)
    {
      m_failed = true;
      m_errno = errno;
    }
    else
    {
      read += ret;
    }
  }

  return read;
}

void BSocket::unread(char* data, int count)
{
  for (int c=count-1; c>=0; c--)
  {
    m_readBuffer.push_front( ((UBYTE*)data)[c]);
  }
}

BServerSocket::BServerSocket(int port): m_port(port), m_failed(false)
{
	struct protoent *pe = getprotobyname("TCP");
	m_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);

	int val=1;
	setsockopt (m_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof (val));

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(m_port);
	
	if (bind(m_socket, (sockaddr *)&server, sizeof(server)) != 0) 
  {
    lassert(false);
    m_failed = true;
    return;
	}
	if (listen(m_socket, 5) != 0)
  {
    lassert(false);
    m_failed = true;
  }

}

BServerSocket::~BServerSocket()
{
  close();
}

bool BServerSocket::anyPendingConnections()
{
  struct timeval timeout;
  fd_set fdSet;
  
  FD_ZERO(&fdSet);
  int max_fd = m_socket;
  FD_SET(m_socket, &fdSet);
  
  timeout.tv_sec = 0;
  timeout.tv_usec = 1;
  
  
  int ret = select(max_fd+1, &fdSet, 0, 0, &timeout);
  if (ret < 0)
  {
    m_failed = true;
    m_errno=errno;
    return false;
  }
  if (ret == 0)
  {
    return false;
  }

  return true;
}

BSocket* BServerSocket::accept()
{
  struct sockaddr addr;
  int addrlen = sizeof(addr);
  int newSock = ::accept(m_socket, &addr, &addrlen);
  if (newSock <= 0) 
  {
    char buf[256];
    sprintf(buf, "Socket failed to accept with errno %d", errno);
    logError(buf, Error);
    m_failed = true;
    m_errno = errno;
    return 0;
  }
  return (new BSocket(newSock));
}

void BServerSocket::close()
{
  closesocket(m_socket);
  m_socket = -1;
}
