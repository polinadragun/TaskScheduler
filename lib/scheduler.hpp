#pragma once
#include <vector>
#include "func_storage.hpp"
#include "node.hpp"
#include "any.hpp"

class TaskScheduler {
public:
    TaskScheduler() {};
    template<typename Func>
    size_t add(Func func) {
        FuncStorage tmp(func);
        tasks.push_back(Node(func));
        return size_++;
    }
    template<typename Func, typename Arg>
    size_t add(Func func, Arg a) {
        FuncStorage tmp(func, a);
        tasks.push_back(Node(func, a));
        return size_++;
    }

    template<typename Func, typename Arg1, typename Arg2>
    size_t add(Func func, Arg1 a, Arg2 b) {
        FuncStorage tmp(func, a, b);
        tasks.push_back(Node(func, a, b));
        return size_++;
    }
    void executeAll() {
        TopSort();
        for (int i = 0; i < ord.size(); ++i) {
            int point = ord[i];
            tasks[point - 1].perform_task();
        }
    }

    template <typename Arg>
    Arg getResult(size_t id) {
        return tasks[id].getResult().get<Arg>();
    }

    template <typename Arg>
    class FutureResultsObject {
    public:
        FutureResultsObject(size_t id, std::vector<Node>& tasks): id_(id), tasks_(tasks) {}
        operator Arg () const {
        return tasks_[id_].getResult().get<Arg>();
        }
        friend class Node;
    private:
        FuncStorage function_;
        std::vector<Node>& tasks_;
        size_t id_;
    };

    template <typename Arg>
    FutureResultsObject<Arg> getFutureResult (size_t id) {
        adj.resize(size_ + 2);
        adj[size_ + 1].push_back(id + 1);
        return FutureResultsObject<Arg>(id, tasks);
    }
    // void Check() {
    //     for (int i = 0; i < adj.size(); ++i) {
    //         std::cout << '\n';
    //         std::cout << i << " to ";
    //         for (int j = 0; j < adj[i].size(); ++j) {
    //             std::cout << adj[i][j] << " ";
    //         }
    //     }
    // }


private:
    std::vector<Node> tasks;
    size_t size_ = 0;
    std::vector<std::vector<size_t>> adj;
    std::vector<size_t> ord;
    std::vector<bool> visited;
    
    void Dfs(size_t point) {
        visited[point] = true;
        for (int i = 0; i < adj[point].size(); ++i) {
            if (!visited[adj[point][i]]) {
                Dfs(adj[point][i]);
            }
        }
        ord.push_back(point);
    }

    void TopSort() {
        visited.resize(size_ + 2, false);
        for (int i = adj.size() - 1; i > 0; --i) {
            if (!visited[i]) {
                Dfs(i);
            }
        }
    }
    
};
