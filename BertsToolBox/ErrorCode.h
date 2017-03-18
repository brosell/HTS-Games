// ErrorCodes.h
#ifndef _ERRORCODE_H_
#define _ERRORCODE_H_



#include "stdstring.h"


enum ErrorCodeValue
{ SUCCESS, MyError1, MyError2, MyError3 };


class ErrorCode
{
private:
  ErrorCodeValue enValue_;
  bool * PboResp_;

public:
  ErrorCode();
  ErrorCode(const ErrorCode& _ref);
  ErrorCode(ErrorCodeValue _val);
  virtual ~ErrorCode();

  ErrorCode& operator = (const ErrorCode& _ref);

  bool operator != (const ErrorCode& _ref) const;
  bool operator == (const ErrorCode& _ref) const
        { return !(*this != _ref); };
};



#endif
