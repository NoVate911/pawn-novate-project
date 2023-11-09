public OnGameModeExit()
{
    foreach(new pl : Player)
    {
        if(PInfo[pl][IsConnection])
            KickPlayer(pl, _, "Выключение");
    }
    KillTimer(STimerInfo[Second]);
    return MySQLCloseConnectionDatabase();
}