/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ ИГРОКА ]      */
/*      [ SECOND TIMER FOR THE PLAYER ]      */
function TimerOnPlayerSecond(playerid)
{
    // Проверка на подключение | Checking for connection
    if(PInfo[playerid][IsConnection])
    {
        // Проверка на вход | Check for entry
        if(!PInfo[playerid][IsLogged])
        {
            // Время на авторизацию/регистрацию | Time for authorization/registration
            if(PInfo[playerid][AuthorizationTime] <= 0)
                KickPlayer(playerid, "Сервер", "Время истекло");
            else
                PInfo[playerid][AuthorizationTime]--;
        }
        else
        {
            // Задержка на отправку сообщений и команд в чат | Delay in sending messages and commands to the chat
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendMessage] > 0)
                CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendMessage]--;
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
                CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]--;

            // Проверка на деньги | Checking for money
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime] <= 0)
                MoneyUpdate(playerid);
            else
                CInfo[playerid][PInfo[playerid][CharacterSelect]][MoneyTime]--;

            // Проверка на AFK | Проверка на AFK
            AFKCheck(playerid);
            if(!PAFKInfo[playerid][IsTrue])
            {
                LevelCheck(playerid);
            }
        }
    }
    return PTimerInfo[playerid][Second] = SetTimerEx("TimerOnPlayerSecond", 1000, false, "i", playerid);
}