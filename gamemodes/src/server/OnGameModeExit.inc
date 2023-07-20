public OnGameModeExit()
{
    foreach(new pl : Player)
    {
        if(PInfo[pl][IsConnection])
            Player_Kick(pl, _, "Выключение");
    }
    KillTimer(STimerInfo[Minute]);
    return MySQL_CloseConnectionDatabase();
}