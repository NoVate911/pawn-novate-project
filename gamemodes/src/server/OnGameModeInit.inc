public OnGameModeInit()
{
    new tickCount = GetTickCount();

    MySQL_ConnectionDatabase(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
    Vehicle_Init();
    SetGameModeText(SERVER_VERSION);
    
    return printf("%s Мод загружен за %dms.", DEBUG_LOAD, GetTickCount() - tickCount);
}