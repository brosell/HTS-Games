// ErrorCodes.cpp
#include "ErrorCode.h"
#include <iostream.h>
#include "stdString.h"


ErrorCode::ErrorCode() : enValue_(SUCCESS),
    PboResp_(new bool(false))
{
}

ErrorCode::ErrorCode(const ErrorCode& _ref) :
    enValue_(_ref.enValue_), PboResp_(new bool(true))
{
  *_ref.PboResp_ = false;
}

ErrorCode::ErrorCode(ErrorCodeValue _val) :
    enValue_(_val), PboResp_(new bool(true))
{
}

ErrorCode::~ErrorCode()
{
  if (*PboResp_)
    cerr << "Destruction of untested error code: value "
      << enValue_ << endl;

  delete PboResp_;
}

ErrorCode& ErrorCode::operator = (const ErrorCode& _ref)
{
  if (*PboResp_)
    cerr << "Untested error code (value " << enValue_
      << ") erased by new value " << _ref.enValue_ << endl;

  enValue_ = _ref.enValue_;
  *PboResp_ = *_ref.PboResp_;
  *_ref.PboResp_ = false;
  
  return *this;
}

bool ErrorCode::operator != (const ErrorCode& _ref) const
{
  *PboResp_ = false;
  *_ref.PboResp_ = false;

  return (enValue_ != _ref.enValue_);
}

