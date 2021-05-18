#pragma once
#ifndef SETTING_MANAGER_H
#define SETTING_MANAGER_H

#include <QString>

class SettingData
{
public:
    QString songDownloadPath;

    SettingData() : songDownloadPath("") {  }
    SettingData(QString path) : songDownloadPath(path) {  }
};

class SettingManager
{
    /* 单例访问 */
public:
    static SettingManager& GetInstance();
    ~SettingManager() {  }

    void loadSettingData();
//    bool saveSettingData();

    QString& getDownlaodPath();

//    SettingData& data();

private:
    SettingManager() : settingData(new SettingData()) {  }

private:
    SettingData *settingData;
};

#endif // SETTING_MANAGER_H
