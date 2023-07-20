/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ ИГРОКА ]      */
/*      [ SECOND TIMER FOR THE PLAYER ]      */
function Timer_OnPlayerSecond(playerid)
{
    if(!PInfo[playerid][IsConnection])
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        PInfo[playerid][AuthorizationTime]--;
        
        if(PInfo[playerid][AuthorizationTime] <= 0)
            Player_Kick(playerid, "Сервер", "Время истекло");
        return 1;
    }
    return 0;
}