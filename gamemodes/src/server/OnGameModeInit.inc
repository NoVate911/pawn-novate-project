public OnGameModeInit()
{
    new tickCount = GetTickCount();
    MySQLConnectionDatabase(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
    STimerInfo[Second] = SetTimer("TimerOnServerSecond", 1000, false);
    VehicleInit();
    WorksInit();
    TextDrawsCreateForServer();
    TimeSet();
    WeatherSet();
    SetGameModeText(SERVER_VERSION);
    DisableInteriorEnterExits();
    EnableStuntBonusForAll(false);
    LimitGlobalChatRadius(0.0);
    LimitPlayerMarkerRadius(0.0);
    ManualVehicleEngineAndLights();
    SetNameTagDrawDistance(25.0);
    printf("%s Мод загружен за %dms.", DEBUG_LOAD, GetTickCount() - tickCount);
    return 1;
}