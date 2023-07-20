public OnPlayerConnect(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsConnection])
        Player_Kick(playerid, _, "Игрок на сервере");

    GetPlayerName(playerid, PInfo[playerid][Nick], MAX_PLAYER_NAME);
    return PTimerInfo[playerid][Authorization] = SetTimerEx("Timer_OnPlayerConnect", 200, false, "i", playerid);
    // src/system/Authorization.inc
}