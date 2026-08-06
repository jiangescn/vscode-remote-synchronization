#include "DisasterParser.h"
#include "strlib.h"
#include <regex>
using namespace std;

/* 这里的所有内容都是此文件私有的。 */
namespace {
    enum NameComponents {
        WholeString,
        CityName,
        XCoord,
        YCoord,
        NumComponents
    };

    /* 给定以下形式的城市信息
     *
     *     城市名称 (X, Y)
     *
     * 解析名称和 X/Y 坐标，并返回
     * 名称，并使用找到的内容填充 DisasterTest。
     */
    string parseCity(const string& cityInfo, DisasterTest& result) {
        /* 按所有分隔符拆分，并确认只得到
         * 三个分量。
         */
        regex  pattern("^([A-Za-z0-9 .\\-]+)\\(\\s*(-?[0-9]+(?:\\.[0-9]+)?)\\s*,\\s*(-?[0-9]+(?:\\.[0-9]+)?)\\s*\\)$");
        smatch components;
        string toMatch = trim(cityInfo);

        if (!regex_match(toMatch, components, pattern)) {
            error("Can't parse this data; is it city info? " + cityInfo);
        }

        /* 这里实际上有四个组成部分：整个匹配项、
         * 加上我们关心的每个子表达式。
         */
        if (components.size() != NumComponents) {
            error("Could not find all components?");
        }

        /* 我们会得到一些额外的前导或尾随
         * 此处有空白，因此将其去除。
         */
        string name = trim(components[CityName]);
        if (name.empty()) error("City names can't be empty.");

        /* 插入城市位置 */
        result.cityLocations[name] = {
            stringToReal(components[XCoord]),
            stringToReal(components[YCoord])
        };

        /* 向道路网络中插入该城市的条目。 */
        result.network[name] = {};
        return name;
    }

    /* 读取文件一行后半部分的出链，
     * 将它们添加到道路网络中。
     */
    void parseLinks(const string& cityName, const string& linksStr,
                    DisasterTest& result) {
        /* 可能不存在任何出链。 */
        if (trim(linksStr) == "") {
            result.network[cityName] = {};
            return;
        }

        auto components = stringSplit(linksStr, ",");
        for (const string& dest: components) {
            /* 清理所有空白，并确保没有
             * 发现一个空条目。
             */
            string cleanName = trim(dest);
            if (cleanName.empty()) {
                error("Blank name in list of outgoing cities?");
            }

            /* 确认这不是重复项。 */
            if (result.network[cityName].contains(cleanName)) {
                error("City appears twice in outgoing list?");
            }

            result.network[cityName] += cleanName;
        }
    }

    /* 解析文件中的一行，并使用其中内容更新网络
     * 它找到的内容。这只会按正向添加边，因为
     * 一种安全措施；稍后会反转边。
     */
    void parseCityLine(const string& line, DisasterTest& result) {
        /* 在行中搜索冒号。split 函数只会返回一个
         * 如果未指定任何出链，则只有一个组件。
         */
        auto numColons = count(line.begin(), line.end(), ':');
        if (numColons != 1) {
            error("Each data line should have exactly one colon on it.");
        }

        /* 将行拆分为城市名称/位置和列表
         * 出发城市。
         */
        auto components = stringSplit(line, ":");
        if (components.isEmpty()) {
            error("Data line appears to have no city information.");
        }

        /* 如果尚不存在，则创建一个虚拟的出发城市列表。 */
        if (components.size() == 1) components.add({});

        string name = parseCity(components[0], result);

        parseLinks(name, components[1], result);
    }

    /* 给定所有正向边都已添加的图，添加
     * 图中的反向边。
     */
    void addReverseEdges(DisasterTest& result) {
        for (const string& source: result.network) {
            for (const string& dest: result.network[source]) {
                if (!result.network.containsKey(dest)) {
                    error("Outgoing link found to nonexistent city '" + dest + "'");
                }
                result.network[dest] += source;
            }
        }
    }

    /* 给定一个图，确认所有节点位于不同位置。 */
    void validateLocations(const DisasterTest& test) {
        Map<GPoint, string> locations;
        for (auto loc: test.cityLocations) {
            if (locations.containsKey(test.cityLocations[loc])) {
                throw runtime_error(loc + " is at the same location as " + locations[test.cityLocations[loc]]);
            }
            locations[test.cityLocations[loc]] = loc;
        }
    }
}

/**
 * 给定指向 Disaster Preparation 测试用例的流，
 * 从该测试用例中提取数据。
 *
 * @param source 包含测试用例的流。
 * @return 从文件读取的测试用例。
 * @throws 如果发生错误或文件无效，则抛出 ErrorException。
 */
DisasterTest loadDisaster(istream& source) {
    DisasterTest result;

    for (string line; getline(source, line); ) {
        /* 跳过空行或注释。 */
        if (trim(line).empty() || startsWith(line, "#")) continue;

        parseCityLine(line, result);
    }

    addReverseEdges(result);
    validateLocations(result);
    return result;
}
