/* ****************************************************************************
 *
 *  LayoutSwapper2.cpp
 *  Created by Bert Rosell, on Wed Nov 19 2003, 13:28:45 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the LayoutSwapper2 component.
 *  Please see LayoutSwapper2.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "LayoutSwapper2.h"


/* ********************************* 
 * LayoutSwapper2
 ***********************************/
LayoutSwapper2::LayoutSwapper2(int dif, bool rot):
m_click1(0),
m_rot(rot)
{
  vector<Rect> sector;


  sector.clear();
  sector.push_back(Rect(0, 0, 100, 100));
  m_sectorLayouts.push_back(sector);

  
  if (dif < 1)
  {
    return;
  }

  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));
  sector.push_back(Rect(0, 50, 50, 50));
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(50, 50, 50, 50));
  m_sectorLayouts.push_back(sector);


  sector.clear();
  sector.push_back(Rect(0, 0, 50, 100));
  sector.push_back(Rect(50, 0, 50, 100));
  m_sectorLayouts.push_back(sector);

  sector.clear();
  sector.push_back(Rect(0, 0, 100, 50));
  sector.push_back(Rect(0, 50, 100, 50));
  m_sectorLayouts.push_back(sector);

  // easy threshold

  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(0, 50, 100, 50));
  m_sectorLayouts.push_back(sector);

  sector.clear();
  sector.push_back(Rect(0, 0, 100, 50));
  sector.push_back(Rect(0, 50, 50, 50));
  sector.push_back(Rect(50, 50, 50, 50));
  m_sectorLayouts.push_back(sector);

  // medium threshold
  sector.clear();
  sector.push_back(Rect(0, 0, 50, 100));
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(50, 50, 50, 50));
  m_sectorLayouts.push_back(sector);

  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));
  sector.push_back(Rect(0, 50, 50, 50));
  sector.push_back(Rect(50, 0, 50, 100));
  m_sectorLayouts.push_back(sector);

  if (dif < 2)
  {
    return;
  }

  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));
  sector.push_back(Rect(0, 50, 50, 50));
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(50, 50, 25, 50));
  sector.push_back(Rect(75, 50, 25, 50));
  m_sectorLayouts.push_back(sector);

  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));
  sector.push_back(Rect(0, 50, 50, 25));
  sector.push_back(Rect(0, 75, 50, 25));
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(50, 50, 50, 50));
  m_sectorLayouts.push_back(sector);


  sector.clear();
  sector.push_back(Rect(0, 0, 50, 50));

//  sector.push_back(Rect(0, 50, 25, 25));
//  sector.push_back(Rect(25, 50, 25, 25));
  sector.push_back(Rect(0, 50, 50, 25));
  sector.push_back(Rect(0, 75, 25, 25));
  sector.push_back(Rect(25, 75, 25, 25));
  
  sector.push_back(Rect(50, 0, 50, 50));
  sector.push_back(Rect(50, 50, 50, 50));
  m_sectorLayouts.push_back(sector);



}

LayoutSwapper2::~LayoutSwapper2()
{
 
}

struct PointHitsSector: public std::unary_function<Sector*, bool>
{
  PointHitsSector(Point p, Point topLeft): m_p(p), m_topLeft(topLeft){ }

  bool operator()(Sector* sector)
  {
    Rect r = sector->position;
    r.x+=m_topLeft.x;
    r.y+=m_topLeft.y;
    return r.containsPoint(m_p);
  }

  Point m_p;
  Point m_topLeft;
};

void LayoutSwapper2::onMouseClick(MouseClickEvent* event)
{
  setDirty(true);
  Rect r = getTranslatedPosition();

  Point m(event->x, event->y);
  Point topLeft(r.x, r.y);

  vector<Sector*>::iterator i;
  i = find_if(m_sectors.begin(), m_sectors.end(), PointHitsSector(m, topLeft));

  if (i==m_sectors.end())
  {
    return;
  }

  Sector* clicked = (*i);
    
  if (event->button == LEFT_BUTTON)
  {
    
    if (m_click1 == 0)
    {
      m_click1 = clicked;
      theGame.am->getSoundEffect("snd_Button")->play();
      return;
    }
    
    if (m_click1 == clicked)
    {
      m_click1 = 0;
      theGame.am->getSoundEffect("snd_NotHere")->play();
      return;
    }
    this->swap(m_click1, clicked);
//    StretchablePiece* p=m_click1->piece;
//    m_click1->setPiece(clicked->piece);
//    clicked->setPiece(p);
//    
//    theGame.am->getSoundEffect("snd_Swap")->play();
    madeMove();
    
    //swap(m_click1->piece, clicked->piece);
    m_click1 = 0;
  }
  else
  {
    clicked->piece->rotate();
  }
}



void LayoutSwapper2::setPicture(Picture* picture)
{
  /*
    need to bust up the picture into random sized (25x25 -> 100x100)
    sectors/pieces
  */
  setDirty(true);
  int c=0;
  for (int x=0; x<400; x+=100)
  {
    for (int y=0; y<300; y+=100)
    {
      int layoutNum = rand()%m_sectorLayouts.size();
      vector<Rect>& layout = m_sectorLayouts[layoutNum];

      vector<Rect>::iterator ir;
      for (ir=layout.begin(); ir!=layout.end(); ir++)
      {
        Rect r = (*ir);
        r.x+=x;
        r.y+=y;
        
        {
          SDL_Surface* surface = createSDLSurface(r.w, r.h);
          picture->copyPart(surface, Rect(0, 0, r.w, r.h), r);
          
          Sector* sec = new Sector(surface, m_rot, this);
          sec->position = r;
          sec->correctId = c;
          sec->piece->setId(c);
          c++;

          SDL_FreeSurface(surface);
          
          m_sectors.push_back(sec);
        }
      }
    }
  }

  // now shuffle the pieces around
  shufflePieces();
}

