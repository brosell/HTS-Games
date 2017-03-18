#ifndef HighScoresDialog_h
#define HighScoresDialog_h
#include "FireworksDialog.h"
#include "HighScores.h"

#include <vector>
#include "boost/shared_ptr.hpp"

extern HighScores g_highScores;

class HighScoresDialog: public FireworksDialog
{
  typedef boost::shared_ptr<UIThing> SP_UIThing;
  typedef std::vector<SP_UIThing> V_SP_UIThing;
public:
  HighScoresDialog(IniFile& ini, string name);

  virtual int doModal(Delegate* loop = 0);

  virtual void paint(Display* surface);

  void clone(Label* label);

private:
  int m_justAdded;
  int m_spacing;

  V_SP_UIThing m_myThings;
};

#endif