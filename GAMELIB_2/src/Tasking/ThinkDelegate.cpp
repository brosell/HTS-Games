#pragma warning (disable : 4786)
#include "ThinkScheduler.h"
#include "ThinkDelegate.h"

ThinkDelegate::~ThinkDelegate()
{
  ThinkScheduler::remove(this);
}
