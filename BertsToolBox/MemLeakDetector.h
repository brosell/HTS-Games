/** 
* 
*	CRTMemManager.h 
* 
*	This file contains a class that initilizes 
*	the built in memory leak manager, and directs 
*	all the output to a log-file. 
* 
*	!!! - Works only when running in DEBUG mode. 
* 
*	Author:	Johan Öfverstedt 
* 
*/
#ifndef CRT_MEM_MANAGER_H
#define CRT_MEM_MANAGER_H

#include <iostream>
#include <fstream>
#include <crtdbg.h>
#include <time.h>
	
#if _DEBUG	
  class CRTMemManager	
  {	
  public:		
    CRTMemManager()		
    {		
      _CrtSetReportHook( CRTMemManager::report );
      _CrtSetDbgFlag((_CRTDBG_LEAK_CHECK_DF) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
    }		
    
    static int report(int reportType, char *message, int *returnValue)
    {
      static first = true;
      if(first)
      {				
        FILE *file = fopen("./CRTDebug.log", "a+");
        char t[20];
        char d[20];
        char s[100];
        _strtime(t);
        _strdate(d);
        sprintf(s, "\n--- Debug session (%s - %s) ---\n\n", d, t);
        fwrite(s, strlen(s), sizeof(char), file);
        if(file)
        {				
          fclose(file);
          file = 0;
        }	
      }					
      first = false;
      {				
        FILE *file = fopen("./CRTDebug.log", "a+");
        if(file)
        {	
          fwrite(message, 1, strlen(message), file);
          fclose(file);
          file = 0;	
        }
        else
        {
          std::cout << message;
        }
      }
      return 0;
    }
	};
#else
  class CRTMemManager	
  {	
  public:		
    CRTMemManager()
    {
    }
  };
#endif

#endif
