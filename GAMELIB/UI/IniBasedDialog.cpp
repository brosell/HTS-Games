#pragma warning (disable:4786 4503 4530)
#include "IniBasedDialog.h"
#include "IniFile.h"
#include "StringTokenizer.h"
#include "UI.h"
#include "UI/List.h"
#include "UI/HSlider.h"
#include "UI/HighlightButton.h"
#include "UI/ToggleButton.h"
#include "UI/DropDownList.h"

#include "Misc/AssetManager.h"


IniBasedDialog::IniBasedDialog(IniFile& ini, string dialogName):
m_ini(ini),
m_dialogName(dialogName)
{
  if (!ini.isRead())
  {
    ini.read();
  }

  setControlName(dialogName);

  setBackground(m_ini[dialogName]["Background"]);
  setText(m_ini[dialogName]["Title"].c_str());
  setPosition(Rect::parseRect(m_ini[dialogName]["Position"]));

  m_defaultFontName = m_ini[dialogName]["Font"];
  if (m_defaultFontName != "")
  {
    setFont(theGame.assetManager->getFont(m_defaultFontName));
  }

  if(m_ini[dialogName]["BackgroundColor"] != "")
  {
    int r, g, b, a;
    parseColor(m_ini[dialogName]["BackgroundColor"], r, g, b, a);
    setBackgroundColor(r, g, b, a);
  }

  string mouse = m_ini[dialogName]["Mouse"];
  if (mouse != "")
  {
    setMouseCursor(mouse);
  }


  
  StringTokenizer st(m_ini[dialogName]["Controls"].c_str(), " ,");
  while (st.hasMoreTokens())
  {
    createControl(st.nextToken());
  }
}

IniBasedDialog::~IniBasedDialog()
{
  list<UIThing*>::iterator i;
  for(i=m_createdUIThings.begin(); i!=m_createdUIThings.end(); i++)
  {
    delete (*i);
  }
}


  // returns the id of the button that was pressed
int IniBasedDialog::getPressedId()
{
  return 0;
}


void IniBasedDialog::createControl(string name)
{
  string type = m_ini[name]["Type"];
  UIThing* thing = 0;
  if (type == "Button" || type == "DefaultButton" || type == "CancelButton")
  {
    thing = addButton(name);
  }
  if (type == "HighlightButton")
  {
    HighlightButton* b=new HighlightButton;
    thing = b;
    b->setHighlight(m_ini[name]["Highlight"]);
    int isDefault = atoi(m_ini[name]["Default"].c_str());
    if (isDefault > 0)
    {
      setDefault(b);
    }
    int isCancel = atoi(m_ini[name]["Cancel"].c_str());
    if (isCancel > 0)
    {
      setCancel(b);
    }
  }
  if (type == "ToggleButton")
  {
    thing = addToggleButton(name);
  }
  if (type == "SkinCanvas")
  {
    SkinCanvas* sc = new SkinCanvas;
    sc->setSkin(m_ini[name]["Skin"]);
    thing = sc;
  }
  if (type == "TextBox")
  {
    TextBox* tb = new TextBox;
    int maxSize = m_ini.getInt(name, "MaxSize");
    if (maxSize > 0)
    {
      tb->setMaxSize(maxSize);
    }
    thing = tb;
  }
  if (type == "TextArea")
  {
    TextArea* ta = new TextArea;
    ta->setIndent(m_ini.getInt(name, "Indent"));
    thing = ta;
  }
  if (type == "List")
  {
    List* l = new List;
    thing = l;
  }
  if (type == "DropDownList")
  {
    DropDownList* l = new DropDownList;
    thing = l;
  }

  if (type == "HSlider")
  {
    thing = addHSlider(name);
  }
  if (type == "Label")
  {
    thing = addLabel(name);
  }
  if (type == "Canvas")
  {
    thing = new Canvas;
  }
  if (type == "WorldCanvas")
  {
    thing = new WorldCanvas(0);
  }
  if (type == "VScrollBar")
  {
    thing = addVScrollBar(name);
  }
  if (type == "ProgressBar")
  {
    thing = addProgressBar(name);
  }
  
  if (thing != 0)
  {
    thing->setControlName(name);
    string font = m_ini[name]["Font"];
    if (font != "")
    {
      thing->setFont(theGame.assetManager->getFont(font));
    }
    else if (m_defaultFontName != "")
    {
      thing->setFont(theGame.assetManager->getFont(m_defaultFontName));
    }
    
    string mouse = m_ini[name]["Mouse"];
    if (mouse != "")
    {
      thing->setMouseCursor(mouse);
    }

    if(m_ini[name]["BackgroundColor"] != "")
    {
      int r, g, b, a;
      parseColor(m_ini[name]["BackgroundColor"], r, g, b, a);
      thing->setBackgroundColor(r, g, b, a);
    }
    thing->setPosition(Rect::parseRect(m_ini[name]["Position"]));
    thing->setId(atoi(m_ini[name]["Id"].c_str()));
    string text = m_ini[name]["Text"];
    if (text != "")
    {
      thing->setText(text.c_str());
    }
    string assetName = m_ini[name]["TextAsset"];
    if (assetName != "")
    {
      thing->setText(theGame.assetManager->getText(assetName).c_str());
    }
    doSFX(name, thing);
    addUIThing(thing);
    m_stringControl[name] = thing;
    m_createdUIThings.push_back(thing);
  }

}



