#pragma warning (disable : 4786)

#ifndef AStar_h
#define AStar_h

#include <list>
#include <set>
#include <algorithm>

using namespace std;

//class AStarNode
//{
//public:
//  int astar_doH(AStarNode* end); // here to end
//
//  int astar_children(AStarNode** nodes, int max);
//
//  AStarNode* astar_parent;
//  int astar_cost; // cost of this node
//  int astar_g; // cost to get to this node
//  int astar_h; 
//};

template <typename NodeType>
class CompareAStarG
{
public:
  bool operator() (const NodeType* n1, const NodeType* n2) const
  {
    return n1->astar_g + n1->astar_h < n2->astar_g + n2->astar_h;
  }
};

template <typename Kind1, typename Kind2>
class PriorityQ: public multiset<Kind1, Kind2>
{
public:
  multiset<Kind1, Kind2>::iterator findItem(Kind1 k)
  {
    multiset<Kind1, Kind2>::iterator i;
    for (i=begin(); i!=end(); i++)
    {
      if ( (*i) == k)
      {
        return i;
      }
    }
    return end();
  }
};


template <typename NodeType, int MAX_CHILDREN>
class AStar
{
public:
  list<NodeType*> route;

  bool createRoute(NodeType* start, NodeType* end)
  {
    NodeType* children[MAX_CHILDREN];
    PriorityQ<NodeType*, CompareAStarG<NodeType> >::iterator found;
    set<NodeType*>::iterator sfound;


    start->astar_g = 0;
    start->astar_doH(end);
    start->astar_parent = 0;

    m_open.insert(start);

    end->astar_parent = 0;

    int c=0;
    NodeType* node = 0;

    while (m_open.size() > 0)
    {
      found = m_open.begin();
      node = *found;
      m_open.erase(found);

      if (node == end)
      {
        // found it!
        //logError(Inform, "route found");
        break;
      }

      int count = node->astar_children(children, MAX_CHILDREN, end);
      lassert(count <= MAX_CHILDREN && count >= 0);
      for (int c=0; c<count; c++)
      {
        NodeType* node_s = children[c];
        int tg = node->astar_g + node_s->astar_cost;

        // is it on the open list allready?
        found = m_open.findItem(node_s);
        if (found != m_open.end())
        {
          NodeType* foundNode = *found;
          if (foundNode->astar_g <= tg)
          {
            // the existing one is better or the same
            continue; 
          }
        }

        // is it on the closed list already?
        sfound = m_closed.find(node_s);
        if (sfound != m_closed.end())
        {
          NodeType* foundNode = *sfound;
          if (foundNode->astar_g <= tg)
          {
            // the existing one is better
            continue;
          }
          // remove it
          m_closed.erase(sfound);
        }

        if (found != m_open.end())
        {
          // remove it
          m_open.erase(found);
        }

        node_s->astar_parent = node;
        node_s->astar_g = tg;

        node_s->astar_doH(end);
        m_open.insert(node_s);
      }
      m_closed.insert(node);
//      node = 0;
    }

    if (node == 0)
    {
      return false;
    }
  
    while (node != start)
    {
      route.push_front(node);
      node = node->astar_parent;
    }

    return true;
  }

private:
  PriorityQ<NodeType*, CompareAStarG<NodeType> > m_open; // FIXME: needs to be a priority Q
  set<NodeType*> m_closed;

  NodeType* m_end;
  NodeType* m_start;
};


#endif