#ifndef THREAD_CONVERT_MP3
#define THREAD_CONVERT_MP3

#include "NetAccess.h"
#include "MP3Editor/mp3Editor.h"

#include <QMutex>
#include <QQueue>
#include <QObject>
#include <QThread>
#include <QMessageBox>
#include <QMutexLocker>
#include <QSharedPointer>

#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>

class ConvertTask
{
public:
    QString sourceMp3FilePath;
    QString targetMp3FilePath;

    int songNcmId;

};

class NcmDetailInfo
{
public:
    int songId;
    QString title;
    QString artists;
    QString firstArtist;
    int albumId;
    QString album;
    QString albumPicUrl;
};

class Mp3Editor;

class ThreadConvertMp3 :public QThread
{
    Q_OBJECT

public:
    ThreadConvertMp3();
    void doTask(ConvertTask task);


signals:
    void sig_finishConvert(int ncmId);

private slots:
    void OnGetEditResultd(bool success, QString path, QString errorTip);
protected:

    virtual void run();

    bool downloadNcmInfo(int ncmId, NcmDetailInfo& info, QString& strLastResult);

    //获得结果中的歌曲信息列表
    bool GetSongInfoFromJson(QString strJsonRes, NcmDetailInfo& info);

private:

    QQueue<ConvertTask> taskQueue;
    Mp3Editor* mp3Editor;
    bool oneConvertDone;

};


#endif // THREAD_CONVERT_MP3
