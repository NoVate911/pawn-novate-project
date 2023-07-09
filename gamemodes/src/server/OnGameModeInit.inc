public OnGameModeInit()
{
    new tickCount = GetTickCount();

    // Подключение к базе данных
    // Connecting to the database
    SInfo[MySQL] = mysql_connect(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
    mysql_log(ALL);
    mysql_set_charset("cp1251", SInfo[MySQL]);
    switch(mysql_errno(SInfo[MySQL]))
    {
        case 2005: return printf("%s Не удалось подключиться к базе данных. Неверное имя хоста. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        case 1045: return printf("%s Не удалось подключиться к базе данных. Неверное имя пользователя. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        case 1049: return printf("%s Не удалось подключиться к базе данных. Неверное имя базы данных. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        default: printf("%s База данных подключена и готова к работе.", DEBUG_MYSQL);
    }

    SetGameModeText(SERVER_VERSION);
    
    return printf("%s Мод загружен за %dms.", DEBUG_LOAD, GetTickCount() - tickCount);
}