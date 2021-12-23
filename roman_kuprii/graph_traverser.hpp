#pragma once

#include <mutex>
#include <optional>
#include <vector>

#include "graph.hpp"

namespace uni_cpp_practice {

class Graph;

class GraphTraverser {
 public:
  using Distance = int;

  enum class Criterion { Distance, Duration };

  struct Path {
    Path(std::vector<VertexId> _vertex_ids,
         Distance _distance,
         Edge::Duration _duration,
         Criterion _criterion)
        : vertex_ids(_vertex_ids),
          distance(_distance),
          duration(_duration),
          criterion(_criterion) {}
    std::vector<VertexId> vertex_ids;
    Distance distance = 0;
    Edge::Duration duration = 0;
    Criterion criterion;
  };

  std::vector<Path> traverse_graph();

  Path find_optimal_path(const VertexId& source_vertex_id,
                         const VertexId& destination_vertex_id,
                         Criterion criterion) const;

  GraphTraverser(const Graph& graph) : graph_(graph) {}

 private:
  const Graph& graph_;
};

}  // namespace uni_cpp_practice
