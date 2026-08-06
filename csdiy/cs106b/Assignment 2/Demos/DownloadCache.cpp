#include "DownloadCache.h"
#include "urlstream.h"
using namespace std;

namespace {
    const string kBaseDir = "Downloads/";

    /* 用于计算哈希 ID 的稳定哈希函数。此哈希函数用于
     * 代替其他哈希函数，因为它能在不同程序运行之间计算一致 ID
     * 运行。
     *
     * 这是 Jenkins 32 位哈希函数。它不是现有的最佳哈希函数，
     * 但它是最容易实现的算法之一。它改编自
     * https://en.wikipedia.org/wiki/Jenkins_hash_function.
     */
    uint32_t jenkinsHashOf(const string& str) {
        uint32_t result = 0;
        for (char ch: str) {
            result += static_cast<unsigned char>(ch);
            result += result << 10;
            result ^= result >> 6;
        }
        result += result << 3;
        result ^= result >> 11;
        result += result << 15;
        return result;
    }

    /* 返回给定 URL/扩展名组合应使用的密钥文件和数据文件名称，
     * 分别地。
     */
    pair<string, string> filenamesFor(const string& url, const string& extension) {
        string hashBase = to_string(jenkinsHashOf(url));

        return make_pair(kBaseDir + hashBase + extension + ".key", kBaseDir + hashBase + extension + ".download");
    }

    /* 返回指定位置是否有给定 dot 字符串的缓存版本
     * 基础文件。
     */
    bool cachedVersionExistsFor(const string& url, const string& extension) {
        auto filenames = filenamesFor(url, extension);
        ifstream keyFile(filenames.first, ios::binary);
        ifstream dataFile(filenames.second, ios::binary);

        /* 如果文件不存在或无法打开，则没有任何内容可
         * 作为绘制起点。
         */
        if (!keyFile || !dataFile) return false;

        /* 确保密钥文件与 URL 完全匹配。 */
        ostringstream contents;
        contents << keyFile.rdbuf();
        return contents.str() == url;
    }

    /* 我们会多次尝试从服务器下载，因为有时 Google 服务器
     * 这些测试不稳定，有时会无缘无故失败。:-(
     */
    const size_t kMaxTries = 10;

    /* 下载给定 URL 的内容，并返回包含其内容的字符串
     * 字节。如果下载失败，将抛出 DownloadError。
     */
    string download(const string& url) {
        int lastErrorCode = 0;
        for (size_t i = 0; i < kMaxTries; i++) {
            iurlstream downloader;
            downloader.setHeader("User-Agent", "A programming assignment for Stanford's CS106B course. Contact: htiek@cs.stanford.edu");
            downloader.open(url);

            if (!downloader) {
                lastErrorCode = downloader.getErrorCode();
                continue;
            }

            ostringstream builder(ios::binary);
            builder << downloader.rdbuf();
            return builder.str();
        }

        throw DownloadError(lastErrorCode);
    }

    /* 尝试将给定字节写入磁盘缓存。这可能失败，在这种情况下
     * 情况下我们会静默失败。
     */
    void cacheBytes(const string& bytes, const string& url, const string& extension) {
        auto filenames = filenamesFor(url, extension);
        ofstream keyFile(filenames.first, ios::binary);
        ofstream dataFile(filenames.second, ios::binary);

        /* 这些文件可能未打开，也可能不可写。但我们将
         * 直接忽略它。
         */
        keyFile << url;
        dataFile << bytes;
    }
}

shared_ptr<istream>
webContentsOf(const string& url, const string& fileExtension,
              DownloadCallback callback) {
    /* 如果已有此 URL 的缓存版本，直接返回一个来自该缓存的流
     * 缓存。
     */
    if (cachedVersionExistsFor(url, fileExtension)) {
        auto filenames = filenamesFor(url, fileExtension);
        return make_shared<ifstream>(filenames.second, ios::binary);
    }

    /* 否则，我们没有缓存。下载它，并尽可能缓存。 */
    if (callback) callback(DownloadStatus::DOWNLOADING);
    auto bytes = download(url);
    if (callback) callback(DownloadStatus::FINISHED);

    /* 尝试将内容写入磁盘。这可能失败，我们会静默忽略。它
     * 令人烦恼，但不至于世界末日。
     */
    cacheBytes(bytes, url, fileExtension);

    /* 将字节包装在 istringstream 中。 */
    return make_shared<istringstream>(bytes, ios::binary);
}
