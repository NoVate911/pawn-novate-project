/*      [ УСТАНОВКА ВРЕМЕНИ НА СЕРВЕРЕ ]      */
/*      [ SETTING THE TIME ON THE SERVER ]      */
stock Time_Set(bool:isOwn = false, hour = 0, minute = 0, second = 0)
{
    foreach(new i : Player)
    {
        if(PInfo[i][IsConnection])
        {
            // Будет ли установлено своё время?
            // Will your time be set?
            if(isOwn) // Да | Yes
                SetPlayerTime(i, hour, minute);
            else // Нет | No
            {
                gettime(hour, minute, second);
                SetPlayerTime(i, hour, minute);
            }
        }
    }
    return 1;
}

/*      [ УСТАНОВКА ВРЕМЕНИ ДЛЯ ИГРОКА ]      */
/*      [ SETTING THE TIME FOR THE PLAYER ]      */
stock Time_SetPlayer(playerid, bool:isOwn = false, hour = 0, minute = 0, second = 0)
{
    if(PInfo[playerid][IsConnection])
    {
        // Будет ли установлено своё время?
        // Will your time be set?
        if(isOwn) // Да | Yes
            SetPlayerTime(playerid, hour, minute);
        else // Нет | No
        {
            gettime(hour, minute, second);
            SetPlayerTime(playerid, hour, minute);
        }
    }
    return 1;
}