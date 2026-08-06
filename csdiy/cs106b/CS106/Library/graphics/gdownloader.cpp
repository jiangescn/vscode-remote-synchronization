/*
 * 文件：gdownloader.cpp
 * ---------------------
 * 此文件实现 gdownloader.h 中声明的 GDownloader 类。
 * 各成员的声明和注释见 .h 文件。
 *
 * @author Marty Stepp
 * @version 2018/09/23
 * - 添加宏检查，以提高与旧 Qt 版本的兼容性
 * @version 2018/09/18
 * - 可用版本；修复了多个线程/Qt 信号问题
 * @version 2018/08/23
 * - 重命名为 gdownloader.cpp，以替代 Java 版本
 * @version 2018/08/03
 * - 初始版本
 */

#include "gdownloader.h"
#include <iomanip>
#include <iostream>
#include <QtGlobal>
#include <QFile>
#include <QIODevice>
#include <QTimer>
#include "error.h"
#include "gthread.h"

static int _sslSupported = -1;

GDownloader::GDownloader()
        : _manager(nullptr),
          _reply(nullptr),
          _httpStatusCode(0),
          _downloadComplete(false) {
            if (_sslSupported == -1) {
                _sslSupported = QSslSocket::supportsSsl();
            }
}

GDownloader::~GDownloader() {
    // TODO：删除
    _manager = nullptr;
    _reply = nullptr;
}

std::string GDownloader::downloadAsString(const std::string& url) {
    _url = url;
    _filename = "";
    _httpStatusCode = 0;
    _lastErrorMessage = "";

    // 在 GUI 线程上下载文件并阻塞/等待完成
    downloadInternal();

    // 将下载内容保存到字符串
    saveDownloadedData("downloadAsString");

    // 将下载的文本作为字符串返回（保存在成员变量中）
    return _filedata;
}

void GDownloader::downloadToFile(const std::string& url, const std::string& file) {
    _url = url;
    _filename = file;
    _httpStatusCode = 0;
    _lastErrorMessage = "";

    // 在 GUI 线程上下载文件并阻塞/等待完成
    downloadInternal();

    // 写入文件
    saveDownloadedData("downloadToFile", file);
}

void GDownloader::downloadInternal() {
    // 简陋的检查
    // 在不支持 SSL 时访问 https URL 注定失败，因此不要尝试
    if (!_sslSupported && _url.compare(0, 6, "https:") == 0) {
        reportNoSSL();
        return;
    }

    GThread::runOnQtGuiThreadAsync([this]() {

        if (!_manager) {
            _manager = new QNetworkAccessManager();
        }
        QNetworkRequest* request = new QNetworkRequest(QUrl(QString::fromStdString(_url)));

        for (std::string headerKey : _headers) {
            request->setRawHeader(QByteArray(headerKey.c_str()), QByteArray(_headers[headerKey].c_str()));
        }

        _reply = _manager->get(*request);

        // 这些函数似乎没有被调用，并且/或者我没有能触发它们的测试用例
        // 因此，与其让这里未经测试，我选择禁用
        //connect(_reply, &QNetworkReply::errorOccurred, this, &GDownloader::fileDownloadError);
        //connect(_reply, &QNetworkReply::sslErrors, this, &GDownloader::sslErrorsReply);
  });

    // 等待下载完成（在学生线程中）
    waitForDownload();
}

void GDownloader::fileDownloadError(QNetworkReply::NetworkError nerror) {
    error("file download error: " + std::to_string(nerror));
}

std::string GDownloader::getErrorMessage() const {
    return _lastErrorMessage;
}

int GDownloader::getHttpStatusCode() const {
    // 所有 HTTP 状态码都在 1xx 到 5xx（含）之间
    return _httpStatusCode >= 100 && _httpStatusCode <= 599 ? _httpStatusCode : 0;
}

std::string GDownloader::getHeader(const std::string& name) const {
    return _headers[name];
}

std::string GDownloader::getUserAgent() const {
    if (_headers.containsKey("User-Agent")) {
        return _headers["User-Agent"];
    } else {
        return "";
    }
}

bool GDownloader::hasError() const {
    if (_httpStatusCode != 0) {
        // 2xx 值表示成功
        return _httpStatusCode < 200 || _httpStatusCode > 299;
    } else {
        return !_lastErrorMessage.empty();
    }
}

