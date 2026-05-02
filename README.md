# tcxUnitTests

Unit testing framework for [TrussC](https://github.com/TrussC-org/TrussC) addons, modeled after [ofxUnitTests](https://github.com/openframeworks/openFrameworks/tree/master/addons/ofxUnitTests).

## Usage

```cpp
#include <TrussC.h>
#include <tcxUnitTests.h>

class TestApp : public tcx::UnitTestsApp {
    void run() override {
        tcxTest(1 + 1 == 2, "basic addition");
        tcxTestEq(std::string("hello").size(), 5u, "string length");
        tcxTestGt(10, 5, "greater than");
        tcxTestLt(5, 10, "less than");
    }
};

int main() {
    return tcx::runTests<TestApp>();
}
```

Add to your project's `addons.make`:
```
tcxUnitTests
```

## API

### Base Class

Inherit from `tcx::UnitTestsApp` and override `run()`.

### Macros

| Macro | Description |
|-------|-------------|
| `tcxTest(expr, name)` | Boolean assertion |
| `tcxTestEq(a, b, name)` | Equality (`a == b`) |
| `tcxTestGt(a, b, name)` | Greater than (`a > b`) |
| `tcxTestLt(a, b, name)` | Less than (`a < b`) |

### Exit Code

`tcx::runTests<App>()` returns the number of failed tests (0 = all passed). Use with CI:

```yaml
- run: ./testApp
  # non-zero exit code fails the step
```

## License

MIT
