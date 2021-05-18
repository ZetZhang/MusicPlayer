#ifndef SUBPAGEDOWNLOADSONG_H
#define SUBPAGEDOWNLOADSONG_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTabWidget>
#include <QMessageBox>

#include "BesButton.h"
#include "BesTableView.h"
#include "BesFileLineEdit.h"
#include "ThreadSearchNcmMusic.h"

class SubPageDownloadSong : public QWidget
{
    Q_OBJECT

public:
    SubPageDownloadSong(QWidget *parent = 0);
    ~SubPageDownloadSong() { }

    void initLayout();
    void initConnection();

public:
    void searchNcmDirectly(const QString& artists, const QString& song);

public slots:
    void OnSearchSong();

    void OnSongResultChanged(SongSearchResult result);
    //由于要求在下载过程中不能重新搜索歌曲，所以这里使用2个接口供外部调用，只有在没有下载任务时才启用搜索
    void onStartOneDownload();
    void onFinishOneDownload();

    // 歌词查看
    void OnShowLrcLyric(const LyricInfo &info);
    // 歌词保存
    void OnSaveLrcLyric();
    // 路径
    void OnSelectLrcLyricPath();
    // 文本框变化
    void OnLrcLyricPathChanged();

private:
    void showTipLabel(bool bShow);

private:
    int nCurrentDownloadCount;

public:
    QLabel* labelTitleSearchSong;
    QLabel* labelSearchNcmSong;
    QLabel* labelSearchNcmArtist;

    QLineEdit* editSearchNcmSong;
    QLineEdit* editSearchNcmArtist;

    BesButton* btnSearchNcmSong;
    QTabWidget* tabpageNcmSongResult;

    QLabel* labelNcmSongResultTip1;
    QLabel* labelNcmSongResultTip2;
    QLabel* labelNcmSongResultTip3;
    QLabel* labelNcmSongResultTip4;
    QLabel* labelNcmSongResultTip5;

    BesTableView* tableNcmSongSearch;

    // lyric
    QWidget* widgetLrcLyricBoard;
    QLabel* labelLrcLyricPanelSong;
    QLabel* labelLrcLyricPanelArtist;
    QLineEdit* editLrcLyricPanelSong;
    QLineEdit* editLrcLyricPanelArtist;
    BesButton* btnLrcLyricPanelSave;
    BesButton* btnLrcLyricPanelSelectPath;
    QTextEdit* editTextLrcLyric;
    QLabel* labelRawLyricPanelSavePath;
    BesFileLineEdit* editRawLyricPanelSavePath;

    ThreadSearchNcmMusic searchThread;

private:
    QString lastLyricPlainText;
};

#endif // SUBPAGEDOWNLOADSONG_H
