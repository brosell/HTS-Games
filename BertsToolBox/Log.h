#ifndef Log_h
#define Log_h

#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>
#include <vector>
#include <locale>

#include <map>

#include <windows.h>

#include "boost/shared_ptr.hpp"

#include "CommentMacro.h"

using namespace std;

const int Inform  = 0x0001;
const int Warning = 0x0002;
const int Error   = 0x0004;
const int Fatal   = 0x0008;
const int Debug   = 0x0010;
const int Errors  = Error | Fatal;
const int Warnings= Errors | Warning;
const int All     = Inform | Warnings;
const int AllDebug= All | Debug;


namespace hts
{
  class Log
  {
  public:
    Log(string filename);
    bool printToConsole(bool b) { bool ret = m_printToConsole; m_printToConsole = b; return ret; }
    
    FILE* getFilePtr();
    
    string getDateAndTime();
  protected:
    void doWrite(const char* line);
    //private:
    FILE* m_stream;
    //ofstream* m_stream;
    bool m_printToConsole;
    string m_filename;
  };
  
  class MaintLog;

  template <typename charT, typename traits = std::char_traits<charT> >
  class MaintLogStreamBuf: public std::basic_streambuf<charT, traits>
  {
  public:
    MaintLogStreamBuf(MaintLog& log, int sev): m_log(log), m_sev(sev)
    {
    }
    
    
  protected:
    virtual int_type overflow(int_type c)
    {
      if (!traits::eq_int_type(c, traits::eof()))
      {
        if ( (m_log.getFilter() && m_sev) != 0)
        {
          if (c == '\n')
          {
            m_buffer.push_back('\0');
            m_log.logError(m_sev, &m_buffer[0]);
            m_buffer.clear();
          }
          else
          {
            m_buffer.push_back(c);
          }
        }
      }
      return traits::not_eof(c);
    }
    
  private:
    std::vector<charT> m_buffer;
    MaintLog& m_log;
    int m_sev;
  };
  
  class MaintLog: public Log
  {
  public:
    //  void write(int sev, string message);
    void write(int sev, const char* str, va_list vl);
    
    void logError(int sev, const char* str, ...){
      va_list vl;
      va_start( vl, str );
      write(sev, str, vl);
      va_end( vl );
    }
    
    std::ostream& stream(int sev) { return *(m_streams[sev].get()); }
    
    int setFilter(int f) { int ret = m_filter; m_filter = f; return ret;}
    int getFilter() { return m_filter; }
    
    const char* getSevString(int sev);
    
    static MaintLog& get(string filename = "Maintenance.log");
    static void closeall();
    
  protected:
    typedef boost::shared_ptr<MaintLogStreamBuf<char> > SP_MLStBuf;
    typedef boost::shared_ptr<std::ostream> SP_OStream;

    MaintLog(string filename = "Maintenance.log");
  private:
    int m_filter;
    static map<string, MaintLog*> s_logs;

    map<int, SP_MLStBuf> m_streamBufs;
    map<int, SP_OStream> m_streams;
    SP_MLStBuf m_errorStreamBuf;
    SP_MLStBuf m_informStreamBuf;
    SP_MLStBuf m_fatalStreamBuf;
    SP_MLStBuf m_debugStreamBuf;
    SP_MLStBuf m_warningStreamBuf;

    SP_OStream m_errorStream;
    SP_OStream m_informStream;
    SP_OStream m_fatalStream;
    SP_OStream m_debugStream;
    SP_OStream m_warningStream;
  };

  

  
  class SocketLog: public Log
  {
  public:
    SocketLog(): Log("Socket.log") { printToConsole(false); }
    void write(char* bytes, int size);
  };
  
  inline void logError(int sev, const char* str, ...)
  {
    va_list vl;
    va_start( vl, str );
    MaintLog::get().write(sev, str, vl);
    va_end( vl );
  }
  
  
  inline void logError(string message, int sev = Inform )
  {
    logError(sev, message.c_str());
  }
  
  class LogScope
  {
  public:
    LogScope(string what, string filename = "Maintenance.log"): m_log(filename), m_what(what)
    {
      char buf[255];
      sprintf(buf, "Entering: %s", m_what.c_str());
      //MaintLog::get(m_log).write(Debug, buf);
      logError(buf, Debug);
    }
    ~LogScope()
    { 
      char buf[255];
      sprintf(buf, "Leaving: %s", m_what.c_str());
      logError(buf, Debug);
    }
  private:
    string m_log;
    string m_what;
  };
  
}

using namespace hts;

#define logScope(what) hts::LogScope __ls(what);

#ifdef _DEBUG
#define lassert(x)\
  if ( !(x) )\
{ hts::logError(Error, "Failed Assertion: (%s) %s(%d)", #x, __FILE__, __LINE__);}

#define lassert2(x, s)\
  if ( !(x) )\
{ hts::logError(Error, "Failed Assertion (%s): \"%s\" %s(%d)", #x, (s), __FILE__, __LINE__); }

#define lassertWithReturn(x, s, r)\
  if ( !(x) )\
{ hts::logError(Error, "Failed Assertion (%s): \"%s\" %s(%d)", #x, (s), __FILE__, __LINE__); return (r); }

#ifdef assert
#undef assert
#endif
#define assert(x) \
  if ( !(x) )\
{ hts::logError(Error, "Failed Assertion: (%s) %s(%d)", #x, __FILE__, __LINE__); \
__asm int 3\
}

#else
#define lassert(x)
#define lassert2(x, s)
#define lassertWithReturn(x, s, r)

#ifdef assert
#undef assert
#endif
#define assert(x)
#endif

#define error MaintLog::get().stream(Error)
#define inform MaintLog::get().stream(Inform)
#define fatal MaintLog::get().stream(Fatal)
#ifdef _DEBUG
#define debug MaintLog::get().stream(Debug)
#else
#define debug COMMENT
#endif

#endif