UIThing* IniBasedDialog::addToggleButton(string name)
{
  ToggleButton* tb = new ToggleButton;
  string skin=m_ini[name]["CheckedTexture"];
  if (skin != "")
  {
    tb->setCheckedTexture(skin);
  }

  skin=m_ini[name]["UncheckedTexture"];
  if (skin != "")
  {
    tb->setUncheckedTexture(skin);
  }

  tb->setChecked(m_ini.getInt(name, "Checked") == 1);

  if (m_ini[name]["Other"] != "")
  {
    int other = m_ini.getInt(name, "Other");
    tb->setOther(other);
  }
  else
  {
    tb->setOther(-1);
  }

  return tb;
}

UIThing* IniBasedDialog::addProgressBar(string name)
{
  int vertical = atoi(m_ini[name]["Vertical"].c_str());
  int red, green, blue, alpha;
  parseColor(m_ini[name]["Color"], red, green, blue, alpha);
  ProgressBar* prg = new ProgressBar(vertical, red, green, blue, alpha);
  prg->setUpperBound(m_ini.getInt(name, "HighBound"));
  prg->setMargin(m_ini.getInt(name, "Margin"));
  prg->setLabelName(m_ini[name]["Label"]);
  return prg;
}

void IniBasedDialog::parseColor(string color, int& red, int& green, int& blue, int &alpha)
{
  red = green = blue = alpha = 0;
  StringTokenizer st(color.c_str(), ", ");
  if (st.countTokens() > 0)
  {
    red = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    green = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    blue = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    alpha = atoi(st.nextToken().c_str());
  }
  else
  {
    alpha = 255;
  }
}

UIThing* IniBasedDialog::addVScrollBar(string name)
{
  VScrollBar* sb = new VScrollBar;
  int low = atoi(m_ini[name]["LowBound"].c_str());
  int high = atoi(m_ini[name]["HighBound"].c_str());
  sb->setBounds(low, high);
  return sb;
}

UIThing* IniBasedDialog::addHSlider(string name)
{
  HSlider* sb = new HSlider;
  int low = atoi(m_ini[name]["LowBound"].c_str());
  int high = atoi(m_ini[name]["HighBound"].c_str());
  sb->setBounds(low, high);
  string slider = m_ini[name]["SliderSkin"];
  if (slider != "")
  {
    sb->setSliderSkin(slider);
  }
  int unitsPerTick = m_ini.getInt(name, "UnitsPerTick");
  if(unitsPerTick < 1)
  {
    unitsPerTick = 1;
  }
  sb->setUnitsPerTick(unitsPerTick);

  return sb;
}


