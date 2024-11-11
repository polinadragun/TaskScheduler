#pragma once
#include "func_storage.hpp"
#include "any.hpp"

class Node {
public:
    template<typename Func>
    Node(const Func& input_func) : task_(input_func) {}

    template<typename Func, typename Arg>
    Node(const Func& input_func, const Arg& a) : task_(input_func, a) {}

    template<typename Func, typename Arg1, typename Arg2>
    Node(const Func& input_func, const Arg1& a, const Arg2& b) : task_(input_func, a, b) {}
    
    any getResult() const { return result_; }
    void setResult(const any& value) { result_ = value; }
    
    void perform_task() {
        result_ = task_();
    }

private:
    FuncStorage task_;
    any result_;
}; 
 
