#include "game_generator.hpp"
#include "game.hpp"
#include "graph.hpp"
#include "graph_generator.hpp"

namespace uni_cpp_practice {

Game GameGenerator::generate() const {
  const auto graph_generator = GraphGenerator(params_);
  auto graph = graph_generator.generate();

  VertexId knight_position = graph.get_vertex_ids_at_depth(0).front();
  VertexId princess_position =
      graph.get_vertex_ids_at_depth(graph.get_depth()).front();

  auto game = Game(graph, knight_position, princess_position);
  return game;
}

}  // namespace uni_cpp_practice
