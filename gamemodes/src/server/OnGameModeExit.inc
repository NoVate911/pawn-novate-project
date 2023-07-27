public OnGameModeExit()
{
    foreach(new pl : Player)
    {
        if(PInfo[pl][IsConnection])
            Kick_Player(pl, _, "Выключение");
    }
    KillTimer(STimerInfo[Second]);
    return MySQL_CloseConnectionDatabase();
}