public OnGameModeInit()
{
    new tickCount = GetTickCount();

    MySQL_ConnectionDatabase(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
    STimerInfo[Minute] = SetTimer("Timer_OnServerMinute", 60000, true);
    Vehicle_Init();
    Time_Set();
    Weather_Set();
    SetGameModeText(SERVER_VERSION);
    DisableInteriorEnterExits();
    EnableStuntBonusForAll(false);
    LimitGlobalChatRadius(0.0);
    LimitPlayerMarkerRadius(0.0);
    
    return printf("%s Мод загружен за %dms.", DEBUG_LOAD, GetTickCount() - tickCount);
}