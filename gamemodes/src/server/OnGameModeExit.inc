public OnGameModeExit()
{
    return mysql_close(SInfo[MySQL]);
}