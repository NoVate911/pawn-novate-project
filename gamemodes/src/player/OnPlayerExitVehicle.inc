public OnPlayerExitVehicle(playerid, vehicleid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
    VehicleHideSpeedometerForPlayer(playerid, vehicleid);
    return 1;
}