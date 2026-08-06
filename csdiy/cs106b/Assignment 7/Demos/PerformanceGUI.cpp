#include "ChainedHashTable.h"
#include "LinearProbingHashTable.h"
#include "RobinHoodHashTable.h"
#include "MyOptionalHashTable.h"
#include "GUI/MiniGUI.h"
#include "Timer.h"
#include "HashFunction.h"
#include "ginteractors.h"
#include "gthread.h"
#include <tuple>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <vector>
#include <random>
using namespace std;

namespace {
    /* 计时结果结构体。 */
    struct TimingResult {
        double insertSuccessTime;
        double insertFailTime;
        double lookupSuccessTime;
        double lookupFailTime;
        double removeSuccessTime;
        double removeFailTime;
    };

    /* 哈希 traits。 */
    template <typename Table> struct HashTraits;

    /* 用于导入定义的 X 宏。 */
    #define HASH_TABLE(type, desc)                \
        template <> struct HashTraits<type> {     \
            static string name() { return desc; } \
        };
    #include "TimeTestConfig.h"
    #undef HASH_TABLE

    template <typename...> struct TypeList {};

    /* 用于将类型添加到类型列表开头的元函数。 */
    template <typename Type, typename List> struct Prepend;
    template <typename Type, typename... Types> struct Prepend<Type, TypeList<Types...>> {
        using type = TypeList<Type, Types...>;
    };

    /* 用于从类型列表中删除最后一项的元函数。 */
    template <typename...> struct RemoveLast;
    template <typename T> struct RemoveLast<T> {
        using type = TypeList<>;
    };
    template <typename First, typename Second, typename... Rest> struct RemoveLast<TypeList<First, Second, Rest...>> {
        using type = typename Prepend<First, typename RemoveLast<TypeList<Second, Rest...>>::type>::type;
    };

    /* 所有可用表的列表。 */
    using AllHashTables = typename RemoveLast<TypeList<
        #define HASH_TABLE(type, desc) type,
        #include "TimeTestConfig.h"
        #undef HASH_TABLE
        void
    >>::type;

    /* 对所有表格类型应用某项操作。 */
    template <typename TestCase> void applyTo(TestCase&, TypeList<>) {
      /* 基本情况：没有类型可应用测试函数。 */
    }

    /* 递归情况：至少有一种类型需要测试。 */
    template <typename TestCase, typename HashTable, typename... HashTables>
    void applyTo(TestCase& testCase, TypeList<HashTable, HashTables...>) {
      /* 在此类型上调用测试函数 */
      testCase.template test<HashTable>();

      /* 递归调用 applyTo，并传入树列表的尾部
       * 类型。
       */
      applyTo<TestCase>(testCase, TypeList<HashTables...>());
    }

    class PerformanceGUI: public ProblemHandler {
    public:
        PerformanceGUI(GWindow& window);

        void settingUp() override;

    private:
        Temporary<GBrowserPane> mContent;

        void runAllTests();
        void displayResults(const vector<vector<TimingResult>>& results);
    };

    PerformanceGUI::PerformanceGUI(GWindow& window) : ProblemHandler(window) {
        mContent = make_temporary<GBrowserPane>(window, "CENTER");

        setDemoOptionsEnabled(false);
    }

    void PerformanceGUI::settingUp() {
        runAllTests();
        setDemoOptionsEnabled(true);
    }

    vector<string> loadEnglishWords() {
        ifstream input("res/EnglishWords.txt");
        return { istream_iterator<string>(input), istream_iterator<string>() };
    }

    const int kNumIterations = 10;

