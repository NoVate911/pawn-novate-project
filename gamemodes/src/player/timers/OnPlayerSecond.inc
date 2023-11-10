/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ ИГРОКА ]      */
/*      [ SECOND TIMER FOR THE PLAYER ]      */
function TimerOnPlayerSecond(playerid)
{
    if(!PInfo[playerid][IsConnection]) // Проверка на подключение | Checking for connection
        return 1;
    else
    {
        if(!PInfo[playerid][IsLogged]) // Проверка на вход | Check for entry
        {
            if(PInfo[playerid][AuthorizationTime] <= 0)
                KickPlayer(playerid, "Сервер", "Время истекло");
            else
                PInfo[playerid][AuthorizationTime]--;
        }
        else
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime] <= 0) // Проверка на деньги | Checking for money
                MoneyUpdate(playerid);
            else
                CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime]--;

            AFKCheck(playerid);
            if(!PAFKInfo[playerid][IsTrue])
            {
                LevelCheck(playerid);
            }
        }
    }
    return PTimerInfo[playerid][Second] = SetTimerEx("TimerOnPlayerSecond", 1000, false, "i", playerid);
}