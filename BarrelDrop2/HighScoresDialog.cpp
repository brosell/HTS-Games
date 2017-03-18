#pragma warning ( disable : 4530 4503 4786 )

#include "HighScoresDialog.h"

HighScoresDialog::HighScoresDialog(IniFile& ini, string dlgname):
FireworksDialog(ini, dlgname)
{
  Label* name = dynamic_cast<Label*>(getControlByName("Name"));
  Label* level = dynamic_cast<Label*>(getControlByName("Level"));
  Label* score = dynamic_cast<Label*>(getControlByName("Score"));
  Label* skill = dynamic_cast<Label*>(getControlByName("Skill"));
  Label* surv = dynamic_cast<Label*>(getControlByName("Survivor"));

  if (name == 0 || level == 0 || score == 0 || skill == 0 || surv == 0)
  {
    error << "Highscores dialog is missing controls. It may not display correctly." << endl;
    return;
  }

  name->hide();
  level->hide();
  score->hide();
  skill->hide();
  surv->hide();

  m_spacing = ini.getInt(dlgname, "VSpacing");

  clone(name);
  clone(level);
  clone(skill);
  clone(score);
  clone(surv);
}

void HighScoresDialog::clone(Label* label)
{
  Rect r = label->getPosition();
  int id = label->getId();

  for (int x=0; x<10; x++, id++, r.y += m_spacing)
  {
    Label* nl = new Label;
    nl->setId(id);
    nl->setPosition(r);
    nl->setHorizJust(label->getHorizJust());
    nl->setVertJust(label->getVertJust());
    nl->setDrawBorder(label->getDrawBorder());

    addUIThing(nl);

    m_myThings.push_back(SP_UIThing(nl));
  }
}



int HighScoresDialog::doModal(Delegate* loop)
{
  for (int x=0; x<10; x++)
  {
    Label* name = dynamic_cast<Label*>(getControl(700+x));
    Label* level = dynamic_cast<Label*>(getControl(800+x));
    Label* scorel = dynamic_cast<Label*>(getControl(900+x));
    Label* skill = dynamic_cast<Label*>(getControl(1000+x));
    Label* surv = dynamic_cast<Label*>(getControl(1100+x));
    
    HighScore score = g_highScores.getScore(x);
    if (name == 0 || level == 0 || scorel == 0 || skill == 0 || surv == 0)
    {
      error << "Highscores dialog is missing controls. It may not display correctly." << endl;
      return -1;
    }

    
    char buf[255];
    name->setText(score.name.c_str());
    
    sprintf(buf, "%d", score.level);
    level->setText(buf);
    
    sprintf(buf, "%d", score.score);
    scorel->setText(buf);

    skill->setText(score.skill.c_str());

    if (score.survivor != 0)
    {
      surv->setText("Survivor!");
    }
    else
    {
      surv->setText("Normal");
    }
  }
  m_justAdded = g_highScores.getLatest();
  int ret = FireworksDialog::doModal(loop);
  g_highScores.setLatest(-1);
  return ret;
}

void HighScoresDialog::paint(Display* surface)
{
  FireworksDialog::paint(surface);
  
  if (m_justAdded != -1)
  {
    Label* name = (Label*)getControl(700+m_justAdded);
    Label* scorel = (Label*)getControl(900+m_justAdded);
    
    Rect nr=name->getPosition();
    Rect sr=scorel->getPosition();
    
    int x=nr.x;
    int y=nr.y;
    
    int w=(sr.x+sr.w)-nr.x;
    int h=(sr.y+sr.h)-nr.y;
    
    surface->fillRect(x, y, w, h, 0, 0, 255, 127);

    name->paint(surface);
    scorel->paint(surface);
    getControl(800+m_justAdded)->paint(surface);
    getControl(1000+m_justAdded)->paint(surface);
    getControl(1100+m_justAdded)->paint(surface);
  }
}