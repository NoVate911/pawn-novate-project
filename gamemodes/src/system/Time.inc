#define MAX_TIME_UPDATE_TIME        (60) // Время обновления времени суток | Time of day update time

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ УСТАНОВКА ВРЕМЕНИ НА СЕРВЕРЕ ]      */
/*      [ SETTING THE TIME ON THE SERVER ]      */
stock Time_Set(bool:isOwn = false, hour = 0, minute = 0)
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
                SetPlayerTime(i, TInfo[Hour], TInfo[Minute]);
        }
    }
    return 1;
}

/*      [ УСТАНОВКА ВРЕМЕНИ ДЛЯ ИГРОКА ]      */
/*      [ SETTING THE TIME FOR THE PLAYER ]      */
stock Time_SetPlayer(playerid, bool:isOwn = false, hour = 0, minute = 0)
{
    if(PInfo[playerid][IsConnection])
    {
        // Будет ли установлено своё время?
        // Will your time be set?
        if(isOwn) // Да | Yes
            SetPlayerTime(playerid, hour, minute);
        else // Нет | No
            SetPlayerTime(playerid, TInfo[Hour], TInfo[Minute]);
    }
    return 1;
}