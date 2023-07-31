public OnGameModeInit()
{
    new tickCount = GetTickCount();

    MySQL_ConnectionDatabase(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
    STimerInfo[Second] = SetTimer("Timer_OnServerSecond", 1000, false);
    Vehicle_Init();
    Ban_Account_Init();
    Ban_Character_Init();
    Time_Set();
    Weather_Set();
    SetGameModeText(SERVER_VERSION);
    DisableInteriorEnterExits();
    EnableStuntBonusForAll(false);
    LimitGlobalChatRadius(0.0);
    LimitPlayerMarkerRadius(0.0);
    ManualVehicleEngineAndLights();
    
    return printf("%s Мод загружен за %dms.", DEBUG_LOAD, GetTickCount() - tickCount);
}