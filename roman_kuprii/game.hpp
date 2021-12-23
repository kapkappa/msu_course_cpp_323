#pragma once

#include "graph_traverser.hpp"

namespace uni_cpp_practice {

class Game {
 public:
  // Traverse by `Distance`
  GraphTraverser::Path find_shortest_path() const;
  // Traverse by `Duration`
  GraphTraverser::Path find_fastest_path() const;

  Game(Graph _map,
       const VertexId& _knight_position,
       const VertexId& _princess_position)
      : map_(_map),
        knight_position_(_knight_position),
        princess_position_(_princess_position) {}

  const Graph& get_map() const { return map_; }

  const VertexId& get_knight_position() const { return knight_position_; }
  const VertexId& get_princess_position() const { return princess_position_; }

 private:
  Graph map_;
  VertexId knight_position_;
  VertexId princess_position_;
};

}  // namespace uni_cpp_practice
