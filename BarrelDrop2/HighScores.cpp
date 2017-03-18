#pragma warning (disable : 4786 4503 4530)

#include "HighScores.h"
#include "IniFile.h"
#include "Log.h"
#include "Convert.h"

#include "boost/format.hpp"

HighScores::HighScores():
m_justAdded(-1)
{
//  for (int x=0; x<10; x++)
//  {
//    m_scores[x].name = "";
//    m_scores[x].level = 0;
//    m_scores[x].score = 0;
//  }
}

HighScores::~HighScores()
{
}

void HighScores::load(string filename)
{
  IniFile ini(filename);
  ini.read();
  char buf[255];
  
  for (int x=0; x<10; x++)
  {
    sprintf(buf, "HighScore%02d", x);
    m_scores[x].name = ini[buf]["Name"];
    if (m_scores[x].name == "")
    {
      m_scores[x].name = "nobody";
    }
    m_scores[x].level = ini.getInt(buf, "Level");
    m_scores[x].score = ini.getInt(buf, "Score");
    m_scores[x].skill = ini[buf]["Skill"];
    m_scores[x].survivor = ini.getInt(buf, "Survivor");
  }

}

void HighScores::save(string filename)
{
  IniFile ini(filename);
  char buf[255];
//  char val[255];
  for (int x=0; x<10; x++)
  {
    sprintf(buf, "HighScore%02d", x);
    string sect(buf);
    ini[sect]["Name"] = m_scores[x].name;
    ini[sect]["Level"] = toString(m_scores[x].level);
    ini[sect]["Score"] = toString(m_scores[x].score);
    ini[sect]["Skill"] = m_scores[x].skill;
    ini[sect]["Survivor"] = toString(m_scores[x].survivor);
  }

  ini.write();
}

HighScore HighScores::getScore(int num)
{
  return m_scores[num];
}

bool HighScores::isHighScore(int score)
{
  return (score > m_scores[9].score);
}

void HighScores::addScore(string name, int level, int s, string skill, int survivor)
{
  HighScore score;
  score.name = name;
  score.level = level;
  score.score = s;
  score.skill = skill;
  score.survivor = survivor;

  lassert(s >= m_scores[9].score);

  for (int c=0; c<10; c++)
  {
    if (s >= m_scores[c].score)
    {
      // insert it here
      for (int d=8; d>=c; d--)
      {
        m_scores[d+1] = m_scores[d];
      }
      m_scores[c] = score;
      m_justAdded = c;
      return;
    }
  }
}