#ifndef _List_h
#define _List_h

#include "UIThing.h"
#include "Font.h"
#include "VScrollBar.h"
#include "IniFile.h"

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
  List(StringMap& attributes);
  ~List();
  virtual string getName() { return "List"; }
  virtual void paint(Display* surface);
  virtual bool acceptsFocus() { return true; }

  void addItemListener(ItemListener* listener) { m_itemListeners.insert(listener); }
  void removeItemListener(ItemListener* listener) { m_itemListeners.erase(listener); }

  virtual void setPosition(Rect& pos)
  {
    setDirty(true);
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
    FontHandle font=getFont();
    if (font.isValid())
    {
      Rect r=getPosition();
      return ((r.h - (m_margin + m_margin))/font->getFontHeight());
    }
    err_NoFont();
    return 0;
  }

  void setMargin(int m) { m_margin = m; setDirty(true);}
  void setLeftMargin(int m) { m_leftMargin = m; setDirty(true); }

  void allowScroll(bool a) { m_allowScroll = a; setDirty(true);}

  void allowNoSelection(bool a) { m_allowNoSelection = a; setDirty(true);}

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
  int m_leftMargin;
  bool m_allowScroll;
  bool m_allowNoSelection;

  set<ItemListener*> m_itemListeners;

  VScrollBar m_scroll;

  FontHandle m_highlightFont;
  SharedSkinHandle m_highlight;

  ItemStateChangeEvent isce;
};
#endif