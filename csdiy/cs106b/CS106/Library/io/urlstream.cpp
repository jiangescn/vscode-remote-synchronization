/*
 * 文件：urlstream.cpp
 * -------------------
 * 此文件包含 iurlstream 类的实现。
 * 有关这些类的使用方法，请参阅 urlstream.h。
 *
 * @author Marty Stepp
 * @version 2018/10/02
 * - 为向后兼容添加 close() 方法（不执行任何操作）
 * @version 2018/09/18
 * - 重构以集成纯 C++ 的 GDownloader 实现
 * - 添加 getErrorMessage 方法
 * @version 2018/06/20
 * - 支持设置 user agent 等请求头
 * - 支持 https URL
 * - 将 string 改为 const string&
 * @version 2015/07/05
 * - 移除全局静态 Platform 变量，改为在需要时调用 getPlatform
 * @version 2014/10/14
 * - 修复 ifstream::open() 调用中的 .c_str() Mac 错误
 * @since 2014/10/08
 */

#include "urlstream.h"
#include <sstream>
#include <string>
#include "error.h"
#include "filelib.h"
#include "gdownloader.h"
#include "strlib.h"

namespace {
    /*
     * 给定状态码，确定它是否表示成功。
     * 所有成功的 HTTP 状态码均为 2xx 形式。
     */
    bool isHttpSuccess(int code) {
        return code >= 200 && code <= 299;
    }
}

iurlstream::iurlstream()
        : _url(""),
          _httpStatusCode(0) {
    // 空
}

iurlstream::iurlstream(const std::string& url)
        : _url(url),
          _httpStatusCode(0) {
    open(url);
}

void iurlstream::close() {
    // 空
}

int iurlstream::getErrorCode() const {
    return isHttpSuccess(_httpStatusCode)? 0 : _httpStatusCode;
}

std::string iurlstream::getErrorMessage() const {
    return _errorMessage;
}

int iurlstream::getHttpStatusCode() const {
    /* 所有 HTTP 状态码都在 1xx 到 5xx（含）之间。 */
    return _httpStatusCode >= 100 && _httpStatusCode <= 599? _httpStatusCode : 0;
}

std::string iurlstream::getHeader(const std::string& name) const {
    return _headers[name];
}

std::string iurlstream::getUrl() const {
    return _url;
}

std::string iurlstream::getUserAgent() const {
    if (_headers.containsKey("User-Agent")) {
        return _headers["User-Agent"];
    } else {
        return "";
    }
}

void iurlstream::open(const std::string& url) {
    if (!url.empty()) {
        _url = url;
    }
    _errorMessage = "";
    
    // GDownloader 为我们完成下载文件的繁重工作
    GDownloader downloader;

    // 如果需要，插入/发送标头
    if (!_headers.isEmpty()) {
        for (std::string headerName : _headers) {
            downloader.setHeader(headerName, _headers[headerName]);
        }
    }
    std::string urlData = downloader.downloadAsString(_url);
    _httpStatusCode = downloader.getHttpStatusCode();

    if (downloader.hasError()) {
        setstate(std::ios::failbit);
        _errorMessage = downloader.getErrorMessage();
    } else {
        clear();
        this->write(urlData.c_str(), static_cast<std::streamsize>(urlData.length()));
        this->seekg(0);
    }
}

void iurlstream::setHeader(const std::string& name, const std::string& value) {
    _headers[name] = value;
}

void iurlstream::setUserAgent(const std::string& userAgent) {
    setHeader("User-Agent", userAgent);
}
