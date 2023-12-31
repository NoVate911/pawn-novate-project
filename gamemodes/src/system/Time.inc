/*      [ УСТАНОВКА ВРЕМЕНИ НА СЕРВЕРЕ ]      */
/*      [ SETTING THE TIME ON THE SERVER ]      */
stock TimeSet(bool:isOwn = false, hour = 0, minute = 0)
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
    new string[9+(-2+2)+(-2+2)];
    if(isOwn)
        format(string, sizeof(string), "%02d:%02d", hour, minute);
    else
        format(string, sizeof(string), "%02d:%02d", TInfo[Hour], TInfo[Minute]);
    TextDrawSetString(TDInfo[Time], string);
    return 1;
}

/*      [ УСТАНОВКА ВРЕМЕНИ ДЛЯ ИГРОКА ]      */
/*      [ SETTING THE TIME FOR THE PLAYER ]      */
stock TimeSetPlayer(playerid, bool:isOwn = false, hour = 0, minute = 0)
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
    new string[9+(-2+2)+(-2+2)];
    if(isOwn)
        format(string, sizeof(string), "%02d:%02d", hour, minute);
    else
        format(string, sizeof(string), "%02d:%02d", TInfo[Hour], TInfo[Minute]);
    TextDrawSetString(TDInfo[Time], string);
    return 1;
}