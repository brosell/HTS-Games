#ifndef MessageCenter_h
#define MessageCenter_h

#pragma warning (disable : 4786)

#include <set>
using namespace std;


#include "Message.h"
#include "Delegate.h"
#include "ObjectCache.h"
#include "MessageTesters.h"
#include "Link.h"

typedef void* HMessageFilter;

class MessageFilter
{
public:
  MessageTester* tester;
  Delegate* delegate;
};

class MessageObserver
{
public:
  virtual void observeMessage(Message* msg) = 0;
};

class MessageCenter
{
public:
  /**
    delivers a message testing against any stored filters
    
    @param msg - the message to be delivered

    @return - true if the Message was delivered
    */
  static
  bool deliverMessage(Message* msg);

  /**
    adds a filter to the MessageCenter. This filter will be tested
    for each and every Message that comes through.

    @param mt - a pointer to a tester
    @param d - a pointer to the delegate to call if a Message passes the test

    @return - the Handle to the filter (can be used later to remove the filter)
    */
  static
  HMessageFilter registerFilter(MessageTester* mt, Delegate* d);

  
  /**
    adds an observer to the current list of observers

    @param observer - the observer to add.
    */
  static
  void registerObserver(MessageObserver* observer);

  static
  void unregisterObserver(MessageObserver* observer);


  /**
    removes a filter from the MessageCenter

    @param handle - the handle to the filter to be removed
    */
  static
  void unregisterFilter(HMessageFilter handle);

  /**
    adds a link for the MessageCenter to Manage. Managed
    Links are read periodically and thier Messages are sent
    via any registered filters

    @param link - the Link pointer to register
    @param id - an id number assigned to the link
  */
  static
  void registerLink(Link* link);

  /**
    unregisters a Link. Once unregistered, the MessageCenter will not
    process it any longer

    @param link - the Link pointer to unregister
    */
  static
  void unregisterLink(Link* link);

  /**
    causes any registered Links to be read and thier messages delivered
    */
  static 
  void tick();

protected:

  static
  void drainLink(Link* link);
private:
  static set<MessageObserver*> s_observers;
  static set<MessageFilter*> s_filters;
  static ObjectCache<MessageFilter> s_filterCache;
  static set<Link*> s_links;
  
};

#endif