#pragma once
#include <coroutine>
#include <exception>

class Dialog {
public:
    struct promise_type {
        int current_value = 0;

        Dialog get_return_object() {
            return Dialog(std::coroutine_handle<promise_type>::from_promise(*this));
        }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void unhandled_exception() { throw; }

        std::suspend_always yield_value(int value) noexcept {
            current_value = value;
            return {};
        }

        void return_void() {}
    };

    using handle_type = std::coroutine_handle<promise_type>;

private:
    handle_type coro_;

public:
    Dialog(handle_type h) : coro_(h) {}
    Dialog(Dialog&& d) noexcept : coro_(d.coro_) { d.coro_ = nullptr; }
    ~Dialog() { if (coro_) coro_.destroy(); }

    int ask(int question) {
        coro_.promise().current_value = question;
        coro_.resume();
        return coro_.promise().current_value;
    }
};
