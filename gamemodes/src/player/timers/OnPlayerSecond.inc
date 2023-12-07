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

            // Проверка на нахождение в транспорте | Checking for being in transport
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle])
            {
                if(GetPlayerVehicleSeat(playerid) == 0)
                {
                    new vehicleid = GetPlayerVehicleID(playerid);
                    new string[9+(-2+3)];
                    for(new vehicle = 0; vehicle < MAX_VEHICLES; vehicle++)
                    {
                        if(VInfo[vehicle][ID] == vehicleid)
                        {
                            format(string, sizeof(string), "%.0f KM/H", VInfo[vehicle][Speed]);
                            TextDrawsUpdateForServer(playerid, VInfo[vehicle][Speedometer][4], string);
                            break;
                        }
                    }
                }
            }
        }
    }
    return PTimerInfo[playerid][Second] = SetTimerEx("TimerOnPlayerSecond", 1000, false, "i", playerid);
}