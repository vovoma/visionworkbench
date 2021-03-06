// __BEGIN_LICENSE__
// Copyright (C) 2006-2011 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


/// \file MinimumSpanningTree.h
///
/// Provides a minimum spanning tree data structure.
#ifndef __VW_MATH__MINIMUM_SPANNING_TREE_H__
#define __VW_MATH__MINIMUM_SPANNING_TREE_H__

// This is an implementation of Kruskal's algorithm. It is able to handle
// graphs with multiple connected components.

// The constructor builds the minimum spanning tree. The apply() method
// allows you to use the tree--it will call a user-defined function for
// every edge along a depth-first traversal of the tree beginning at a
// user-defined node. Note that, if the tree is not connected, other
// connected components will be processed by apply() after the connected
// component that contains the user-defined starting node.


namespace vw {
namespace math {

  class EdgePrimitive {
  public:
    EdgePrimitive() : default_cost(1.0) {}
    virtual ~EdgePrimitive() {}
    virtual const int &node1() const = 0;
    virtual const int &node2() const = 0;
    virtual const double &cost() const {return default_cost;}
  private:
    double default_cost;
  };

  class EdgePrimitiveFunctor {
  public:
    virtual ~EdgePrimitiveFunctor() {}
    virtual void operator()(EdgePrimitive *prim, int node_toward_root) = 0;
  };

  class MinimumSpanningTree {
  public:
    MinimumSpanningTree(int num_primitives_, EdgePrimitive **prims_);

    ~MinimumSpanningTree();

    void apply(EdgePrimitiveFunctor &func, int start_node);

  private:
    void apply_(EdgePrimitiveFunctor &func, int node, bool *visited);

  private:
    EdgePrimitive **prims;
    int num_primitives;
    bool *prim_used;
    int min_node;
    int num_nodes;
    bool *node_used;
    int *num_edges;
    EdgePrimitive ***edges;
  };

}} // namespace vw::math

#endif // __VW_MATH__MINIMUM_SPANNING_TREE_H__
