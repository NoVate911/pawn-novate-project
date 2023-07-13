public OnPlayerConnect(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    GetPlayerName(playerid, PInfo[playerid][Nick], MAX_PLAYER_NAME);
    return PTimerInfo[playerid][Authorization] = SetTimerEx("Timer_OnPlayerConnect", 200, false, "i", playerid);
    // src/system/Authorization.inc
}