#pragma once

#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <queue>
#include <random>

namespace lab {

    template <typename T>
    auto distance (const T& lhs, const T& rhs) {
        static std::mt19937 gen (std::random_device{}());
        static std::uniform_int_distribution <std::size_t> dis (0, 10);
        return dis(gen);
    }

    template <typename T>
    class Graph {
    public:
        struct Edge {
            std::size_t from;
            std::size_t to;
            std::size_t weight;
        };

    public:

        Graph (std::initializer_list<T> elems)
            : _vertices {elems}
        {}

        void add_vertice (const T& value) {
            _vertices.push_back(value);
        }

        void add_edge (const std::size_t from, const std::size_t to) {
            _edges.push_back({from, to,
                                distance(_vertices.at(from), _vertices.at(to))});
        }

        template <typename Iter>
        void add_edges (Iter begin, Iter end) {
            _edges.reserve(std::distance(begin, end));

            for (; begin != end; ++begin) {
                _edges.push_back(*begin);
            }
        }

        void remove_vertice (std::size_t index) {
            _vertices.erase(_vertices.begin() + index);
            _edges.erase (std::remove_if(_edges.begin(), _edges.end(),
                    [index] (const auto& edge) {
                          return edge.from == index || edge.to == index;
                    }), _edges.end()
                    );
        }

        template <typename Iter>
        void remove_edges (Iter begin, Iter end) {
            _edges.erase(begin, end);
        }

        [[nodiscard]]
        auto& vertices() const noexcept {
            return _vertices;
        }

        [[nodiscard]]
        auto& edges() const noexcept {
            return _edges;
        }

        private:
            std::vector <T> _vertices;
            std::vector <Edge> _edges;
    };

    template <typename T>
    auto bellman_ford (const Graph<T>& graph, const std::size_t src) -> std::vector<std::size_t> {

        constexpr auto inf_dist = std::numeric_limits<std::size_t>::max();
        std::vector<std::size_t> dists (graph.vertices().size(), inf_dist);     /// distances to vertices
        dists.at(src) = 0;

        for (int i = 0; i < graph.edges().size() - 1; ++i) {
            for (const auto& [from, to, weight] : graph.edges()) {
                if (dists[from] != inf_dist && dists[from] + weight < dists[to]) {
                    dists[to] = dists[from] + weight;
                }
            }
        }
        for (const auto& [from, to, weight] : graph.edges()) {
            if (dists[from] != inf_dist && dists[from] + weight < dists[to]) {
                throw std::logic_error{"Graph contains negative weight cycle"};
            }
        }

        return dists;
    }

    template <typename T>
    auto dijkstra (const Graph<T>& graph, const std::size_t src) -> std::vector<std::size_t> {

        constexpr auto inf_dist = std::numeric_limits<std::size_t>::max();

        std::priority_queue <std::pair <std::size_t, std::size_t>,
                             std::vector<std::pair <std::size_t, std::size_t>>,
                             std::greater<>> elems;
        std::vector<std::size_t> dists (graph.vertices().size(), inf_dist);

        dists[src] = 0;
        elems.emplace(0, src);

        while (!elems.empty()) {
            auto u = elems.top().second;
            elems.pop();

            for (const auto& [from, to, weight] : graph.edges()) {
                if (from == u &&
                    dists[from] != inf_dist &&
                    (dists[to] == inf_dist || dists[to] > dists[from] + weight)) {

                    dists[to] = dists[from] + weight;
                    elems.emplace(dists[to], to);
                }
            }
        }
        return dists;
    }

    template <typename T>
    auto johnson_paths (Graph<T> graph) -> std::vector<std::vector<std::size_t>> {

        /// Adding zero vertice
        graph.add_vertice(T{});
        for (int i = 0; i < graph.vertices().size() - 1; ++i) {
            graph.add_edge(graph.vertices().size() - 1, i);
        }
        const auto bellman_dists = bellman_ford(graph, graph.vertices().size() - 1);

        auto edges = graph.edges();

        // Reweighting
        for (auto& [from, to, weight] : edges) {
            weight = weight + bellman_dists[from] - bellman_dists[to];
        }

        /// Setting new edges in graph
        graph.remove_edges(graph.edges().begin(), graph.edges().end());
        graph.add_edges(edges.begin(), edges.end());

        // Removing zero vertice
        graph.remove_vertice(graph.vertices().size() - 1);

        std::vector<std::vector<std::size_t>> result;
        result.reserve (graph.vertices().size());

        for (int i = 0; i < graph.vertices().size(); ++i) {
            result.push_back(dijkstra(graph, i));
        }
        return result;
    }
}
