#pragma once
#include <memory>
#include "any.hpp"

class FuncStorage {
public:
    FuncStorage() = default;

   template<typename Func>  
    FuncStorage(const Func& func)
        : callable_(new CallableImplZero<Func>(func)) {}

    template<typename Func, typename Arg>
    FuncStorage(const Func& func, const Arg& a)
        : callable_(new CallableImplOne<Func, Arg>(func, a)) {}

    template<typename Func, typename Arg1, typename Arg2>
    FuncStorage(const Func& func, const Arg1& a, const Arg2& b)
        : callable_(new CallableImplTwo<Func, Arg1, Arg2>(func, a, b)) {}

    any operator()() {
        return callable_->invoke();
    }

private:

    struct Callable {
        virtual ~Callable() = default;
        virtual any invoke() = 0;
    };

    template<typename Func>
    class CallableImplZero : public Callable {
    public:
        CallableImplZero(const Func& callable) : func_(callable) {}

        any invoke() override {
            return func_();
        }

    private:
        Func func_;
    };

    template<typename Func, typename Arg>
    class CallableImplOne : public Callable {
    public:
        CallableImplOne(const Func& callable, const Arg& a) : func_(callable), a_(a) {}

        any invoke() override {
            auto result = func(a_);
            return any(result);
        }

    private:
        Func func_;
        Arg a_;
    };

    template<typename Func, typename Arg1, typename Arg2>
    class CallableImplTwo : public Callable {
    public:
        CallableImplTwo(const Func& callable, const Arg1& a, const Arg2& b) : func_(callable), a_(a), b_(b) {}

        any invoke() override {
            auto result = func_(a_, b_);
            return any(result);
        }

    private:
        Func func_;
        Arg1 a_;
        Arg2 b_;
    };

    std::shared_ptr<Callable> callable_;
};
