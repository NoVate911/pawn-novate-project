public OnPlayerExitVehicle(playerid, vehicleid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
    if(GetPlayerVehicleSeat(playerid) == 0)
    {
        if(VehicleFindID(vehicleid))
        {
            for(new v = 0; v < MAX_VEHICLES; v++)
            {
                if(VInfo[v][ID] == vehicleid)
                {
                    for(new speedometer = 0; speedometer < 6; speedometer++)
                        TextDrawHideForPlayer(playerid, VInfo[v][Speedometer][speedometer]);
                    break;
                }
            }
        }
    }
    return 1;
}