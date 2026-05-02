#pragma once

#include <TrussC.h>
#include <chrono>
#include <iostream>
#include <string>

namespace tcx {

namespace console {
inline const char *reset() { return "\033[0m"; }
inline const char *bold()  { return "\033[1m"; }
inline const char *red()   { return "\033[31m"; }
inline const char *green() { return "\033[32m"; }
} // namespace console

class UnitTestsApp : public trussc::App {
public:
    void setup() override {
        auto start = std::chrono::high_resolution_clock::now();
        run();
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (num_failed_ == 0) {
            std::cout << std::endl
                      << console::bold() << console::green()
                      << num_passed_ << "/" << num_total_ << " tests passed"
                      << console::reset() << std::endl;
        } else {
            std::cout << std::endl
                      << console::bold() << console::red()
                      << num_failed_ << "/" << num_total_ << " tests failed"
                      << console::reset() << std::endl;
        }
        std::cout << "took " << ms << "ms" << std::endl;

        requestExit();
    }

    int failCount() const { return num_failed_; }

protected:
    virtual void run() = 0;

    bool test(bool condition, const std::string &name, const std::string &file, int line) {
        num_total_++;
        if (condition) {
            std::cout << console::bold() << console::green() << "[ PASS ] " << console::reset() << name << std::endl;
            num_passed_++;
            return true;
        }
        std::cout << console::bold() << console::red() << "[ FAIL ] " << console::reset() << name << std::endl;
        std::cout << "         at " << file << ":" << line << std::endl;
        num_failed_++;
        return false;
    }

    template<typename T1, typename T2>
    bool test_eq(T1 actual, T2 expected,
                 const std::string &v_actual, const std::string &v_expected,
                 const std::string &name, const std::string &file, int line) {
        num_total_++;
        if (actual == expected) {
            std::cout << console::bold() << console::green() << "[ PASS ] " << console::reset() << name << std::endl;
            num_passed_++;
            return true;
        }
        std::cout << console::bold() << console::red() << "[ FAIL ] " << console::reset() << name << std::endl;
        std::cout << "         expected: " << v_expected << " = " << expected << std::endl;
        std::cout << "         actual:   " << v_actual   << " = " << actual   << std::endl;
        std::cout << "         at " << file << ":" << line << std::endl;
        num_failed_++;
        return false;
    }

    template<typename T1, typename T2>
    bool test_gt(T1 actual, T2 expected,
                 const std::string &v_actual, const std::string &v_expected,
                 const std::string &name, const std::string &file, int line) {
        num_total_++;
        if (actual > expected) {
            std::cout << console::bold() << console::green() << "[ PASS ] " << console::reset() << name << std::endl;
            num_passed_++;
            return true;
        }
        std::cout << console::bold() << console::red() << "[ FAIL ] " << console::reset() << name << std::endl;
        std::cout << "         expected: " << v_actual << " > " << v_expected << std::endl;
        std::cout << "         actual:   " << actual << " <= " << expected << std::endl;
        std::cout << "         at " << file << ":" << line << std::endl;
        num_failed_++;
        return false;
    }

    template<typename T1, typename T2>
    bool test_lt(T1 actual, T2 expected,
                 const std::string &v_actual, const std::string &v_expected,
                 const std::string &name, const std::string &file, int line) {
        num_total_++;
        if (actual < expected) {
            std::cout << console::bold() << console::green() << "[ PASS ] " << console::reset() << name << std::endl;
            num_passed_++;
            return true;
        }
        std::cout << console::bold() << console::red() << "[ FAIL ] " << console::reset() << name << std::endl;
        std::cout << "         expected: " << v_actual << " < " << v_expected << std::endl;
        std::cout << "         actual:   " << actual << " >= " << expected << std::endl;
        std::cout << "         at " << file << ":" << line << std::endl;
        num_failed_++;
        return false;
    }

private:
    int num_total_ = 0;
    int num_passed_ = 0;
    int num_failed_ = 0;
};

template<typename AppClass>
int runTests() {
    AppClass app;
    app.setup();
    app.exit();
    return app.failCount();
}

} // namespace tcx

#define tcxTest(x, ...)      this->test(x, __VA_ARGS__, __FILE__, __LINE__)
#define tcxTestEq(x, y, ...) this->test_eq(x, y, #x, #y, __VA_ARGS__, __FILE__, __LINE__)
#define tcxTestGt(x, y, ...) this->test_gt(x, y, #x, #y, __VA_ARGS__, __FILE__, __LINE__)
#define tcxTestLt(x, y, ...) this->test_lt(x, y, #x, #y, __VA_ARGS__, __FILE__, __LINE__)
