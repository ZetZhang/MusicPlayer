#include "myQSS.h"
#include "NetAccess.h"
#include "BesTableView.h"
#include "BesTableModel.h"
#include "SettingManager.h"
#include "SearcherNetEaseCloud.h"

#include <QUrl>
#include <QDir>
#include <QScrollBar>
#include <QHeaderView>
#include <QMessageBox>
#include <QDesktopServices>

BesTableView::BesTableView(QWidget *parent) :
    QTableView(parent)
{
    this->setMouseTracking(true);//详见 BesFramelessWidget.h 注释

    initEntity();
    initConnection();
    initMenu();
    BaseInit();
}

BesTableView::~BesTableView()
{
    delete m_model;
}

void BesTableView::deleteAllItems()
{
    m_model->deleteAllItems();
    emit m_model->layoutChanged();
    this->update();
}

void BesTableView::appendItems(const QVector<SONGINFO> &infos)
{
    QVector<SONGINFO> infos_dealed = initSongInfo(infos);

    m_model->appendItems(infos_dealed);
    emit m_model->layoutChanged();
    this->update();
}

void BesTableView::setItems(const QVector<SONGINFO> &infos)
{
    QVector<SONGINFO> infos_dealed = initSongInfo(infos);

    m_model->deleteAllItems();
    m_model->appendItems(infos_dealed);
    emit m_model->layoutChanged();
    this->update();
}

void BesTableView::OnDownloadNcmMusic(SONGINFO songInfo)
{
    QString downloadPath = SettingManager::GetInstance().getDownlaodPath();
    QDir DataDir(downloadPath);

    if(!DataDir.exists())
        if(!DataDir.mkpath(downloadPath))
            QMessageBox::about(Q_NULLPTR, "提示", tr("无法为配置创建目录")+":" + downloadPath);

    //构建本地文件路径
    LyricInfo lyricInfo;
    SearcherNetEaseCloud search;

    QString localFileName = songInfo.strSong +" - "+ songInfo.strArtists;
    localFileName = localFileName.replace(QRegExp("[\\/\\\\\\|\\*\\?<>\\:\"]"), "_"); //将文件不允许出现的字符替换为下划线

    QString strSavePath = downloadPath + '/' + localFileName + ".mp3";
    QString strTempSavePath = downloadPath + '/' + localFileName + "temp.mp3";
    QString strLyricSavePath = downloadPath + '/' + localFileName + ".lrc";

    if (songInfo.nPercentage == -1) { //只有从未下载过时，才尝试下载
        emit sig_oneDownloadStarted();

        OnProgressChanged("0 kB/s", 5,QVariant(songInfo.nID)); //先发一个信号，让界面有所显示

        QString strId = QString().number(songInfo.nID);
        QString strLink = "http://music.163.com/song/media/outer/url?id="+ strId +".mp3";
        net.DownloadFile(strLink, strTempSavePath, songInfo.nID);

        bool bShowUnexpectedResultTip = search.SearchLyric(songInfo, lyricInfo);

        if (!lyricInfo.strLabelText.isEmpty()) {
            QFile fileOut(strLyricSavePath);
            if (! fileOut.open(QFile::WriteOnly | QFile::Truncate)) {
                QMessageBox::information(Q_NULLPTR, tr("失败提示"), tr("无法保存文件:")+ strLyricSavePath +"\n\n可能是程序没有写权限");
                return;
            }

            QTextStream streamFileOut(&fileOut);
            streamFileOut.setCodec("UTF-8");
            streamFileOut.setGenerateByteOrderMark(false);
            streamFileOut << lyricInfo.strLabelText;
            streamFileOut.flush();

            fileOut.close();
        }
    } else if (songInfo.nPercentage == -2) {
        //已经尝试过，404 找不到音乐，应该是没版权
        QMessageBox::about(Q_NULLPTR, "提示", "由于版权保护等原因，无法获取该音乐");
    } else if (songInfo.nPercentage == -3) {
        //表示网络连接错误
        QMessageBox::about(Q_NULLPTR, "提示", "网络连接错误");
    } else if (songInfo.nPercentage == -4) {
        //表示本地存储失败
        QMessageBox::about(Q_NULLPTR, "提示", "本地存储失败，可能是文件名包含非法字符或其他无法写文件的原因导致");
    }
}

