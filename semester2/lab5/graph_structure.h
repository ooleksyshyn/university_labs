#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

class graph{
public:
    explicit graph(bool is_oriented = false, bool is_weighted = false) : oriented(is_oriented),
                                                                         weighted(is_weighted){}
    virtual void add_node(std::vector<std::pair<long long, long long>>) = 0;
    virtual void add_rib(long long, long long, long long = 1) = 0;
    virtual void add_node(std::vector<long long>) = 0;
    virtual bool is_weighted() const = 0;
    virtual bool is_oriented() const = 0;
    virtual void print() const = 0;
    virtual bool connected() const = 0;
    using Lambda = std::function<void(graph&, long long)>;
    virtual void width_go_through(long long, Lambda) = 0;
    virtual std::vector<long long> top_sort() const = 0;
    virtual std::vector<std::vector<int>> floyd_algorithm() const = 0;
    virtual void width_go_through_first_min_weight(long long, Lambda) = 0;
    virtual long long total_weight()const = 0;
    virtual void generate_random(long long) = 0;

protected:
    bool oriented;
    bool weighted;
};

int RandomInt(int, int);