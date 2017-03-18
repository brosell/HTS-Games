#ifndef HighScores_h
#define HighScores_h

#include <string>
using namespace std;

class HighScore
{
public:
  HighScore(): name("nobody"), level(0), score(0) { }
  string name;
  int level;
  int score;
  string skill;
  int survivor;
};


class HighScores
{
public:
  HighScores();
  ~HighScores();
  
  void load(string filename);
  void save(string filename);

  HighScore getScore(int num);

  // true if score will be in the top 10
  bool isHighScore(int score);

  // adds the score to the top ten
  void addScore(string name, int level, int score, string skill, int survivor);

  int getLatest() { return m_justAdded; }
  void setLatest(int l) { m_justAdded = l; }
private:
  HighScore m_scores[10];
  size_t m_justAdded;
};

#endif