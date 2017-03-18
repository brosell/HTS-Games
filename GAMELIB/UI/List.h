#ifndef _List_h
#define _List_h

#include "UIThing.h"
#include "Font.h"
#include "VScrollBar.h"

#include <list>
#include <vector>
using namespace std;

class Surface;

class ListItem
{
public:
  ListItem(int id, string str): id(id), str(str) { }
  int id;
  string str;
};

class List: public Container, public AdjustmentListener
{
public:
  List();
  ~List();
  virtual string getName() { return "List"; }
  virtual void paint(Display* surface);
  virtual bool acceptsFocus() { return true; }

  void addItemListener(ItemListener* listener) { m_itemListeners.insert(listener); }
  void removeItemListener(ItemListener* listener) { m_itemListeners.erase(listener); }

  virtual void setPosition(Rect& pos)
  {
    Container::setPosition(pos);
    Rect r(pos.w - 10, 0, 10, pos.h);
    m_scroll.setPosition(r);
  }

  void addItem(int id, string item);
  void removeItem(int id);
  void clear();

  vector<ListItem>::iterator begin() { return m_items.begin(); }
  vector<ListItem>::iterator end() { return m_items.end(); }

  void setSelected(int pos);

  int getSelectedId();
  string getSelectedString();

  int countItems() { return m_items.size(); }

  bool hasSelection();
  
  int getVisibleLines()
  {
    Font* font=Font::getDefault();
    Rect r=getPosition();
    return ((r.h - (m_margin + m_margin))/font->getFontHeight());
  }

  void setMargin(int m) { m_margin = m; }

  void allowScroll(bool a) { m_allowScroll = a; }

  virtual void adjustmentValueChanged(AdjustmentEvent* event);

  virtual void onKeyPress(KeyPressEvent* event);
  virtual void onMouseClick(MouseClickEvent* event);

protected:
  void updateItemListeners();
  void createHighlight();
  void drawLines(Display* surface, list<string>& lines);
  int m_selectedItem;
  int m_topIndex;


  vector<ListItem> m_items;
private:
  int m_margin;
  bool m_allowScroll;

  set<ItemListener*> m_itemListeners;

  VScrollBar m_scroll;

  ItemStateChangeEvent isce;
};
#endif