UIThing* IniBasedDialog::addButton(string name)
{
  Button* button = new Button;
  if (m_ini[name]["DownTexture"] != "")
    button->setDownTexture(m_ini[name]["DownTexture"]);
  if (m_ini[name]["UpTexture"] != "")
    button->setUpTexture(m_ini[name]["UpTexture"]);
  if (m_ini[name]["FocusTexture"] != "")
    button->setFocusTexture(m_ini[name]["FocusTexture"]);
  if (m_ini[name]["OverTexture"] != "")
    button->setOverTexture(m_ini[name]["OverTexture"]);

  string type = m_ini[name]["Type"];
  if (type == "DefaultButton")
  {
    setDefault(button);
  }
  else if (type == "CancelButton")
  {
    setCancel(button);
  }
  else
  {
    int isDefault = atoi(m_ini[name]["Default"].c_str());
    if (isDefault > 0)
    {
      setDefault(button);
    }
    int isCancel = atoi(m_ini[name]["Cancel"].c_str());
    if (isCancel > 0)
    {
      setCancel(button);
    }
  }

  string link = m_ini[name]["Link"];
  if (link != "")
  {
    button->setLink(link);
  }

  return button;
}

UIThing* IniBasedDialog::addLabel(string name)
{
  // justified states
  Label* label = new Label;
  string hjust = m_ini[name]["HJust"];
  if (hjust == "Right")
  {
    label->setHorizJust(JUST_RIGHT);
  }
  else if (hjust == "Center")
  {
    label->setHorizJust(JUST_CENTER);
  }
  else
  {
    label->setHorizJust(JUST_LEFT);
  }

  string vjust = m_ini[name]["VJust"];
  if (vjust == "Middle")
  {
    label->setVertJust(JUST_MIDDLE);
  }
  else if (vjust == "Bottom")
  {
    label->setVertJust(JUST_BOTTOM);
  }
  else
  {
    label->setVertJust(JUST_TOP);
  }
  return label;
}

void IniBasedDialog::doSFX(string name, UIThing* thing)
{
  string asset = "";
  
  asset = m_ini[name]["SFX_MousePress"];
  if (asset != "")
  {
    thing->setOnMousePressSFX(asset);
  }

  asset = m_ini[name]["SFX_MouseRelease"];
  if (asset != "")
  {
    thing->setOnMouseReleaseSFX(asset);
  }

  asset = m_ini[name]["SFX_MouseClick"];
  if (asset != "")
  {
    thing->setOnMouseClickSFX(asset);
  }
  
  asset = m_ini[name]["SFX_MouseDblClick"];
  if (asset != "")
  {
    thing->setOnMouseDblClickSFX(asset);
  }
  
  asset = m_ini[name]["SFX_MouseEnter"];
  if (asset != "")
  {
    thing->setOnMouseEnterSFX(asset);
  }

  asset = m_ini[name]["SFX_MouseExit"];
  if (asset != "")
  {
    thing->setOnMouseExitSFX(asset);
  }
  
  asset = m_ini[name]["SFX_MouseOver"];
  if (asset != "")
  {
    StringTokenizer st(asset, ", ");
    string a = st.nextToken();
    bool loop = false;
    if (st.countTokens() > 0)
    {
      loop = atoi(st.nextToken())==0?false:true;
    }
    thing->setMouseOverSFX(a, loop);
  }
  
  asset = m_ini[name]["SFX_KeyPress"];
  if (asset != "")
  {
    thing->setOnKeyPressSFX(asset);
  }
  
  asset = m_ini[name]["SFX_KeyRelease"];
  if (asset != "")
  {
    thing->setOnKeyReleaseSFX(asset);
  }

}
