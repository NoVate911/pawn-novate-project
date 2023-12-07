public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        VehicleStateChange(playerid, newstate, oldstate);
    }
    return 1;
}