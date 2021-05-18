#include "SettingManager.h"

#include <qsettings.h>

SettingManager &SettingManager::GetInstance()
{
    static SettingManager* instance = nullptr;
    if(instance == nullptr)
        instance = new SettingManager();
    return *instance;
}

QString& SettingManager::getDownlaodPath()
{
    return settingData->songDownloadPath;
}

void SettingManager::loadSettingData()
{
    QSettings mysettings("./MusicPlayer.ini",QSettings::IniFormat);
    settingData->songDownloadPath = mysettings.value("songDownload/location").toString();
}


//bool SettingManager::saveSettingData()
//{
//    QSettings mysettings("./MusicPlayer.ini",QSettings::IniFormat);
//    return true;
//}