    template <typename Table> TimingResult timeTest(double loadFactor) {
        Timing::Timer constructionTimer;
        Timing::Timer insertSuccessTimer;
        Timing::Timer insertFailTimer;
        Timing::Timer lookupSuccessTimer;
        Timing::Timer lookupFailTimer;
        Timing::Timer removeSuccessTimer;
        Timing::Timer removeFailTimer;

        /* 加载所有英语单词。 */
        auto english = loadEnglishWords();

        /* 确定需要多少槽位。 */
        int numSlots = english.size() / loadFactor;

        /* 用于洗牌的随机源。 */
        mt19937 generator(randomInteger(0, INT_MAX));

        for (int iteration = 0; iteration < kNumIterations; iteration++) {
            constructionTimer.start();

            /* 这行代码构造哈希表。如果你有自定义哈希函数
             * 你希望在此使用，而不是我们标准选择的随机哈希函数。
             * 将此行改为
             *
             *    Table table(HashFunction<string>::wrap(numSlots, your-hash-function));
             */
            Table table(Hash::random(numSlots));
            constructionTimer.stop();

            for (string& word: english) {
                word = toLowerCase(word);
            }

            for (const auto& word: english) {
                insertSuccessTimer.start();
                if (!table.insert(word)) {
                    error("Couldn't insert \"" + word + "\" into the hash table.");
                }
                insertSuccessTimer.stop();

                insertFailTimer.start();
                if (table.insert(word)) {
                    error("Inserted duplicate word \"" + word + "\" into the hash table.");
                }
                insertFailTimer.stop();
            }

            /* 以随机顺序查询表中的所有项目。 */
            shuffle(english.begin(), english.end(), generator);

            for (const auto& word: english) {
                lookupSuccessTimer.start();
                if (!table.contains(word)) {
                    error("Couldn't locate word \"" + word + "\" in the hash table.");
                }
                lookupSuccessTimer.stop();
            }

            /* 查询不存在的内容。 */
            for (string& word: english) {
                word = toUpperCase(word);
            }

            for (const auto& word: english) {
                lookupFailTimer.start();
                if (table.contains(word)) {
                    error("Found word \"" + word + "\", which is not in the hash table.");
                }
                lookupFailTimer.stop();
            }

            /* 删除所有不存在的单词。 */
            shuffle(english.begin(), english.end(), generator);

            for (const auto& word: english) {
                removeFailTimer.start();
                if (table.remove(word)) {
                    error("Removed word \"" + word + "\", which is not in the hash table.");
                }
                removeFailTimer.stop();

                string toRemove = toLowerCase(word);
                removeSuccessTimer.start();
                if (!table.remove(toRemove)) {
                    error("Couldn't remove word \"" + word + "\", which is in the hash table.");
                }
                removeSuccessTimer.stop();
            }
        }


        return {
            insertSuccessTimer.elapsed()   / (english.size() * kNumIterations),
            insertFailTimer.elapsed()      / (english.size() * kNumIterations),
            lookupSuccessTimer.elapsed()   / (english.size() * kNumIterations),
            lookupFailTimer.elapsed()      / (english.size() * kNumIterations),
            removeSuccessTimer.elapsed()   / (english.size() * kNumIterations),
            removeFailTimer.elapsed()      / (english.size() * kNumIterations),
        };
    }

    /* 所有负载因子。 */
    const vector<double> kLoadFactors = {
        0.50,
        0.60,
        0.70,
        0.80,
        0.85,
        0.90,
        0.93,
        0.96,
        0.97,
    };

    /* 测试求值器——运行测试并保存结果。 */
    struct Evaluator {
        const double loadFactor;
        vector<TimingResult> results;

        Evaluator(double load) : loadFactor(load) {};

        template <typename Table> void test() {
            results.push_back(timeTest<Table>(loadFactor));
        }
    };

    /* 通用 printf。 */
    string format(const string& pattern) {
        /* 若存在替换位置，则说明出现了问题。 */
        if (pattern.find("%s") != string::npos) {
            error("Unmatched pattern string?");
        }
        return pattern;
    }

    string niceToString(double value) {
        ostringstream converter;
        converter << fixed << setprecision(2) << value;
        return converter.str();
    }

    template <typename First, typename... Args>
    string format(const string& pattern, First&& first, Args&&... args) {
        size_t toReplace = pattern.find("%s");
        if (toReplace == string::npos) {
            error("No pattern to replace?");
        }

        return    pattern.substr(0, toReplace)
                + to_string(std::forward<First>(first))
                + format(pattern.substr(toReplace + 2), args...);
    }