void LayoutSwapper2::shufflePieces()
{
  vector<StretchablePiece*> pieces;
  vector<Sector*>::iterator i;

  for (i=m_sectors.begin(); i!=m_sectors.end(); i++)
  {
    pieces.push_back((*i)->piece);
  }

  random_shuffle(pieces.begin(), pieces.end());
  random_shuffle(pieces.begin(), pieces.end());
  random_shuffle(pieces.begin(), pieces.end());
  random_shuffle(pieces.begin(), pieces.end());
  random_shuffle(pieces.begin(), pieces.end());
  random_shuffle(pieces.begin(), pieces.end());

  int c=0;
  for (i=m_sectors.begin(); i!=m_sectors.end(); i++)
  {
    (*i)->piece = pieces[c];
    c++;
  }
}

bool LayoutSwapper2::isDone()
{
  vector<Sector*>::iterator i;
  for (i=m_sectors.begin(); i!=m_sectors.end(); i++)
  {
    if ( (*i)->swapping())
    {
      return false;
    }

    if ((*i)->correctId != (*i)->piece->getId() )
    {
      return false;
    }
    if ( !(*i)->piece->isStraight()) 
    {
      return false;
    }
  }
  return true;
}

void LayoutSwapper2::doHelp()
{
  if (m_helped.w != 0 && m_helped.h != 0) // != Rect(0, 0, 0, 0))
  {
    MessageBeep(-1);
    return;
  }
  
  setDirty(true);
  vector<Sector*> wrongSectors;
  vector<Sector*>::iterator i;
  for (i=m_sectors.begin(); i!=m_sectors.end(); i++)
  {
    if ( (*i)->swapping())
    {
      continue;
    }
    if ((*i)->correctId != (*i)->piece->getId() || !(*i)->piece->isStraight())
    {
      wrongSectors.push_back(*i);
    }
  }

  if (wrongSectors.empty())
  {
    return;
  }

  std::random_shuffle(wrongSectors.begin(), wrongSectors.end());
  
  Sector* sector=wrongSectors[0];

  m_helped = sector->piece->getCorrectSector()->position;

  this->swap(sector, sector->piece->getCorrectSector());
  
  StretchablePiece* wrongPiece=sector->piece;
//
//  Sector* s2 = wrongPiece->getCorrectSector();
//  StretchablePiece* other = s2->piece;
//
//  //std::swap(sector->piece, sector->piece->getCorrectSector()->piece);
//  sector->setPiece(other);
//  s2->setPiece(wrongPiece);

  while (!wrongPiece->isStraight())
  {
    wrongPiece->rotate();
  }

  
  ThinkScheduler::doAt(ThinkScheduler::thisFrame() + 30, &d_clearHelped);
  setDirty(true);

  Layout::doHelp();
}

void LayoutSwapper2::swap(Sector* s1, Sector* s2)
{
  setDirty(true);
  StretchablePiece* p1 = s1->piece;
  StretchablePiece* p2 = s2->piece;

  s1->setPiece(p2);
  s2->setPiece(p1);

  theGame.am->getSoundEffect("snd_Swap")->play();
}

void LayoutSwapper2::paint(Display* display)
{
  //Layout::paint(display);
  Rect r = getTranslatedPosition();

  /*
    for_each (sector) DrawSector()

    if click one, draw red square around selected sector
  */

  vector<Sector*>::iterator i;
  for (i=m_sectors.begin(); i!=m_sectors.end(); i++)
  {
    (*i)->draw(display, r.x, r.y);
    if (m_click1 == (*i))
    {
      display->fillRect(r.x+m_click1->position.x, r.y+m_click1->position.y, m_click1->position.w, m_click1->position.h, 255, 0, 0, 127);
    }
  }

  drawHelped(display);
}

Sector::Sector(SDL_Surface* image, bool rot, Layout* layout): 
m_thinker(*this, Sector::think),
m_layout(layout)
{
  piece = new StretchablePiece(this, image, rot);
  setPiece(piece);
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_thinker);
} 


void Sector::draw(Display* display, int topLeftX, int topLeftY)
{
  Rect dp(drawRect);

  Rect r(position);
  r.x+=topLeftX + ((position.w/2)-(drawRect.w/2));
  r.y+=topLeftY + ((position.h/2)-(drawRect.h/2));
  r.w = dp.w;
  r.h = dp.h;

  piece->draw(display, r);

  r =position;
  r.x+=topLeftX;
  r.y+=topLeftY;

  if (m_layout->isGridShowing())
  {
    display->drawHLine(r.x, r.w, r.y, SectorLineColor);
    display->drawHLine(r.x, r.w, r.y+r.h, SectorLineColor);
    display->drawVLine(r.x, r.y, r.h, SectorLineColor);
    display->drawVLine(r.x+r.w, r.y, r.h, SectorLineColor);
  }
}

void Sector::setPiece(StretchablePiece* piece)
{
  this->piece = piece;
  drawRect = Rect(0, 0, 0, 0);
  
}

void Sector::think()
{
  if (drawRect.w < position.w)
  {
    m_layout->setDirty(true);
    drawRect.w+=position.w/10;
  }
  if (drawRect.h < position.h)
  {
    m_layout->setDirty(true);
    drawRect.h+=position.h/10;
  }

  // constrain
  if (drawRect.w > position.w) drawRect.w = position.w;
  if (drawRect.h > position.h) drawRect.h = position.h;
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_thinker);
}
