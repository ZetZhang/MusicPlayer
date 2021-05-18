#ifndef BES_TABLEVIEW_H
#define BES_TABLEVIEW_H

#include "NetAccess.h"
#include "BesTableModel.h"
#include "SongSearchResult.h"
#include "ThreadConvertMp3.h"
#include "BesButtonDelegate.h"

#include <QVector>
#include <QMenu>
#include <QTableView>

class BesTableView : public QTableView
{
    Q_OBJECT
public:
    explicit BesTableView(QWidget *parent = 0);
    ~BesTableView();

    BesTableModel* tableModel() {return m_model;}

public:
    void deleteAllItems();
    void appendItems(const QVector<SONGINFO>& infos);
    void setItems(const QVector<SONGINFO>& infos);

signals:
    // song
    void sig_oneDownloadStarted();
    void sig_oneDownloadFinished();
    void sig_showLrcLyric(const LyricInfo&);

public slots:
    void OnDownloadNcmMusic(SONGINFO songInfo);
    void OnSearchNcmLyric(SONGINFO songInfo); // 从歌曲结构中提取搜索信息去搜索歌词
    void OnFinishedDownload(QVariant, DOWNLOAD_FINISH_STATUS);
    void OnProgressChanged(QString speed, int percentage, QVariant data);

    void OnFinishConversion(int ncmId);

    void OnSearchListCustome(QPoint pos);
    void menuChoiceAction(QAction*);

protected:
    void initEntity();
    void initMenu();
    void initConnection();
//    void iniData(); // 歌词界面取消
    virtual void resizeEvent(QResizeEvent *event);

private:
    void BaseInit(); //基础的初始化
    QVector<SONGINFO> initSongInfo(const QVector<SONGINFO>& infos);

private:
    BesTableModel *m_model;
    BesButtonDelegate *m_buttonDelegate;
    NetworkAccess net;
    ThreadConvertMp3 mp3Converter;
    QMenu *m_menuSearchList;

    QString strLastSongName;
    QString strLastArtistName;
};

#endif // BES_NCM_SONG_TABLEVIEW_H
