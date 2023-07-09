public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerNPC(playerid))
        return 1;

    Data_Clear_PlayerInfo(playerid);
    Data_Clear_PlayerTimerInfo(playerid);
    return 1;
}