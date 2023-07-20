/*      [ УСТАНОВКА ПОГОДЫ НА СЕРВЕРЕ ]      */
/*      [ SETTING THE WEATHER ON THE SERVER ]      */
stock Weather_Set(bool:isOwn = false, weather = 0)
{
    foreach(new i : Player)
    {
        if(PInfo[i][IsConnection])
        {
            // Будет ли установлена своя погода?
            // Will the weather be set its own?
            if(isOwn) // Да | Yes
                SetPlayerWeather(i, weather);
            else // Нет | No
            {
                weather = random(22);
                SetPlayerWeather(i, weather);
            }
            SInfo[Weather] = weather;
        }
    }
    return 1;
}

/*      [ УСТАНОВКА ПОГОДЫ ДЛЯ ИГРОКА ]      */
/*      [ SETTING THE WEATHER FOR THE PLAYER ]      */
stock Weather_SetPlayer(playerid, bool:isOwn = false, weather = 0)
{
    if(PInfo[playerid][IsConnection])
    {
        // Будет ли установлена своя погода?
        // Will the weather be set its own?
        if(isOwn) // Да | Yes
            SetPlayerWeather(playerid, weather);
        else // Нет | No
            SetPlayerWeather(playerid, SInfo[Weather]);
    }
    return 1;
}