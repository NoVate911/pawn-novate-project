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
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelayOpeningDialog] > 0)
                CInfo[playerid][PInfo[playerid][CharacterSelect]][DelayOpeningDialog]--;

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
                    new id = VehicleGetArrayID(GetPlayerVehicleID(playerid));
                    new speed_string[9+(-2+3)], mileage_string[7+(-2+8)];
                    format(speed_string, sizeof(speed_string), "%.0f KM/H", VInfo[id][Speed]);
                    TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][4], speed_string);
                    format(mileage_string, sizeof(mileage_string), "%.0f KM", VInfo[id][Mileage]);
                    TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][5], mileage_string);
                    if(!VInfo[id][IsUsed])
                        VInfo[id][IsUsed] = true;
                }
            }
            else
            {
                if(IsValidPlayerTextDraw(playerid, PTDInfo[playerid][Speedometer][4]))
                    VehicleHideSpeedometerForPlayer(playerid);
            }
        }
    }
    PTimerInfo[playerid][Second] = SetTimerEx("TimerOnPlayerSecond", 1000, false, "i", playerid);
    return 1;
}