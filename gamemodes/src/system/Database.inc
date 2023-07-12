/*      [ ПОДКЛЮЧЕНИЕ К БАЗЕ ДАННЫХ ]      */
/*      [ CONNECTING TO THE DATABASE ]      */
stock MySQL_ConnectionDatabase(hostname[], username[], password[], database[])
{
    SInfo[MySQL] = mysql_connect(hostname, username, password, database);
    mysql_log(ALL);
    mysql_set_charset("cp1251", SInfo[MySQL]);
    switch(mysql_errno(SInfo[MySQL]))
    {
        case 2005: return printf("%s Не удалось подключиться к базе данных. Неверное имя хоста. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        case 1045: return printf("%s Не удалось подключиться к базе данных. Неверное имя пользователя. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        case 1049: return printf("%s Не удалось подключиться к базе данных. Неверное имя базы данных. (Код ошибки: %d)", DEBUG_MYSQL, mysql_errno(SInfo[MySQL]));
        default: printf("%s База данных подключена и готова к работе.", DEBUG_MYSQL);
    }
    return 1;
}

/*      [ ЗАКРЫТИЕ ПОДКЛЮЧЕНИЯ К БАЗЕ ДАННЫХ ]      */
/*      [ CLOSING THE DATABASE CONNECTION ]     */
stock MySQL_CloseConnectionDatabase()
{
    mysql_close(SInfo[MySQL]);
    return 1;
}