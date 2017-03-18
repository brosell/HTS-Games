#ifndef TextBox_tests_h
#define TextBox_tests_h

#include "TestSuite.h"

#include "TextBox.h"

class TextBox_tests: public hts::TestFixture
{
  typedef TextBox_tests THIS_TYPE;

  TextBox* m_tb;
public:
  virtual void registerTestCases()
  {
    FIXTURE_INIT();
    TEST_CASE(SetText);
    TEST_CASE(ClearText);
    TEST_CASE(SetTextWithMaxSize);
    TEST_CASE(SetTextResize);
  }

  virtual void setUp(){
    m_tb = new TextBox;
  }

  virtual void tearDown(){
    hts::Delete()(m_tb);
  }

  void SetText()
  {
    m_tb->setText("This is a test");
    CHECK(m_tb->getText() == "This is a test");
  }

  void ClearText()
  {
    m_tb->setText("This is a test");
    CHECK(m_tb->getText() == "This is a test");
    m_tb->setText("");
    CHECK(m_tb->getText() == "");
  }

  void ChangeText()
  {
    m_tb->setText("This is a test");
    CHECK(m_tb->getText() == "This is a test");
    m_tb->setText("Changed Text");
    CHECK(m_tb->getText() == "Changed Text");
  }

  void SetTextWithMaxSize()
  {
    m_tb->setMaxSize(4);
    m_tb->setText("This is a test");
    CHECK(m_tb->getText() == "This");
  }

  void SetTextResize()
  {
    m_tb->setText("This is a test");
    CHECK(m_tb->getText() == "This is a test");
    m_tb->setMaxSize(4);
    CHECK(m_tb->getText() == "This");
  }
};

#endif