// FIXME：完善歌词搜索，直接emit
void BesTableView::OnSearchNcmLyric(SONGINFO songInfo)
{
    LyricInfo lyricInfo;
//    SearcherNetEaseCloud search;
    QSharedPointer<ISearcher> search = QSharedPointer<ISearcher>(new SearcherNetEaseCloud());

    bool bShowUnexpectedResultTip = search->SearchLyric(songInfo, lyricInfo);

    emit (sig_showLrcLyric(lyricInfo));
}

void BesTableView::OnFinishedDownload(QVariant data, DOWNLOAD_FINISH_STATUS status)
{
    QString downloadPath = SettingManager::GetInstance().getDownlaodPath();
    emit sig_oneDownloadFinished();

    int nSongId = data.toInt();

    QVector<SONGINFO>& infos =m_model->DataVector();
    for (SONGINFO& info: infos) {
        if (info.nID == nSongId) {
            if (status == DOWNLOAD_FINISH_STATUS::NORMAL) {
                info.nPercentage = 99; //100

                //接下来下载mp3图片等信息写入mp3中
                QString localFileName = info.strSong +" - "+ info.strArtists;
                localFileName = localFileName.replace(QRegExp("[\\/\\\\\\|\\*\\?<>\\:\"]"), "_"); //将文件不允许出现的字符替换为下划线

                QString strSavePath = downloadPath + '/' + localFileName + ".mp3";
                QString strTempSavePath = downloadPath + '/' + localFileName + "temp.mp3";

                ConvertTask task;
                task.songNcmId = nSongId;
                task.sourceMp3FilePath = strTempSavePath;
                task.targetMp3FilePath = strSavePath;
                mp3Converter.doTask(task);

            } else if (status == DOWNLOAD_FINISH_STATUS::NETEASE_MUSIC_NOT_FOUND) {
                info.nPercentage = -2;
            } else if (status == DOWNLOAD_FINISH_STATUS::NET_WORK_ERROR) {
                info.nPercentage = -3;
            } else {
                info.nPercentage = -4;
            }
            update();
        }
    }
}


void BesTableView::OnFinishConversion(int ncmId)
{
    QVector<SONGINFO> &infos = m_model->DataVector();
    for(SONGINFO& info: infos)
    {
        if(info.nID == ncmId)
        {
            info.nPercentage = 100;
            update();
            break;
        }
    }
}

void BesTableView::OnProgressChanged(QString speed, int percentage, QVariant data)
{
    Q_UNUSED(speed);

    int nSongId = data.toInt();

    QVector<SONGINFO>& infos = m_model->DataVector();
    for(SONGINFO& info: infos)
    {
        if(info.nID == nSongId)
        {
            info.nPercentage = percentage < 5 ? 5: percentage;  //为了用户不因网络卡顿而看不到任何进度，最小显示5

            update();
        }
    }
}

/**
 * @brief  initEntity 
 */
void BesTableView::initEntity()
{
    m_model = new BesTableModel();
    this->setModel(m_model);

    QStringList headers;
    headers << "" << tr("操作") << tr("音乐标题") << tr("歌手") << tr("专辑") << tr("时长");
    m_model->setHorizontalHeader(headers);
    m_buttonDelegate = new BesButtonDelegate(this);
    this->setItemDelegateForColumn(1, m_buttonDelegate);
}

/**
 * @brief  OnSearchListCustome 执行右键菜单
 *
 * @param  pos
 */
void BesTableView::OnSearchListCustome(QPoint pos)
{
    if (this->indexAt(pos).isValid())
        m_menuSearchList->exec(QCursor::pos());
}

/**
 * @brief  initMenu 初始化右键菜单
 */
void BesTableView::initMenu()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction *action_searchlist_view = new QAction(QIcon(":/image/image/image/view_music_normal_white.png"), u8"查看歌曲");
    QAction *action_searchlist_listen = new QAction(QIcon(":/image/image/image/listen_music_normal_white.png"), u8"试听歌曲");
    QAction *action_searchlist_download = new QAction(QIcon(":/image/image/image/download_music_item_normal_white.png"), u8"下载歌曲");
    QAction *action_searchlist_download_lyric = new QAction(QIcon(":/image/image/image/download_lyric_item_normal_white.png"), u8"查看歌词");
    m_menuSearchList = new QMenu(this);
    m_menuSearchList->addAction(action_searchlist_view);
    m_menuSearchList->addAction(action_searchlist_listen);
    m_menuSearchList->addAction(action_searchlist_download);
    m_menuSearchList->addAction(action_searchlist_download_lyric);
    m_menuSearchList->setStyleSheet(tableViewMenuStyle());
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnSearchListCustome(QPoint)));
    connect(m_menuSearchList, SIGNAL(triggered(QAction *)), this, SLOT(menuChoiceAction(QAction*)));
}

