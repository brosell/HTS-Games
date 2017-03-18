#pragma warning (disable:4786 4503 4530)
#include "PropertiesDialog.h"
#include "StdString.h"

PropertiesDialog::PropertiesDialog(map<string, string>& theProperties):
m_properties(theProperties)
{
  // create controls for each property

  // create OK button

  setPosition(Rect(0, 0, 320, 480));
  setBackgroundColor(127, 127, 127, 255);

  map<string, string>::iterator pair;
  int y = 10;
  int x = 10;

  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    string name = pair->first;
    CStdString lblName;
    CStdString txtName;
    lblName.Format("lbl_%s", name.c_str());
    txtName = name;

    Label* lbl = new Label;
    lbl->setPosition(Rect(x, y, 150, 30));
    lbl->setText(name.c_str());
    lbl->setControlName(lblName);
    addUIThing(lbl);

    TextBox* txt = new TextBox;
    txt->setPosition(Rect(x+150, y, 150, 30));
    txt->setText(pair->second.c_str());
    txt->setControlName(txtName);
    txt->setBackgroundColor(255, 255, 255, 255);
    addUIThing(txt);
    y+=40;
  }

  Button* ok = new Button;
  ok->setPosition(Rect(x, y, 150, 30));
  ok->setBackgroundColor(200, 200, 200, 255);
  ok->setControlName("OkButton");
  ok->setText("Ok");
  addUIThing(ok);
  setDefault(ok);

  Button* cancel = new Button;
  cancel->setPosition(Rect(x+150, y, 150, 30));
  cancel->setBackgroundColor(200, 200, 200, 255);
  cancel->setControlName("CancelButton");
  cancel->setText("Cancel");
  addUIThing(cancel);
  setCancel(cancel);
}

PropertiesDialog::~PropertiesDialog()
{
  // delete all the controls
  map<string, string>::iterator pair;
  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    string name = pair->first;
    CStdString lblName;
    CStdString txtName;
    lblName.Format("lbl_%s", name.c_str());
    txtName = name;

    UIThing* lbl = getControlByName(lblName);
    UIThing* txt = getControlByName(txtName);
    
    removeUIThing(lbl);
    removeUIThing(txt);

    delete lbl;
    delete txt;
  }

  UIThing* thing = getControlByName("OkButton");
  removeUIThing(thing);
  delete thing;

  thing = getControlByName("Cancel");
  removeUIThing(thing);
  delete thing;
}

void PropertiesDialog::onOK()
{
  // set values in m_properties
  map<string, string>::iterator pair;
  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    CStdString txtName = pair->first;
    TextBox* txt = (TextBox*)getControlByName(txtName);
    m_properties[txtName] = txt->getText();
  }
  DialogBox::onOK();
}