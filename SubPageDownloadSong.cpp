#include "SettingManager.h"
#include "SubPageDownloadSong.h"

#include <QFont>
#include <QSettings>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QStandardPaths>

SubPageDownloadSong::SubPageDownloadSong(QWidget *parent)
    : QWidget(parent), nCurrentDownloadCount(0)
{
    initLayout();
    initConnection();
}

void SubPageDownloadSong::initLayout()
{
    QVBoxLayout* vMainLayour= new QVBoxLayout(this);

    //标题
    QFont font;
    font.setPointSize(10);
    font.setFamily(("Microsoft YaHei"));
    font.setBold(true);
    labelTitleSearchSong = new QLabel(this);
    labelTitleSearchSong->setObjectName("labelTitleSearchSong");
    labelTitleSearchSong->setText(tr("歌曲搜索"));
    labelTitleSearchSong->setStyleSheet("color: rgb(255, 255, 255); ");
    labelTitleSearchSong->setFont(font);

    //搜索按钮
    labelSearchNcmSong = new QLabel(this);
    labelSearchNcmArtist = new QLabel(this);
    labelSearchNcmSong->setMinimumSize(120, 30);
    labelSearchNcmArtist->setMinimumSize(120, 30);
    labelSearchNcmSong->setMaximumSize(150, 30);
    labelSearchNcmArtist->setMaximumSize(150, 30);
    labelSearchNcmSong->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labelSearchNcmArtist->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labelSearchNcmSong->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelSearchNcmArtist->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelSearchNcmSong->setText(tr("歌曲名："));
    labelSearchNcmSong->setStyleSheet("color: rgb(255, 255, 255); ");
    labelSearchNcmArtist->setText(tr("歌手："));
    labelSearchNcmArtist->setStyleSheet("color: rgb(255, 255, 255); ");

    editSearchNcmSong = new QLineEdit(this);
    editSearchNcmArtist = new QLineEdit(this);
    editSearchNcmSong->setPlaceholderText(tr("必填"));
    editSearchNcmArtist->setPlaceholderText(tr("选填"));
    editSearchNcmArtist->setStyleSheet("color: rgb(255, 255, 255);  background-color: rgba(255, 255, 255, 50);");
    editSearchNcmSong->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 50);");
    editSearchNcmSong->setMinimumSize(250, 30);
    editSearchNcmArtist->setMinimumSize(250, 30);
    editSearchNcmSong->setMaximumSize(250, 30);
    editSearchNcmArtist->setMaximumSize(250, 30);
    editSearchNcmSong->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    editSearchNcmArtist->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    btnSearchNcmSong = new BesButton(this);
    btnSearchNcmSong->setObjectName("btnSearchNcmSong");
    btnSearchNcmSong->setText(tr("搜索"));
    btnSearchNcmSong->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(66, 66, 66);");
    btnSearchNcmSong->setMinimumSize(150,30);
    btnSearchNcmSong->setMaximumSize(150,30);
    btnSearchNcmSong->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout1->addWidget(labelSearchNcmSong);
    hLayout1->addWidget(editSearchNcmSong);
    hLayout1->addWidget(btnSearchNcmSong);
    hLayout1->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    hLayout2->addWidget(labelSearchNcmArtist);
    hLayout2->addWidget(editSearchNcmArtist);
    hLayout2->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    //搜索结果提示
    labelNcmSongResultTip1 = new QLabel(this);
    labelNcmSongResultTip2 = new QLabel(this);
    labelNcmSongResultTip3 = new QLabel(this);
    labelNcmSongResultTip4 = new QLabel(this);
    labelNcmSongResultTip5 = new QLabel(this);
    labelNcmSongResultTip1->setMinimumHeight(30);
    labelNcmSongResultTip2->setMinimumHeight(30);
    labelNcmSongResultTip3->setMinimumHeight(30);
    labelNcmSongResultTip4->setMinimumHeight(30);
    labelNcmSongResultTip5->setMinimumHeight(30);
    labelNcmSongResultTip1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed );
    labelNcmSongResultTip2->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed );
    labelNcmSongResultTip3->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed );
    labelNcmSongResultTip4->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed );
    labelNcmSongResultTip5->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed );
    labelNcmSongResultTip2->setObjectName("labelNcmSongResultTip2");
    labelNcmSongResultTip4->setObjectName("labelNcmSongResultTip4");
    labelNcmSongResultTip1->setText(tr("搜索歌曲名"));
    labelNcmSongResultTip2->setText(tr("\"\""));
    labelNcmSongResultTip3->setText(tr("、歌手"));
    labelNcmSongResultTip4->setText(tr("\"\""));
    labelNcmSongResultTip5->setText(tr("找到15条歌曲记录。"));
    showTipLabel(false);
    QHBoxLayout* hLayout3 = new QHBoxLayout();
    hLayout3->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    hLayout3->addWidget(labelNcmSongResultTip1);
    hLayout3->addWidget(labelNcmSongResultTip2);
    hLayout3->addWidget(labelNcmSongResultTip3);
    hLayout3->addWidget(labelNcmSongResultTip4);
    hLayout3->addWidget(labelNcmSongResultTip5);
    hLayout3->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    //LRC歌词面板
    widgetLrcLyricBoard = new QWidget(this);

    labelLrcLyricPanelSong = new QLabel(widgetLrcLyricBoard);
    labelLrcLyricPanelArtist = new QLabel(widgetLrcLyricBoard);
    editLrcLyricPanelSong= new QLineEdit(widgetLrcLyricBoard);
    editLrcLyricPanelArtist= new QLineEdit(widgetLrcLyricBoard);
    btnLrcLyricPanelSave = new BesButton(widgetLrcLyricBoard);
    editTextLrcLyric = new QTextEdit(widgetLrcLyricBoard);

    font.setPointSize(12);
    editTextLrcLyric->setReadOnly(true);
    editTextLrcLyric->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 50);");
    editTextLrcLyric->setFont(font);

    labelLrcLyricPanelSong->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labelLrcLyricPanelArtist->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labelLrcLyricPanelSong->setText(tr("音乐："));
    labelLrcLyricPanelSong->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 0);");
    labelLrcLyricPanelArtist->setText(tr("歌手："));
    labelLrcLyricPanelArtist->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 0);");
    labelLrcLyricPanelSong->setMinimumSize(100, 30);
    labelLrcLyricPanelArtist->setMinimumSize(100, 30);
    labelLrcLyricPanelArtist->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelLrcLyricPanelSong->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed);

    editLrcLyricPanelSong->setMinimumHeight(30);
    editLrcLyricPanelSong->setStyleSheet("color: rgb(255, 255, 255);  background-color: rgba(255, 255, 255, 50);");
    editLrcLyricPanelArtist->setMinimumHeight(30);
    editLrcLyricPanelArtist->setStyleSheet("color: rgb(255, 255, 255);  background-color: rgba(255, 255, 255, 50);");

    btnLrcLyricPanelSave->setMinimumHeight(30);
    btnLrcLyricPanelSave->setText("保存LRC歌词");
    btnLrcLyricPanelSave->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(66, 66, 66);");
    btnLrcLyricPanelSave->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout* hLayout5 = new QHBoxLayout();
    hLayout5->addWidget(labelLrcLyricPanelSong);
    hLayout5->addWidget(editLrcLyricPanelSong);
    hLayout5->addWidget(labelLrcLyricPanelArtist);
    hLayout5->addWidget(editLrcLyricPanelArtist);
    hLayout5->addWidget(btnLrcLyricPanelSave);

    QVBoxLayout* vLayoutLrcPanel = new QVBoxLayout(widgetLrcLyricBoard);
    vLayoutLrcPanel->addLayout(hLayout5);
    vLayoutLrcPanel->addWidget(editTextLrcLyric);

    //搜索结果
    tableNcmSongSearch = new BesTableView(this);
    tableNcmSongSearch->setObjectName("tableNcmSongSearch");
    widgetLrcLyricBoard->setObjectName("tableNcmLyricSearch");

    // 路径
    labelRawLyricPanelSavePath = new QLabel(this);
    editRawLyricPanelSavePath= new BesFileLineEdit(BesFileTypeFloder, this);
    btnLrcLyricPanelSelectPath = new BesButton(this);

    labelRawLyricPanelSavePath->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labelRawLyricPanelSavePath->setText(tr("保存路径："));
    labelRawLyricPanelSavePath->setStyleSheet("color: rgb(255, 255, 255);");
    labelRawLyricPanelSavePath->setMinimumSize(100, 30);
    labelRawLyricPanelSavePath->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed);

