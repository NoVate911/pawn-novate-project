/*      [ НАПРАВЛЕНИЕ КАМЕРЫ ПРИ АВТОРИЗАЦИИ/РЕГИСТРАЦИИ/ВЫБОРЕ ПЕРСОНАЖА ]      */
/*      [ CAMERA DIRECTION DURING AUTHORIZATION/REGISTRATION/CHARACTER SELECTION ]      */
new const Float:Positions_Camera_Connect[3][3] = {
    {1372.3881, -2197.2434, 88.6293},
    {1561.8575, -2255.2761, 43.5144},
    {1478.7219, -2283.5388, 22.3047}
};

/*      [ ========== ========== ========== ========== ========== ]      */

public OnPlayerConnect(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    GetPlayerName(playerid, PInfo[playerid][Nick], MAX_PLAYER_NAME);
    foreach(new p : Player)
    {
        if(strcmp(PInfo[playerid][Nick], PInfo[p][Nick]) == 0)
        {
            if(PInfo[p][IsConnection])
                return KickPlayer(playerid, _, "Игрок на сервере");
        }
    }
    PTimerInfo[playerid][Authorization] = SetTimerEx("TimerOnPlayerConnect", 1000, false, "i", playerid);
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ТАЙМЕР НА ПОДКЛЮЧЕНИЕ ]      */
/*      [ CONNECTION TIMER ]      */
function TimerOnPlayerConnect(playerid)
{
    KillTimer(PTimerInfo[playerid][Authorization]);
    PInfo[playerid][IsConnection] = true;
    TimeSetPlayer(playerid);
    WeatherSetPlayer(playerid);
    ChatClear(playerid);
    TogglePlayerSpectating(playerid, true);
    SetPlayerVirtualWorld(playerid, playerid+1000);
    AnimationsPreload(playerid);
    InterpolateCameraPos(playerid, Positions_Camera_Connect[0][0], Positions_Camera_Connect[0][1], Positions_Camera_Connect[0][2], Positions_Camera_Connect[1][0], Positions_Camera_Connect[1][1], Positions_Camera_Connect[1][2], 120000);
    InterpolateCameraLookAt(playerid, Positions_Camera_Connect[2][0], Positions_Camera_Connect[2][1], Positions_Camera_Connect[2][2], Positions_Camera_Connect[2][0], Positions_Camera_Connect[2][1], Positions_Camera_Connect[2][2], 120000);
    static const query[] = "SELECT nick FROM accounts WHERE nick = '%s' LIMIT 1";
    new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick]);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    if(cache_num_rows())
    {
        PInfo[playerid][AuthorizationTime] = MAX_AUTHORIZATION_TIME;
        PInfo[playerid][AuthorizationCountTry] = AUTHORIZATION_COUNT_TRY;
        Dialog_Show(playerid, Dialog:DlgAuthLogPassword);
    }
    else
    {
        PInfo[playerid][AuthorizationTime] = MAX_REGISTRATION_TIME;
        Dialog_Show(playerid, Dialog:DlgAuthRegPassword);
    }
    cache_delete(cache);
    PTimerInfo[playerid][Second] = SetTimerEx("TimerOnPlayerSecond", 1000, false, "i", playerid);
    return 1;
}