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
            if(PInfo[playerid][AuthorizationTime] <= 0)
                Kick_Player(playerid, "Сервер", "Время истекло");
            else
                PInfo[playerid][AuthorizationTime]--;
        }
        else
        {
            // Проверка на деньги | Checking for money
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime] <= 0)
                Money_Update(playerid);
            else
                CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime]--;

            AFK_Check(playerid);
            if(!PAFKInfo[playerid][IsTrue])
            {
                Level_Check(playerid);
            }
        }
    }
    return PTimerInfo[playerid][Second] = SetTimerEx("Timer_OnPlayerSecond", 1000, false, "i", playerid);
}