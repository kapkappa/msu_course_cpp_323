#pragma once

#include "game.hpp"
#include "graph.hpp"
#include "graph_generator.hpp"

namespace uni_cpp_practice {

class Game;

class GameGenerator {
 public:
  Game generate() const;

  GameGenerator(const GraphGenerator::Params& params) : params_(params) {}

 private:
  GraphGenerator::Params params_;
};

}  // namespace uni_cpp_practice
