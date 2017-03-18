#ifndef IniBasedDialog_h
#define IniBasedDialog_h

#include "UI.h"

#include "IniFile.h"

#include <map>
using namespace std;

/**
A DialogBox that uses an inifile for defination

<pre>
[DialogName]
Background = the image to use as a background
Title = the title of the dialog. Shows at the top.
Position = x, y, w, h. the position of the dialog
Font = font asset name. If ommitted, the defualt font is used.
Controls = comma delimited list of controls

[ControlName]
The following are common to all controls
Type = [Button | DefaultButton | CancelButton | HighlightButton | ToggleButton | TextBox | TextArea | List | DropDownList | HSlider | Label | WorldCanvas | VscrollBar]
Position = x, y, w, h
Font = asset name of font. If ommited, the the font of the dialog is used.
Id = int id of the control
Text = text sent to setText of control

ProgressBar
Color = r, g, b
HighBound

VScrollBar, HSlider
LowBound = the lowerbound of the scroll values
HighBound = the upper bound

Button, DefaultButton, CancelButton
DownTexture
UpTexture
FocusTexture
OverTexture

HighlightButton
Highlight = image to use as a highlight
Default = [0 | 1]
Cancel = [0 | 1]

Label
HJust = the horizontal justification [Right | Center | Left]
VJust = the vertical justification [Top | Middle | Bottom]
</pre>
<em>Example</em>
<pre>
[Game]
Position = 0, 0, 640, 480
Background = UI\GameBackground8x10x45.bmp
Font = UI\font_arial_14_green.bmp
Controls = PlayField ScoreDisplay, LevelDisplay, CurrentPtsDisplay

[PlayField]
Id = 100
Type = WorldCanvas
Position = 65, 15, 360, 450


[ScoreDisplay]
Id = 101
Type = Label
Font = fnt_ScoreBoard
HJust = Center
Position = 490, 100, 140, 30

[LevelDisplay]
Id = 102
Type = Label
Font = fnt_ScoreBoard
HJust = Center
Position = 490, 250, 140, 30

[CurrentPtsDisplay]
Id = 102
Type = Label
Font = fnt_ScoreBoard
HJust = Center
Position = 490, 175, 140, 30
</pre>
*/
class IniBasedDialog: public DialogBox
{
public:
  IniBasedDialog(IniFile& ini, string dialogName);

  virtual ~IniBasedDialog();

  /** 
  @param name the name form the ini file
  */
  //UIThing* getControlByName(string name);

  /** returns the id of the button that was pressed */
  int getPressedId(); 

private:
  void createControl(string name);
  UIThing* addButton(string name);
  UIThing* addToggleButton(string name);
  UIThing* addVScrollBar(string name);
  UIThing* addTextBox(string name);
  UIThing* addTextField(string name);
  UIThing* addWorldCanvas(string name);
  UIThing* addLabel(string name);
  UIThing* addHSlider(string name);
  UIThing* addProgressBar(string name);

  void parseColor(string color, int& red, int& green, int& blue, int& alpha);

  void doSFX(string name, UIThing* thing);

  string m_defaultFontName;

  map<string, UIThing*> m_stringControl;

  list<UIThing*> m_createdUIThings;

  IniFile& m_ini;
  string m_dialogName;
};


#endif