std::string GDownloader::qtNetworkErrorToString(QNetworkReply::NetworkError nerror) {
    // http://doc.qt.io/qt-5/qnetworkreply.html#NetworkError-enum
    switch (nerror) {
    case QNetworkReply::ConnectionRefusedError: return "the remote server refused the connection (the server is not accepting requests)";
    case QNetworkReply::RemoteHostClosedError: return "the remote server closed the connection prematurely, before the entire reply was received and processed";
    case QNetworkReply::HostNotFoundError: return "the remote host name was not found (invalid hostname)";
    case QNetworkReply::TimeoutError: return "the connection to the remote server timed out";
    case QNetworkReply::OperationCanceledError: return "the operation was canceled via calls to abort() or close() before it was finished.";
    case QNetworkReply::SslHandshakeFailedError: return "the SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted.";
    case QNetworkReply::TemporaryNetworkFailureError: return "the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established.";
    case QNetworkReply::NetworkSessionFailedError: return "the connection was broken due to disconnection from the network or failure to start the network.";
    case QNetworkReply::BackgroundRequestNotAllowedError: return "the background request is not currently allowed due to platform policy.";
    case QNetworkReply::TooManyRedirectsError: return "while following redirects, the maximum limit was reached. The limit is by default set to 50 or as set by QNetworkRequest::setMaxRedirectsAllowed(). (This value was introduced in 5.6.)";
    case QNetworkReply::InsecureRedirectError: return "while following redirects, the network access API detected a redirect from a encrypted protocol (https) to an unencrypted one (http). (This value was introduced in 5.6.)";
    case QNetworkReply::ProxyConnectionRefusedError: return "the connection to the proxy server was refused (the proxy server is not accepting requests)";
    case QNetworkReply::ProxyConnectionClosedError: return "the proxy server closed the connection prematurely, before the entire reply was received and processed";
    case QNetworkReply::ProxyNotFoundError: return "the proxy host name was not found (invalid proxy hostname)";
    case QNetworkReply::ProxyTimeoutError: return "the connection to the proxy timed out or the proxy did not reply in time to the request sent";
    case QNetworkReply::ProxyAuthenticationRequiredError: return "the proxy requires authentication in order to honour the request but did not accept any credentials offered (if any)";
    case QNetworkReply::ContentAccessDenied: return "access denied";
    case QNetworkReply::ContentOperationNotPermittedError: return "the operation requested on the remote content is not permitted";
    case QNetworkReply::ContentNotFoundError: return "the remote content was not found at the server";
    case QNetworkReply::AuthenticationRequiredError: return "the remote server requires authentication to serve the content but the credentials provided were not accepted (if any)";
    case QNetworkReply::ContentReSendError: return "the request needed to be sent again, but this failed for example because the upload data could not be read a second time.";
    case QNetworkReply::ContentConflictError: return "the request could not be completed due to a conflict with the current state of the resource.";
    case QNetworkReply::ContentGoneError: return "the requested resource is no longer available at the server.";
    case QNetworkReply::InternalServerError: return "the server encountered an unexpected condition which prevented it from fulfilling the request.";
    case QNetworkReply::OperationNotImplementedError: return "the server does not support the functionality required to fulfill the request.";
    case QNetworkReply::ServiceUnavailableError: return "the server is unable to handle the request at this time.";
    case QNetworkReply::ProtocolUnknownError: return "the Network Access API cannot honor the request because the protocol is not known";
    case QNetworkReply::ProtocolInvalidOperationError: return "the requested operation is invalid for this protocol";
    case QNetworkReply::UnknownNetworkError: return "an unknown network-related error was detected";
    case QNetworkReply::UnknownProxyError: return "an unknown proxy-related error was detected";
    case QNetworkReply::UnknownContentError: return "an unknown error related to the remote content was detected";
    case QNetworkReply::ProtocolFailure: return "a breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)";
    case QNetworkReply::UnknownServerError: return "unknown server error";
    case QNetworkReply::NoError:
        break;
    }
    return "";
}

void GDownloader::saveDownloadedData(const std::string& member, const std::string& filename) {
    if (_reply) {
        QNetworkReply::NetworkError nerror = _reply->error();
        if (nerror) {
            // 连接失败；记录错误消息
            _lastErrorMessage = qtNetworkErrorToString(nerror);
        } else if (filename.empty()) {
            // 保存到字符串
            _filedata = _reply->readAll().toStdString();
        } else {
            // 保存到文件
            QFile outfile(QString::fromStdString(filename));
            if (!outfile.open(QIODevice::WriteOnly)) {
                error("GDownloader::" + member + ": cannot open file " + filename + " for writing");
            }
            outfile.write(_reply->readAll());
            outfile.close();
        }

        // 清理连接
        _reply->deleteLater();
        _reply = nullptr;
        _downloadComplete = true;
    }
}

void GDownloader::setHeader(const std::string& name, const std::string& value) {
    _headers[name] = value;
}

void GDownloader::setUserAgent(const std::string& userAgent) {
    setHeader("User-Agent", userAgent);
}

void GDownloader::sslErrorsReply(QList<QSslError>) {
    std::cout << "  DEBUG: sslErrors from NetworkReply" << std::endl;
}

void GDownloader::sslErrorsNam(QNetworkReply *reply, QList<QSslError>) {
    std::cout << "  DEBUG: sslErrors from NetworkAccessManager" << std::endl;
}

void GDownloader::reportNoSSL() {
    _downloadComplete = true;
    _lastErrorMessage = "No ssl support, unable to fetch secure url " + _url;
}

void GDownloader::waitForDownload() {
    // 等待下载完成
    while (!_downloadComplete) {
        GThread::getCurrentThread()->sleep(10);
        if (_reply && _reply->isFinished()) {
            _downloadComplete = true;
            break;
        }
    }

    // 获取 HTTP 状态码
    QVariant statusCode = _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid()) {
        _httpStatusCode = statusCode.toInt();
        _lastErrorMessage = _reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString().toStdString();
    } else {
        _httpStatusCode = -1;
        _lastErrorMessage = "Unable to connect to URL";
    }
}