//    editRawLyricPanelSavePath->setReadOnly(true);
    editRawLyricPanelSavePath->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 50);");
    editRawLyricPanelSavePath->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    editRawLyricPanelSavePath->setMinimumHeight(30);
    editRawLyricPanelSavePath->setText(SettingManager::GetInstance().getDownlaodPath());

    btnLrcLyricPanelSelectPath->setText("选择路径");
    btnLrcLyricPanelSelectPath->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(66, 66, 66);");
    btnLrcLyricPanelSelectPath->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout* hLayout4 = new QHBoxLayout();
    hLayout4->addWidget(labelRawLyricPanelSavePath);
    hLayout4->addWidget(editRawLyricPanelSavePath);
    hLayout4->addWidget(btnLrcLyricPanelSelectPath);

    //tab 搜索歌曲结果页面
    tabpageNcmSongResult = new QTabWidget(this);
    tabpageNcmSongResult->setObjectName("tabpageNcmSongResult");
    tabpageNcmSongResult->setFocusPolicy(Qt::NoFocus);
    tabpageNcmSongResult->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
    tableNcmSongSearch->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 50)");
//    widgetLrcLyricBoard->setStyleSheet("color: rgb(255, 255, 255); background-color: rgba(139, 139, 139, 40)");
    tabpageNcmSongResult->addTab(tableNcmSongSearch, "歌曲结果");
    tabpageNcmSongResult->addTab(widgetLrcLyricBoard, "歌词结果");
    tabpageNcmSongResult->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    vMainLayour->addWidget(labelTitleSearchSong);
    vMainLayour->addSpacerItem(new QSpacerItem(20,20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    vMainLayour->addLayout(hLayout4);
    vMainLayour->addSpacerItem(new QSpacerItem(20,10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    vMainLayour->addLayout(hLayout1);
    vMainLayour->addLayout(hLayout2);
    vMainLayour->addSpacerItem(new QSpacerItem(20,20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    vMainLayour->addLayout(hLayout3);
    vMainLayour->addSpacerItem(new QSpacerItem(20,10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    vMainLayour->addWidget(tabpageNcmSongResult);
}

void SubPageDownloadSong::initConnection()
{
     connect(btnSearchNcmSong, &BesButton::clicked, this, &SubPageDownloadSong::OnSearchSong);
     connect(&searchThread, &ThreadSearchNcmMusic::songResultChanged, this, &SubPageDownloadSong::OnSongResultChanged);
     connect(tableNcmSongSearch, &BesTableView::sig_oneDownloadStarted, this, &SubPageDownloadSong::onStartOneDownload);
     connect(tableNcmSongSearch, &BesTableView::sig_oneDownloadFinished, this, &SubPageDownloadSong::onFinishOneDownload);
     connect(tableNcmSongSearch, &BesTableView::sig_showLrcLyric, this, &SubPageDownloadSong::OnShowLrcLyric); // 先保存所有结构列表，再从列表中存取
     connect(btnLrcLyricPanelSave, &BesButton::clicked, this, &SubPageDownloadSong::OnSaveLrcLyric);
     connect(btnLrcLyricPanelSelectPath, &BesButton::clicked, this, &SubPageDownloadSong::OnSelectLrcLyricPath);
     connect(editRawLyricPanelSavePath, &BesFileLineEdit::editingFinished, this, &SubPageDownloadSong::OnLrcLyricPathChanged);
}

void SubPageDownloadSong::searchNcmDirectly(const QString &artists, const QString &song)
{
    editSearchNcmSong->setText(song);
    editSearchNcmArtist->setText(artists);

    if(btnSearchNcmSong->isEnabled() == false)
    {
        //正在下载中，提示稍后再搜索
        QMessageBox::about(nullptr, "提示", "有歌曲正在下载中，请稍后搜索");
        return;
    }

    OnSearchSong();
}

void SubPageDownloadSong::OnSelectLrcLyricPath()
{
    QString downloadLocation = QFileDialog::getExistingDirectory(this, "", QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first());
    if (downloadLocation.size() != 0) {
        QSettings mysettings("./MusicPlayer.ini",QSettings::IniFormat);

        editRawLyricPanelSavePath->setText(downloadLocation);
        mysettings.setIniCodec("UTF8");
        mysettings.setValue("songDownload/location", downloadLocation);
        SettingManager::GetInstance().loadSettingData();
    }
}

// FIXME：路径问题
void SubPageDownloadSong::OnLrcLyricPathChanged()
{
    QString downloadLocation_rollback = SettingManager::GetInstance().getDownlaodPath();
    QString downloadLocation = editRawLyricPanelSavePath->text();
    if (downloadLocation.size() != 0) {
        QDir DataDir(downloadLocation);

        if(!DataDir.exists())
            if(QMessageBox::StandardButton::Yes == QMessageBox::question(Q_NULLPTR, tr("路径提示"), tr("该目录不存在，是否建立该目录:") + downloadLocation)) {
                if(!DataDir.mkpath(downloadLocation))
                    QMessageBox::about(Q_NULLPTR, "提示", tr("无法为配置创建目录")+":" + downloadLocation);

                if(!DataDir.exists()) {
                    QMessageBox::information(Q_NULLPTR, "提示", "创建目录失败！");
                    downloadLocation = downloadLocation_rollback;
                    editRawLyricPanelSavePath->setText(downloadLocation);
                } else {
                    QMessageBox::information(Q_NULLPTR, "提示", "创建目录成功！");
                }
            }

        QSettings mysettings("./MusicPlayer.ini",QSettings::IniFormat);
        mysettings.setIniCodec("UTF8");
        mysettings.setValue("songDownload/location", downloadLocation);
        SettingManager::GetInstance().loadSettingData();
    }
}

void SubPageDownloadSong::OnSearchSong()
{
    tabpageNcmSongResult->setCurrentIndex(0);
    QString song = editSearchNcmSong->text().trimmed();
    QString artist = editSearchNcmArtist->text().trimmed();
    if(song.isEmpty()) {
        QMessageBox::about(Q_NULLPTR, "提示", "歌曲名不能为空");
        return;
    }

    showTipLabel(true);
    labelNcmSongResultTip2->setText("“" + song + "”");
    labelNcmSongResultTip4->setText("“" + artist + "”");
    labelNcmSongResultTip5->setText(tr("正在搜索中..."));
    btnSearchNcmSong->setEnabled(false);

    searchThread.StartSearchNcm(artist, song);
}

void SubPageDownloadSong::OnSongResultChanged(SongSearchResult result)
{
    //显示搜索结果
    int nCount = result.vecSongInfo.size();
    QString strResultTip = result.strUnexpectedResultTip;
    labelNcmSongResultTip5->setText(QString().sprintf("，找到%d条歌曲记录。", nCount) + strResultTip);
    labelNcmSongResultTip5->setVisible(true);

    if(result.vecSongInfo.size()!=0)
        tableNcmSongSearch->setItems(result.vecSongInfo);
    if(result.bCurrentSearchDone) //搜索结束时才能恢复按钮
        //恢复按钮，可以下一次继续搜索
        btnSearchNcmSong->setEnabled(true);
}

void SubPageDownloadSong::onStartOneDownload()
{
    nCurrentDownloadCount++;
    btnSearchNcmSong->setEnabled(false);
}

void SubPageDownloadSong::onFinishOneDownload()
{
    nCurrentDownloadCount--;
    if(nCurrentDownloadCount == 0)
        btnSearchNcmSong->setEnabled(true);
}


void SubPageDownloadSong::showTipLabel(bool bShow)
{
    labelNcmSongResultTip1->setVisible(bShow);
    labelNcmSongResultTip2->setVisible(bShow);
    labelNcmSongResultTip3->setVisible(bShow);
    labelNcmSongResultTip4->setVisible(bShow);
    labelNcmSongResultTip5->setVisible(bShow);
}

void SubPageDownloadSong::OnSaveLrcLyric()
{
    //构建本地文件路径
    auto lyricPanelSavePath = editRawLyricPanelSavePath->text();

    if(editTextLrcLyric->toPlainText().trimmed() == "当前歌曲无歌词") {
        QMessageBox::information(Q_NULLPTR, tr("提示"),tr("歌词内容为空"));
        return;
    }

    QString fileName;
    QString content = lastLyricPlainText;

    if(content.size() == 0) {
        QMessageBox::information(Q_NULLPTR, tr("提示"),tr("error: Lrc歌词内容为空"));
        return;
    }

    //构建 fileName
    QString song = editLrcLyricPanelSong->text();
    QString artist = editLrcLyricPanelArtist->text();

    if(song.size() == 0 && artist.size() == 0) //尝试构建失败
    {
        QMessageBox::information(Q_NULLPTR, tr("提示"),tr("歌名和歌手为空，无法保存"));
        return;
    }

    if(song.size() == 0)
        song = "XXX";

    if(artist.size() == 0)
        artist = "XXX";

    QString localFileName = song + " - " + artist;
    localFileName = localFileName.replace(QRegExp("[\\/\\\\\\|\\*\\?<>\\:\"]"), "_"); //将文件不允许出现的字符替换为下划线
    fileName = lyricPanelSavePath + "/" + localFileName + ".lrc";

    //提示是否保存到路径
    if(QMessageBox::StandardButton::Yes == QMessageBox::question(Q_NULLPTR, tr("保存确认"), tr("是否保存到路径：") + fileName)) {
        QFile fileOut(fileName);
        if (! fileOut.open(QFile::WriteOnly | QFile::Truncate)) {
            QMessageBox::information(Q_NULLPTR, tr("失败提示"), tr("无法保存文件:")+ fileName +"\n\n可能是程序没有写权限");
            return;
        }

        QTextStream streamFileOut(&fileOut);
        streamFileOut.setCodec("UTF-8");
        streamFileOut.setGenerateByteOrderMark(false);
        streamFileOut << content;
        streamFileOut.flush();

        fileOut.close();

        QMessageBox::information(Q_NULLPTR, tr("提示"), tr("歌词已成功保存到路径：") + fileName);
    }
}

void SubPageDownloadSong::OnShowLrcLyric(const LyricInfo &info)
{
    tabpageNcmSongResult->setCurrentIndex(1);
    editLrcLyricPanelSong->setText(info.strSong);
    editLrcLyricPanelArtist->setText(info.strArtist);
    if (info.strPlaneText.isEmpty())
        editTextLrcLyric->setPlainText("当前歌曲无歌词");
    else
        editTextLrcLyric->setPlainText(info.strPlaneText);
    lastLyricPlainText = info.strLabelText;
}
