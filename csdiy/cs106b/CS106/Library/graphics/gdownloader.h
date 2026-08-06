/*
 * 文件：gdownloader.h
 * -------------------
 * GDownloader 可以从 URL 下载数据并保存到文件，或返回
 * 将数据作为字符串。
 *
 * 请注意，由于下载器使用纯 C++ 实现，你的项目
 * 必须包含 Qt 的 'network' 组件才能正常工作。
 * 如果连接 HTTPS URL 时出现错误，可能还需要
 * 在系统上安装各种 SSL 软件包，例如 openssl、libssl-dev，
 * libssl1.0 等。具体取决于操作系统。
 *
 * 部分基于以下来源：
 * https://wiki.qt.io/Download_Data_from_URL
 *
 * @author Marty Stepp
 * @version 2018/09/18
 * - 可用版本；修复了多个线程/Qt 信号问题
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gdownloader.h，以替代 Java 版本
 * @version 2018/08/03
 * - 初始版本
 */


#ifndef _gdownloader_h
#define _gdownloader_h

#include <string>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "map.h"

/**
 * GDownloader 可以通过互联网连接下载文件和数据。
 * 它可以将数据保存到文件，或以字符串形式返回数据。
 */
class GDownloader : public QObject {
    Q_OBJECT

public:
    /**
     * 创建新的下载器。
     */
    GDownloader();

    /**
     * 释放下载器内部分配的内存。
     */
    virtual ~GDownloader();

    /**
     * 下载给定 URL 的文本内容，并以字符串形式返回。
     * 此方法会阻塞，直到数据下载完成。
     */
    std::string downloadAsString(const std::string& url);

    /**
     * 下载给定 URL 的文本内容，并保存到给定输出文件。
     * 此方法会阻塞，直到数据下载完成。
     */
    void downloadToFile(const std::string& url, const std::string& file);

    /**
     * 返回最近发生的 HTTP 错误消息。
     * 如果未发生 HTTP 错误，则返回 ""。
     */
    std::string getErrorMessage() const;

    /**
     * 返回此 URL 请求中给定 HTTP 标头的值。
     * 若未定义给定请求头，则返回空字符串。
     */
    std::string getHeader(const std::string& name) const;

    /**
     * 返回最近一次 HTTP 状态码，它可能表示成功
     * 状态码（例如 200）或错误码（例如 404）。若没有 HTTP 状态
     * 码可返回，则返回 0。
     */
    int getHttpStatusCode() const;

    /**
     * 返回此 URL 请求的 HTTP“User-Agent”标头值，
     * 如果未设置用户代理，则返回空字符串。
     */
    std::string getUserAgent() const;

    /**
     * 如果 HTTP 连接失败并发生错误，则返回 true。
     * 可以调用 getErrorMessage 查看具体错误。
     */
    bool hasError() const;

    /**
     * 向给定 URL 发起 HTTP GET 请求。
     * 以及之前指定的任何标头。
     */
    void httpGet(const std::string& url);

    /**
     * 向给定 URL 发起 HTTP POST 请求，
     * 提交之前指定的所有标头和查询参数。
     */
    void httpPost(const std::string& url);

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

signals:
    /**
     * 数据下载完成时会触发此 Qt 信号。
     */
    void downloaded();

private slots:
    void downloadInternal();
    void fileDownloadError(QNetworkReply::NetworkError);
    void reportNoSSL();
    void saveDownloadedData(const std::string& member, const std::string& filename = "");
    void sslErrorsNam(QNetworkReply*, QList<QSslError>);
    void sslErrorsReply(QList<QSslError>);
    void waitForDownload();
private:
    Q_DISABLE_COPY(GDownloader)

    static std::string qtNetworkErrorToString(QNetworkReply::NetworkError nerror);

    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
    Map<std::string, std::string> _headers;   // 要发送的 HTTP 请求头（名称 => 值）
    int _httpStatusCode;
    bool _downloadComplete;
    std::string _url;
    std::string _filename;
    std::string _filedata;
    std::string _lastErrorMessage;
};

#endif // _gdownloader_h