    const string kHTMLHeader =
            R"(<html>
                <head>
                </head>
                <body style="color:black;background-color:white;font-size:13pt;">)";

    const string kHTMLFooter =
            R"(</body></html>)";

    const string kTableIntro =
            R"(<table cellpadding="3" cellspacing="0" align="center">)";

    const string kTableOutro =
            R"(</table>)";

    /* 创建表格使用的标题。 */
    struct HeaderBuilder {
        ostream& out;
        template <typename Table> void test() {
            out << "<th>" << HashTraits<Table>::name() << "</th>";
        }
    };

    void makeTableHeader(ostream& out) {
        /* 为不需要标题的项预留两个空白条目。 */
        out << "<tr><th></th><th></th>";

        /* 为所有相关类型生成标题。 */
        HeaderBuilder builder{out};
        applyTo(builder, AllHashTables());

        out << "</tr>";
    }

    /* 关于如何访问每一行数据的信息。 */
    struct RowInfo {
        string title;
        double TimingResult::* field;
    };
    const vector<RowInfo> kRows = {
        { "Insert (success)", &TimingResult::insertSuccessTime },
        { "Insert (failure)", &TimingResult::insertFailTime    },
        { "Lookup (success)", &TimingResult::lookupSuccessTime },
        { "Lookup (failure)", &TimingResult::lookupFailTime    },
        { "Remove (success)", &TimingResult::removeSuccessTime },
        { "Remove (failure)", &TimingResult::removeFailTime    },
    };

    /* 空单元格中显示的值。 */
    const string kEmptyValue = "<i>waiting</i>";

    string styleFor(int row) {
        return format("background-color:%s;border: 3px solid black; border-collapse:collapse;",
                      row % 2 == 0? "#ffff80" : "white");
    }

    void makeTableRows(ostream& out,
                       const vector<vector<TimingResult>>& results,
                       size_t numCols) {
        /* 遍历所有负载因子，它们构成表格的各行。 */
        for (size_t row = 0; row < kLoadFactors.size(); row++) {
            out << format("<tr style=\"%s\">", styleFor(row));
            out << format("<td rowspan=\"%s\">&alpha; = ", kRows.size()) << kLoadFactors[row] << "</td>";

            for (size_t section = 0; section < kRows.size(); section++) {
                out << format("<td>%s</td>", kRows[section].title);

                for (size_t col = 0; col < numCols; col++) {
                    string value = (row < results.size()? niceToString(results[row][col].*kRows[section].field) + "ns" : kEmptyValue);
                    out << format("<td>%s</td>", value);
                }

                /* 奇怪的边界情况：由于我们预先为标题打开了一行，因此需要关闭
                 * 此行，然后如果后面还有一行，则重新打开一个。
                 */
                out << "</tr>";
                if (section + 1 != kRows.size()) out << format("<tr style=\"%s\">", styleFor(row));;
            }
        }
    }

    template <typename... Args>
    size_t sizeOf(TypeList<Args...>) {
        return sizeof...(Args);
    }

    void PerformanceGUI::displayResults(const vector<vector<TimingResult>>& results) {
        ostringstream builder;
        builder << kHTMLHeader << kTableIntro;

        makeTableHeader(builder);
        makeTableRows(builder, results, sizeOf(AllHashTables()));

        builder << kTableOutro << kHTMLFooter;

        /* 同步更新 HTML 显示，以免其他线程争用
         * 与我们一起。
         */
        GThread::runOnQtGuiThread([&] {
            mContent->setText(builder.str());
        });
    }

    void PerformanceGUI::runAllTests() {
        /* 所有测试结果的 Grid。 */
        vector<vector<TimingResult>> results;

        displayResults(results);
        for (double load: kLoadFactors) {
            Evaluator evaluator(load);
            applyTo(evaluator, AllHashTables());
            results.push_back(evaluator.results);
            displayResults(results);
        }
    }
}

GRAPHICS_HANDLER("Performance Analysis", GWindow& window) {
    return make_shared<PerformanceGUI>(window);
}

namespace {
    void printResults(const vector<TimingResult>& results, TypeList<>, size_t index) {
        if (index != results.size()) {
            error("Internal error: Size mismatch.");
        }
    }

    template <typename First, typename... Rest>
    void printResults(const vector<TimingResult>& results, TypeList<First, Rest...>, size_t index) {
        if (index >= results.size()) {
            error("Internal error: Size mismatch.");
        }

        cout << HashTraits<First>::name() << endl;
        for (auto row: kRows) {
            cout << "  " << row.title << ": " << results[index].*row.field << endl;
        }
        cout << endl;
        printResults(results, TypeList<Rest...>(), index + 1);
    }

    void displayResults(const vector<TimingResult>& results) {
        printResults(results, AllHashTables(), 0);
    }
}

CONSOLE_HANDLER("Performance Analysis") {
    for (double load: kLoadFactors) {
        cout << "Evaluating on load factor alpha = " << load << "..." << endl;
        Evaluator evaluator(load);
        applyTo(evaluator, AllHashTables());
        displayResults(evaluator.results);
    }
}
