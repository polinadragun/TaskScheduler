#pragma once
#include <memory>
class any {
public:
    any() :value_p(nullptr) {}
    any(const any& other) {
        if (other.value_p) {
            value_p = other.value_p->clone();
        }
    }

    template<typename T>
    any(const T input) : value_p(new val<T>(input)) {}

    ~any() {
        delete value_p;
    }
    any& operator=(const any& other) {
        delete value_p;
        if (other.value_p) {
            value_p = other.value_p->clone();
        } else {
            value_p = nullptr;
        }
        return *this;
    }

    bool is_nullptr() const {
        if (this->value_p == nullptr) {
            return true;
        }
        return false;
    }

    template<typename T>
    T get() const {
        if (value_p) {
            auto typed_value_p = static_cast<val<T>*>(value_p);
            return typed_value_p->value;
        }
    }

private:
    class base_val {
    public:
        virtual ~base_val() = default;
        virtual base_val* clone() const = 0;
    };

    template<typename T>
    class val : public base_val {
    public:
        T value; 
        val(T input) {
            value = input;
        }
        base_val* clone() const override {
            return new val<T>(value);
        }
         
    };
    
    base_val* value_p = nullptr;

};
