#include "SimpleTest.h"
#include <string>
using namespace std;

namespace SimpleTest {
    namespace Internal {
        /* 为何使用此类型？因为我们希望能够
         *
         * 1. 找出某个组中的所有测试，并
         * 2. 按行号对它们排序。
         */
        map<TestKey, multimap<int, TestCase>>& rawTests() {
            static map<TestKey, multimap<int, TestCase>> result;
            return result;
        }

        void doFail(const string& message, size_t line) {
            throw TestFailedException(message, line);
        }
        void doExpect(bool condition, const string &expression, size_t line) {
            if (!condition) {
                doFail(expression, line);
            }
        }

        void showError(const std::string& message, size_t line) {
            doFail(message, line);
        }

        /* TestFailedException 实现。 */
        TestFailedException::TestFailedException(const string& message, std::size_t line)
            : logic_error("Line " + to_string(line) + ": " + string(message)) {

        }

        /* TestCaseAdder 实现。 */
        TestCaseAdder::TestCaseAdder(const TestKey& key, int line, const string& name, TestType type, std::function<void()> test) {
            rawTests()[key].insert(make_pair(line, TestCase{ name, type, line, test }));
        }
    }
}