void BesTableView::menuChoiceAction(QAction *action)
{
    QString action_text = action->text();

    QModelIndex index = currentIndex();
    SONGINFO info = m_model->DataVector().at(index.row());
    QString current_data_nid = QString().number(info.nID);

    if (action_text == "查看歌曲") {
        QString strLink = "http://music.163.com/#/song?id=" + current_data_nid;
        QDesktopServices::openUrl(QUrl(strLink));
    } else if (action_text == "试听歌曲") {
        QString strLink = "http://music.163.com/song/media/outer/url?id=" + current_data_nid;
        QDesktopServices::openUrl(QUrl(strLink));
    } else if (action_text == "下载歌曲") {
        OnDownloadNcmMusic(info);
    } else if (action_text == "查看歌词") {
        OnSearchNcmLyric(info);
    }
}

/**
 * @brief  initConnection 连接信号槽
 */
void BesTableView::initConnection()
{
    connect(m_buttonDelegate, &BesButtonDelegate::sig_rowClicked, this, &BesTableView::selectRow);
    connect(m_buttonDelegate, &BesButtonDelegate::sig_preview_ncm_song, [=](int row){
       QString strLink = "http://music.163.com/#/song?id=" + QString().number(m_model->DataVector().at(row).nID);
       QDesktopServices::openUrl(QUrl(strLink));
    });
    connect(m_buttonDelegate, &BesButtonDelegate::sig_listen_ncm_song, [=](int row){
       QString strLink = "http://music.163.com/song/media/outer/url?id=" + QString().number(m_model->DataVector().at(row).nID);
       QDesktopServices::openUrl(QUrl(strLink));
    });
    // download song
    connect(m_buttonDelegate, &BesButtonDelegate::sig_download_ncm_song, [=](int row){
        OnDownloadNcmMusic(m_model->DataVector().at(row));
    });
    // search lyric
    connect(m_buttonDelegate, &BesButtonDelegate::sig_search_ncm_lyric, [=](int row){
        OnSearchNcmLyric(m_model->DataVector().at(row));
    });

    connect(&net, &NetworkAccess::sig_finishDownload, this, &BesTableView::OnFinishedDownload);
    connect(&net, &NetworkAccess::sig_progressChanged, this, &BesTableView::OnProgressChanged);

    connect(&mp3Converter, &ThreadConvertMp3::sig_finishConvert, this, &BesTableView::OnFinishConversion);
}

/**
 * @brief  BaseInit 基础的初始化
 */
void BesTableView::BaseInit()
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    this->setColumnWidth(0,50);
    this->setColumnWidth(1,120);
    this->setColumnWidth(5,120);
    this->verticalHeader()->setVisible(false);
//    this->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(255, 255, 255, 50);}");
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeMode::Fixed);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeMode::Fixed);
    this->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeMode::Fixed);
    this->horizontalHeader()->setMinimumSectionSize(50);
    this->horizontalHeader()->setStyleSheet("QHeaderView::section {color: rgb(255, 255, 255); background:  transparent; background-color: rgba(139, 139, 139, 70);}");
    this->horizontalHeader()->setHighlightSections(false);
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {background-color: rgba(255, 255, 255, 70);}");
    this->setGridStyle(Qt::PenStyle::NoPen);
    this->setShowGrid(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/**
 * @brief  resizeEvent 自动调整大小
 *
 * @param  event
 */
void BesTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);

    double widthLeft = this->width() - 50- 100 - 120 - 15;
    if(widthLeft <= 0)
        return;

    this->setColumnWidth(2,widthLeft * 3/7);
    this->setColumnWidth(3,widthLeft * 2/7);
    this->setColumnWidth(4,widthLeft * 2/7);
}

QVector<SONGINFO> BesTableView::initSongInfo(const QVector<SONGINFO> &infos)
{
    QVector<SONGINFO> infos_dealed = infos;
    for(SONGINFO& info:infos_dealed)
        info.nPercentage = -1;

    return infos_dealed;
}

