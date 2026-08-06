/* 用于缓存从 Web 下载的文件版本的实用工具。 */
#ifndef DownloadCache_Included
#define DownloadCache_Included

#include <fstream>
#include <string>
#include <utility>
#include <memory>
#include <functional>

/* 表示下载状态的类型。 */
enum class DownloadStatus {
    DOWNLOADING,
    FINISHED
};

/* 用于报告进度的回调函数。 */
using DownloadCallback = std::function<void (DownloadStatus)>;

/* 给定 URL，返回包含该 URL 内容的流。此系统
 * 会尝试缓存内容，以免重复下载。
 *
 * 如果发生错误，将抛出 DownloadError 异常。
 *
 * 可以选择提供回调函数以接收状态更新。
 */
std::shared_ptr<std::istream>
webContentsOf(const std::string& url, const std::string& fileExtension,
              DownloadCallback callback = nullptr);

/* 表示下载错误的类型。它只是将下载错误向前传递。 */
class DownloadError {
public:
    DownloadError(int errorCode) : theErrorCode(errorCode) {

    }

    int errorCode() const {
        return theErrorCode;
    }

private:
    int theErrorCode;
};

#endif
