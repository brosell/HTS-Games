#ifndef AssetManager_H
#define AssetManager_H

#include <map>
#include <string>
using namespace std;

#include "Audio/SoundEffect.h"
#include "Graphics/SharedSkin.h"
#include "Graphics/SharedRotateSkin.h"
#include "BR_Game.h"
#include "Audio/Music.h"
#include "Graphics/Display.h"
#include "IniFile.h"
#include "MouseCursor.h"

/**
internal use - The posible asset types
*/
enum ASSET_TYPE
{
  UNDEF,
  SOUND_EFFECT,
  MUSIC,
  SKIN,
  ROTATESKIN,
  FONT1,
  MOUSE,
  TEXTURE,
  RELEVANT,
  TEXT
};

/** 
internal use - represents an asset
*/
class Asset
{
public:
  Asset():used(false), references(0) {}
  /** the name from the ini file */
  string name;
  /** the type derived from the inifile */
  ASSET_TYPE type;
  /** the asset */
  void* asset;

  bool used;

  int references;
};

/**
Manages games asset via an asset file in ini format.<p>
The format of the file: <p>
<pre>
[assetName]
Type = [SoundEffect | Music | Skin | RotateSkin | Font | Texture | Relevant]
Filename (for SoundEffect | Music | Font | Texture | Relevant) = the assets filename
FPS (for Skin, RotateSkin) = the Frames per second
Frames (for Skin, RotateSkin) = the number of frames
Frame01 (for Skin, RotateSkin) = the filename of the frame
FrameNN

Examples:
[rq_GameOver]
Type = Relevant
Filename = UI\gameover.bmp

[gfx_Block_Red_Idle]
Type = Skin
FPS = 1
Frames = 1
Frame01 = images\blocks\block_red_idle.bmp
</pre>

<ul>
<li>SoundEffect - a wav based sound effect
<li>Music - a midi
<li>Skin - a possibly animated texture
<li>RotateSkin - a posibly animated and rotatable texture
<li>Font - a SFont compatable font
<li>Texture - a texture
<li>Relevant - a required file. These aren't loaded, but the 
"assetter" tool uses them to create a package
</ul>
*/
class AssetManager
{
public:
  AssetManager(string assetIniFn);
  AssetManager() {}
  ~AssetManager();

  void setAssetFn(string fn);

  void load();
  void unload();

  bool isAssetLoaded(string name);

  int getIntAttribute(string name, string attribute);
  float getFloatAttribute(string name, string attribute);
  string getStringAttribute(string name, string attribute);
  /** the point of Point(-1, -1) if no such attribute */
  Point getPointAttribute(string name, string attribute);
  Rect getRectAttribute(string name, string attribute);


  /* futureuse. create a tool to create Asset lists
  void save();*/

  /** returns a loaded sound effect */
  SoundEffect* getSoundEffect(string assetName);
  void releaseSoundEffect(SoundEffect* effect);

  /** returns a loaded music */
  Music* getMusic(string assestName);

  /** returns a loaded texture */
  HTexture getTexture(string assetName);
  void releaseTexture(HTexture texture);

  /** returns a loaded SharedSkin */
  Skin* getSkin(string assetName);
  void releaseSkin(Skin* skin);

  /** returns a loaded RotateSkin */
  SharedRotateSkin* getRotateSkin(string assetName);
  void releaseRotateSkin(SharedRotateSkin* skin);

  /** mouse cursor */
  MouseCursor* getMouseCursor(string assetName);
  void releaseMouseCursor(MouseCursor* mouse);

  /** returns a loaded Font */
  Font* getFont(string assetName);

  string getText(string assetName);

  bool verify();

protected:
  
private:
  Asset* load(string assetName);
  void load2(string assetName);
  Asset* loadSoundEffect(string assetName);
  Asset* loadTexture(string assetName);
  Asset* loadSkin(string assetName);
  Asset* loadRotateSkin(string assetName);
  Asset* loadMusic(string assetName);
  Asset* loadFont(string assetName);
  Asset* loadText(string assetName);
  Asset* loadMouseCursor(string assetName);

  IniFile* m_ini;

  map<string, Asset*> m_assetMap;
  map<void*, Asset*> m_assetToAssetMap; // the actual asset is the key
};
#endif