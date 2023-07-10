public OnPlayerConnect(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    GetPlayerName(playerid, PInfo[playerid][Nick], MAX_PLAYER_NAME);
    return PTimerInfo[playerid][Authorization] = SetTimerEx("Timer_OnPlayerConnect", 300, false, "i", playerid);
}

function Timer_OnPlayerConnect(playerid)
{
    KillTimer(PTimerInfo[playerid][Authorization]);
    Chat_Clear_Player(playerid);
    TogglePlayerSpectating(playerid, true);
    SetPlayerVirtualWorld(playerid, playerid + 1000);
    PInfo[playerid][IsConnection] = true;

    static const query[] = "SELECT nick FROM accounts WHERE nick = '%s' LIMIT 1";
    new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick]);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    if(cache_num_rows())
    {
        PInfo[playerid][AuthorizationTime] = MAX_AUTHORIZATION_TIME;
        PInfo[playerid][AuthorizationCountTry] = AUTHORIZATION_COUNT_TRY;
        Dialog_Show(playerid, Dialog:Dlg_Auth_Log_Password);
    }
    else
    {
        PInfo[playerid][AuthorizationTime] = MAX_REGISTRATION_TIME;
        Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Password);
    }
    cache_delete(cache);
    return PTimerInfo[playerid][Second] = SetTimerEx("Timer_OnPlayerSecond", 1000, true, "i", playerid);
}