#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "game.hpp"
#include "game_generator.hpp"
#include "graph.hpp"
#include "graph_generation_controller.hpp"
#include "graph_generator.hpp"
#include "graph_printing.hpp"
#include "graph_traversal_controller.hpp"
#include "graph_traverser.hpp"
#include "logger.hpp"
#include "logging_helping.hpp"

constexpr int GRAPHS_NUMBER = 0;
constexpr int INVALID_NEW_DEPTH = -1;
constexpr int INVALID_NEW_VERTICES_NUMBER = -1;
constexpr int INVALID_THREADS_NUMBER = 0;
const std::string LOG_FILENAME = "temp/log.txt";
const std::string DIRECTORY_NAME = "temp";

const int MAX_THREADS_COUNT = std::thread::hardware_concurrency();

using uni_cpp_practice::Game;
using uni_cpp_practice::GameGenerator;
using uni_cpp_practice::Graph;
using uni_cpp_practice::GraphGenerator;
using uni_cpp_practice::GraphTraverser;
using uni_cpp_practice::Logger;
using uni_cpp_practice::graph_generation_controller::GraphGenerationController;
using uni_cpp_practice::graph_traversal_controller::GraphTraversalController;

int handle_graphs_number_input() {
  int graphs_quantity = GRAPHS_NUMBER;
  do {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter amount of graphs to generate" << std::endl;
    std::cin >> graphs_quantity;
  } while (std::cin.fail() || graphs_quantity < GRAPHS_NUMBER);
  return graphs_quantity;
}

int handle_depth_input() {
  int depth = INVALID_NEW_DEPTH;
  do {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter generate graph depth from zero" << std::endl;
    std::cin >> depth;
  } while (std::cin.fail() || depth <= INVALID_NEW_DEPTH);
  return depth;
}

int handle_vertices_number_input() {
  int new_vertices_num = INVALID_NEW_VERTICES_NUMBER;
  do {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter new_vertices_num from zero" << std::endl;
    std::cin >> new_vertices_num;
  } while (std::cin.fail() || new_vertices_num < INVALID_NEW_VERTICES_NUMBER);
  return new_vertices_num;
}

int handle_threads_number_input() {
  int threads_count = INVALID_THREADS_NUMBER;
  do {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter threads number from zero to max_threads: "
              << MAX_THREADS_COUNT << std::endl;
    std::cin >> threads_count;
  } while (std::cin.fail() || threads_count <= INVALID_THREADS_NUMBER ||
           threads_count > MAX_THREADS_COUNT);
  return threads_count;
}

void prepare_temp_directory() {
  std::filesystem::create_directory(DIRECTORY_NAME);
}

std::vector<Graph> generate_graphs(Logger& logger,
                                   const int threads_count,
                                   const int graphs_count,
                                   const GraphGenerator::Params& params) {
  auto graphs = std::vector<Graph>();
  graphs.reserve(graphs_count);

  auto generation_controller =
      GraphGenerationController(threads_count, graphs_count, params);
  generation_controller.generate(
      [&logger](int index) {
        logger.log(uni_cpp_practice::logging_helping::write_log_start(index));
      },
      [&logger, &graphs](const Graph& graph, int index) {
        logger.log(
            uni_cpp_practice::logging_helping::write_log_end(graph, index));
        graphs.push_back(graph);
        uni_cpp_practice::logging_helping::write_graph(graph, index);
      });

  return graphs;
}

void traverse_graphs(const std::vector<Graph>& graphs,
                     Logger& logger,
                     const int threads_count) {
  auto traversal_controller = GraphTraversalController(threads_count, graphs);
  traversal_controller.traverse_graphs(
      [&logger](int index) {
        logger.log(
            uni_cpp_practice::logging_helping::write_traverse_start(index));
      },
      [&logger](int index, const std::vector<GraphTraverser::Path>& pathes) {
        logger.log(uni_cpp_practice::logging_helping::write_traverse_end(
            index, pathes));
      });
}

int main() {
  const int depth = handle_depth_input();
  const int new_vertices_num = handle_vertices_number_input();

  auto& logger = Logger::get_logger();
  prepare_temp_directory();
  logger.set_output(LOG_FILENAME);
  logger.log(uni_cpp_practice::logging_helping::game_preparing_string());

  const auto params = GraphGenerator::Params(depth, new_vertices_num);
  const auto game_generator = GameGenerator(params);
  const auto game = game_generator.generate();

  logger.log(uni_cpp_practice::logging_helping::game_ready_string(game));
  logger.log(
      uni_cpp_practice::logging_helping::shortest_path_searching_string());

  const auto shortest_path = game.find_shortest_path();

  logger.log(uni_cpp_practice::logging_helping::shortest_path_ready_string(
      shortest_path));
  logger.log(
      uni_cpp_practice::logging_helping::fastest_path_searching_string());

  const auto fastest_path = game.find_fastest_path();

  logger.log(uni_cpp_practice::logging_helping::fastest_path_ready_string(
      fastest_path));

  uni_cpp_practice::logging_helping::write_map(game.get_map());

  return 0;
}
