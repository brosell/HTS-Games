#ifndef ListChooser_h
#define ListChooser_h

#include "BR_Game.h"
#include "UI/List.h"
#include <string>
#include <algorithm>
#include <numeric>
#include "Utils.h"
#include "STLFunctorDelegate.h"

using namespace std;

/** List chooser acts like a popup menu. It is popped up and its list
is displayed. When the mouse is over the list, the item under the cursor
is highlighted. When the user clicks an item, the id is returned to the
calling fn. */
class ListChooser: public DialogBox
{
  typedef hts::STLVoidFunctorUnaryDelegate<ListChooser, string> D_AddItem;
public:
  /** construct a ListChooser from a range of iterator (must be string types) */
  template<typename ForwardIterator>
    ListChooser(ForwardIterator begin, ForwardIterator end):
  m_margin(0)
  {
    init();
    for_each(begin, end, D_AddItem(*this, &ListChooser::addItem));
  }

  /** create an empty listchooser */
  ListChooser():
  m_margin(0)
  {
    init();
  }

  ~ListChooser()
  {
    delete m_list;
  }

  virtual void onMouseMove(MouseMoveEvent* event);
  virtual void onMouseClick(MouseClickEvent* event);

  virtual void onKeyPress(KeyPressEvent* event);

  //virtual void keyPressed

  void init();

  void addItem(int id, string item);
  void removeItem(int id);
  size_t countItems();

  size_t getItemsHeight();
  size_t getItemsWidth();

  void setMargin(size_t m) { m_margin = m; }
  size_t getMargin() { return m_margin; }
  
  /** show the list. if it won't fit, adjust x and y so it does 
  @param x top left x
  @param y top left y
  */
  int popUp(int x, int y, bool testOnly = false);

  string getChoice();

private:
  size_t myHeight() { return getItemsHeight() + (2*m_margin); }
  size_t myWidth() { return getItemsWidth() + (2*m_margin); }

  List* m_list;

  void addItem(string s)
  {
    addItem(0, s);
  }

  size_t m_margin;

  struct WidthMessurer;

};

inline void ListChooser::addItem(int id, string item)
{
  lassert(m_list != 0);
  m_list->addItem(id, item);
}

inline void ListChooser::removeItem(int id)
{
  lassert(m_list != 0);
  m_list->removeItem(id);
}

inline size_t ListChooser::countItems()
{
  lassert(m_list != 0);
  return m_list->countItems();
}

inline size_t ListChooser::getItemsHeight()
{
  Font * font = getFont();
  assert(font != 0);
  return (m_list->countItems() * font->getFontHeight());
}


struct ListChooser::WidthMessurer
{
  WidthMessurer(Font* font): m_font(font) {}
  size_t operator()(size_t iv, ListItem& item)
  {
    int iw = m_font->getTextWidth(item.str);
    return (iv>=iw?iv:iw);
  }
private:
  Font* m_font;
};

inline size_t ListChooser::getItemsWidth()
{
  return std::accumulate(m_list->begin(), m_list->end(), 0, WidthMessurer(getFont()));
}


#endif