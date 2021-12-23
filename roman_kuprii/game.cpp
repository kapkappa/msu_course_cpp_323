#include "game.hpp"

#include "graph_traverser.hpp"

namespace uni_cpp_practice {

GraphTraverser::Path Game::find_shortest_path() const {
  GraphTraverser graph_traverser(map_);
  return graph_traverser.find_optimal_path(knight_position_, princess_position_,
                                           GraphTraverser::Criterion::Distance);
}

GraphTraverser::Path Game::find_fastest_path() const {
  GraphTraverser graph_traverser(map_);
  return graph_traverser.find_optimal_path(knight_position_, princess_position_,
                                           GraphTraverser::Criterion::Duration);
}

}  // namespace uni_cpp_practice
