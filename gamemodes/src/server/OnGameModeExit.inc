public OnGameModeExit()
{
    foreach(new pl : Player)
    {
        if(PInfo[pl][IsConnection])
            Player_Kick(pl, _, "Выключение");
    }
    KillTimer(STimerInfo[Second]);
    return MySQL_CloseConnectionDatabase();
}