#pragma warning (disable : 4786)
#include "Log.h"
#include "fileUtils.h"
#include <sstream>

Log::Log(string filename):
//m_stream(filename.c_str()),
m_stream(0),
m_filename(filename),
m_printToConsole(true)
{
  remove(filename.c_str());
}

string Log::getDateAndTime()
{
  char timeBuffer[9];
  char dateBuffer[9];

  // get data/time
  _strdate(dateBuffer);
  _strtime(timeBuffer);

  // and write
  stringstream ss;
  ss << dateBuffer << " " << timeBuffer;

  return ss.str();
}

FILE* Log::getFilePtr()
{
  if (m_stream == 0)
  {
    m_stream = fopen(m_filename.c_str(), "w");
  }
  return m_stream;
}

void Log::doWrite(const char* line)
{

  if (getFilePtr() == 0)
  {
    return;
  }

  string dateTime = getDateAndTime();

  fprintf(m_stream, "%s - ", dateTime.c_str());
  fprintf(m_stream, "%s\n", line);

  fflush(m_stream);
  fflush(m_stream);
  if (m_printToConsole)
  {
    fprintf(stderr, "%s - ", dateTime.c_str());
    fprintf(stderr, "%s\n", line);
  }
}
  
map<string, MaintLog*> MaintLog::s_logs;

MaintLog::MaintLog(string filename): 
Log(filename), 
m_filter(Errors)
{
  m_streamBufs[Error] = SP_MLStBuf(new MaintLogStreamBuf<char>(*this, Error));
  m_streamBufs[Inform] = SP_MLStBuf(new MaintLogStreamBuf<char>(*this, Inform));
  m_streamBufs[Fatal] = SP_MLStBuf(new MaintLogStreamBuf<char>(*this, Fatal));
  m_streamBufs[Debug] = SP_MLStBuf(new MaintLogStreamBuf<char>(*this, Debug));
  m_streamBufs[Warning] = SP_MLStBuf(new MaintLogStreamBuf<char>(*this, Warning));
  
  m_streams[Error] = SP_OStream(new std::ostream(m_streamBufs[Error].get()));
  m_streams[Inform] = SP_OStream(new std::ostream(m_streamBufs[Inform].get()));
  m_streams[Fatal] = SP_OStream(new std::ostream(m_streamBufs[Fatal].get()));
  m_streams[Debug] = SP_OStream(new std::ostream(m_streamBufs[Debug].get()));
  m_streams[Warning] = SP_OStream(new std::ostream(m_streamBufs[Warning].get()));
}

MaintLog& MaintLog::get(string filename)
{
  MaintLog* ml = 0;
  map<string, MaintLog*>::iterator pair;
  pair = s_logs.find(filename);
  if (pair == s_logs.end())
  {
    ml = new MaintLog(filename);
    s_logs[filename] = ml;
  }
  else
  {
    ml = pair->second;
  }
  return *ml;
}

void MaintLog::closeall()
{
  map<string, MaintLog*>::iterator pair;
  for (pair = s_logs.begin(); pair!=s_logs.end(); pair++)
  {
    MaintLog* ml = pair->second;
    FILE* fp = ml->getFilePtr();
    fflush(fp);
    fclose(fp);
    delete ml;
  }
  s_logs.clear();
}

const char* MaintLog::getSevString(int sev)
{
  switch(sev)
  {
  case Inform:
    {
      return "Inform";
    }
    break;
  case Warning:
    {
      return "Warning";
    }
    break;
  case Error:
    {
      return "*Error";
    }
    break;
  case Fatal:
    {
      return "*FATAL ERROR";
    }
    break;
  case Debug:
    {
      return "++ DEBUG ++";
    }
    break;
  default:
    {
      return "*** Unknown Severity";
    }
    break;
  }
}



//void MaintLog::write(int sev, string message)
//{
//  if ( (m_filter & sev) == 0)
//  {
//    return;
//  }
//
////  ss << ": " << message;
////  doWrite(ss.str().c_str());
//  write(sev, "%s: %s", getSevString(sev), message.c_str());
//}

void MaintLog::write(int sev, const char* str, va_list vl)
{
  if ( (m_filter & sev) == 0 && sev != Fatal)
  {
    return;
  }

  FILE* stream = getFilePtr();
  fprintf(stream, "%s - %s: ", getDateAndTime().c_str(), getSevString(sev));
  if (m_printToConsole || sev != Fatal)
  { 
    fprintf(stderr, "%s - %s: ", getDateAndTime().c_str(), getSevString(sev));
  }

  vfprintf(stream, str, vl);
  fprintf(stream, "\n");
  if (m_printToConsole || sev != Fatal)
  { 
    vfprintf(stderr, str, vl);
    fprintf(stderr, "\n");
  }

  if (sev == Fatal)
  {
    exit(-1);
  }
}

void SocketLog::write(char* bytes, int size)
{
  char buf[1024];
  char* ptr = buf;
  for (int c=0; c<size && c<1024; c++)
  {
    ptr += sprintf(ptr, "%02x ", bytes[c]);
  }

  doWrite(buf);
}

