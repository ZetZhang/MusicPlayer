#pragma once

#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QQueue>
#include <QString>
#include <QFileInfo>
#include <QUrlQuery>
#include <QEventLoop>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

enum DOWNLOAD_FINISH_STATUS {
    NORMAL,
    NETEASE_MUSIC_NOT_FOUND,
    NET_WORK_ERROR,             //网络连接错误
    LOCAL_STORAGE_FAIL,         //本地存储失败
};

class DownloadInfo
{
public:
    QString  strUrl;
    QString  strSaveFilePath;
    QVariant data;
};

class NetworkAccess :public QObject
{
    Q_OBJECT
public:
    NetworkAccess() {  }

    bool DownloadFile(const QString strUrl, const QString strSaveAs, QVariant data);

    /* get 请求下载，下载完成后才返回 */
    static bool SyncDownloadString(const QString strUrl, QString& target, QUrlQuery query = QUrlQuery(),bool targetIsFile = false);
    /* post 请求下载，下载完成后才返回 */
    static bool SyncDownloadStringPost(const QString strUrl, QString& strSaveBuffer, QByteArray queryData = QByteArray());

signals:
    // 完成
    void finished();
    // 下载完成信号
    void sig_finishDownload(QVariant data, DOWNLOAD_FINISH_STATUS Status);
    // 下载进度信号
    void sig_progressChanged(QString speed, int percentage, QVariant data);
    // 下载错误信号
    void sig_netErrorWhenDownload(QVariant data);
    // 保存文件时文件打开错误信号
    void sig_fileOpenErrorWhenSave(QVariant data);

public slots:
    void replyFinished(QNetworkReply *reply);
    void onDownloadProgress(qint64 bytesSent,qint64 bytesTotal);
    void onReadyRead();

    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

public:

    QNetworkAccessManager manager;
    QQueue<DownloadInfo> downloadQueue;
    QNetworkReply *currentDownload;

    QFile output;
    QTime downloadTime;

    bool bDownloadResult;
    bool bDownloadFinish;
    QString* pStrBuffer;
};
