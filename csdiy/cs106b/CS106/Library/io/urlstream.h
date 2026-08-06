/*
 * 文件：urlstream.h
 * -----------------
 * 此文件导出 <code>iurlstream</code> 类，该类
 * 实现用于从 URL 读取数据的输入流。
 * 其实现只是对标准 C++ stringstream 的轻量包装。
 * 该实现先将 URL 数据下载到内存缓冲区，然后
 * 公开该内存缓冲区以供读取。
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
 * @version 2014/10/08
 * - 初始版本
 * @since 2014/10/08
 */


#ifndef _urlstream_h
#define _urlstream_h

#include <sstream>
#include <string>

#include "map.h"

/**
 * <code>iurlstream</code> 是用于从 URL 读取数据的输入流。
 * 其实现只是对标准 C++ stringstream 的轻量包装。
 * 将给定 URL 的数据下载到内存缓冲区，随后从中
 * 可以像读取其他输入流一样读取它。
 */
class iurlstream : public std::stringstream {
public:
    /**
     * 初始化一个未连接到任何源的新 iurlstream。
     * 若要设置 URL 的各种属性，请使用此构造函数
     * 下载前的连接设置（如用户代理或其他标头）。
     */
    iurlstream();

    /**
     * 初始化一个连接到给定源 URL 的新 iurlstream。
     * 立即下载该 URL 的数据。
     */
    iurlstream(const std::string& url);

    /**
     * 关闭流。
     * 此函数实际上什么也不做，仅为兼容旧版而保留
     * 用于兼容性。你无需调用它。
     */
    void close();

    /**
     * 返回最近收到的错误代码（如果有）。
     * 如果尚未发出错误代码，则返回 0。
     */
    int getErrorCode() const;

    /**
     * 返回最近一次错误的消息（如果有）。
     * 如果未发生错误，则返回 ""。
     */
    std::string getErrorMessage() const;

    /**
     * 返回最近一次 HTTP 状态码，它可能表示成功
     * 状态码（例如 200）或错误码（例如 404）。若没有 HTTP 状态
     * 码可返回，则返回 0。
     */
    int getHttpStatusCode() const;

    /**
     * 返回此 URL 请求中给定 HTTP 标头的值。
     * 若未定义给定请求头，则返回空字符串。
     */
    std::string getHeader(const std::string& name) const;

    /**
     * 返回传给流构造函数或最近一次调用的 URL
     * 传给 open(...)。
     */
    std::string getUrl() const;

    /**
     * 返回此 URL 请求的 HTTP“User-Agent”标头值，
     * 如果未设置用户代理，则返回空字符串。
     */
    std::string getUserAgent() const;

    /**
     * 打开给定 URL 进行读取。
     * 如果未传入 URL，则使用传给构造函数的 URL。
     */
    void open(const std::string& url = "");

    /**
     * 设置此 URL 请求中给定 HTTP 标头的值。
     * 必须在 open() 之前调用，并且该流必须使用以下方式创建：
     * 使用无参数构造函数。
     *
     * @example stream.setHeader("Referer", "http://cs106b.stanford.edu/");
     */
    void setHeader(const std::string& name, const std::string& value);

    /**
     * 设置此 URL 请求的 HTTP“User-Agent”标头值。
     * 必须在 open() 之前调用，并且该流必须使用以下方式创建：
     * 使用无参数构造函数。
     * 等价于调用 setHeader，并将 "User-Agent" 作为请求头名称。
     *
     * @example stream.setUserAgent("Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.4; en-US; rv:1.9.2.2) Gecko/20100316 Firefox/3.6.2");
     */
    void setUserAgent(const std::string& userAgent);

private:
    std::string _url;                         // 要打开的 URL
    int _httpStatusCode;                      // 最近一次 HTTP 错误（如果有；初始为 0）
    Map<std::string, std::string> _headers;   // 要发送的 HTTP 请求头（名称 => 值）
    std::string _errorMessage;                // 如果发生错误，说明具体原因的错误消息
};

/**
 * HTTP 返回码的常量。
 * @private
 */
typedef enum {
    // 客户端错误
    ERRHOST = -1,    // 不存在这样的主机
    ERRSOCK = -2,    // 无法创建套接字
    ERRCONN = -3,    // 无法连接到主机
    ERRWRHD = -4,    // 写入头部时发生套接字写入错误
    ERRWRDT = -5,    // 写入数据时发生套接字写入错误
    ERRRDHD = -6,    // 读取结果时套接字发生读取错误
    ERRPAHD = -7,    // 数据服务器返回了无效答案
    ERRNULL = -8,    // 空数据指针
    ERRNOLG = -9,    // 标头中没有长度或长度无效
    ERRMEM  = -10,   // 无法分配内存
    ERRRDDT = -11,   // 读取数据时发生错误
    ERRURLH = -12,   // 无效 URL——必须以 'http://' 开头
    ERRURLP = -13,   // URL 中的端口无效
    
    ERR_MALFORMED_URL = -42,
    ERR_IO_EXCEPTION = -43,


    // 服务器返回的代码
    ERR400 = 400,   // 无效查询
    ERR403 = 403,   // 禁止
    ERR408 = 408,   // 请求超时
    ERR500 = 500,   // 服务器错误
    ERR501 = 501,   // 尚未实现
    ERR503 = 503,   // 服务过载

    // 成功结果
    OK0 = 0,     // 解析成功
    OK201 = 201, // 资源创建成功
    OK200 = 200  // 资源读取成功

} http_retcode;

#endif // _urlstream_h
