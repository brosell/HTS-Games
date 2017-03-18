#pragma warning (disable : 4786 4503 4530)

#include "Block.h"
#include "Board.h"
#include "Globals.h"
#include "GameUI.h"

extern Board* board;


string scolors[] = 
{
  "Red",
  "Green",
  "Blue",
  "Yellow",
  "Purple"
};

ExplodingBlockParticleTraits* Block::s_traits[3];
ExplodingBlockParticleTraits* Block::s_blackTraits = 0;

Block::Block(Board* board, int color):
m_board(board),
m_color(color),
m_verticalEffect(0),
m_horizontalEffect(0),
m_state(IDLE),
d_co_disappear(*this, Block::doDisappear, "Block::disappear")
{
  if (color == WILD_UP_DOWN)
  {
    m_skinIdle = Globals::am->getSkin("gfx_Block_Wild_Up_Down");
    m_verticalEffect = Globals::am->getSkin("gfx_Vertical_Wild_Effect");
    m_horizontalEffect = Globals::am->getSkin("gfx_Horizontal_Wild_Effect");
  }
  else if (color == WILD_LEFT_RIGHT)
  {
    m_skinIdle = Globals::am->getSkin("gfx_Block_Wild_Left_Right");
    m_verticalEffect = Globals::am->getSkin("gfx_Vertical_Wild_Effect");
    m_horizontalEffect = Globals::am->getSkin("gfx_Horizontal_Wild_Effect");
  }
  else if (color == BLACK)
  {
    m_skinIdle = Globals::am->getSkin("gfx_Block_Black");
  }
  else
  {
    char assetName[128];
    sprintf(assetName, "gfx_Block_%s_Idle", scolors[m_color].c_str());
    m_skinIdle = Globals::am->getSkin(assetName);
    sprintf(assetName, "gfx_Block_%s_Disappearing", scolors[m_color].c_str());
  }

  if (s_blackTraits == 0)
  {
    s_traits[0] = new ExplodingBlockParticleTraits(0);
    s_traits[1] = new ExplodingBlockParticleTraits(1);
    s_traits[2] = new ExplodingBlockParticleTraits(2);

    s_blackTraits = new ExplodingBlockParticleTraits(BLACK);
  }

}

Block::~Block()
{
}

void Block::idle()
{
  m_state = IDLE;
  m_skinIdle->reset();
}

void Block::disappear()
{
  d_co_disappear.spawn();
}

void Block::doDisappear()
{
  m_state = DISAPPEARING;
  explode();
  Coroutine::pause(250);
  done();
}

void Block::explode()
{
  int color = m_color;
  
  Point pos = board->getPositioni();
  pos.x += (m_x*BLOCK_SIZE + HALF_BLOCK_SIZE);
  pos.y += (m_y*BLOCK_SIZE + HALF_BLOCK_SIZE);

  if (color>10)
  {
    scvs_specialNotices->fire(pos, 6, s_blackTraits, 0);  
  }
  else
  {
    scvs_specialNotices->fire(pos, 6, s_traits[color], 0);
  }
}

void Block::particlesDone(ParticleEvent* event)
{
  disappear();
  Shape::instance().reset();
}

void Block::draw(Display* display, int x, int y)
{
  m_x = x;
  m_y = y;
  Point pos = board->getPositioni();
  pos.x += (x*BLOCK_SIZE + HALF_BLOCK_SIZE);
  pos.y += (y*BLOCK_SIZE + HALF_BLOCK_SIZE);

  switch (m_state)
  {
  case IDLE:
    m_skinIdle->blit(display, pos.x, pos.y);
    break;
  case DISAPPEARING:
    if (m_color == WILD_UP_DOWN || m_color == WILD_LEFT_RIGHT)
    {
      drawSpecial(display);
    }
    else
    {
//      m_skinDisappearing->blit(display, pos.x, pos.y);
    }
    break;
  case DONE:
    break;
  default:
    lassert(false);
    break;
  }
}

void Block::drawToScreen(Display* display, int x, int y)
{
  m_skinIdle->blit(display, x, y, false);
}

void Block::drawSpecial(Display* display)
{
  Point pos = board->getPositioni();
  pos.x += (m_x*BLOCK_SIZE);
  pos.y += (m_y*BLOCK_SIZE);

  if (getColor() == WILD_UP_DOWN)
  {
    m_verticalEffect->blit(display, pos.x, 15, false);
  }
  else
  {
    m_horizontalEffect->blit(display, 100, pos.y, false);
  }
}


void Block::done()
{
  m_state = DONE;

}
