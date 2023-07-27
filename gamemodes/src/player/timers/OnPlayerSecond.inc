/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ ИГРОКА ]      */
/*      [ SECOND TIMER FOR THE PLAYER ]      */
function Timer_OnPlayerSecond(playerid)
{
    // Проверка на подключение | Checking for connection
    if(!PInfo[playerid][IsConnection])
        return 1;
    else
    {
        // Проверка на вход | Check for entry
        if(!PInfo[playerid][IsLogged])
        {
            PInfo[playerid][AuthorizationTime]--;
            
            if(PInfo[playerid][AuthorizationTime] <= 0)
                Player_Kick(playerid, "Сервер", "Время истекло");
        }
        else
        {
            AFK_Check(playerid);
            if(!PAFKInfo[playerid][IsTrue])
            {
                Level_Check(playerid);
            }
        }
    }
    return PTimerInfo[playerid][Second] = SetTimerEx("Timer_OnPlayerSecond", 1000, false, "i", playerid);
}