public OnPlayerExitVehicle(playerid, vehicleid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
    new id = VehicleGetArrayID(vehicleid);
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new Float:x, Float:y, Float:z;
        GetVehiclePos(vehicleid, x, y, z);
        VInfo[id][CurrentPosition][0] = x;
        VInfo[id][CurrentPosition][1] = y;
        VInfo[id][CurrentPosition][2] = z;
        GetVehicleZAngle(vehicleid, VInfo[id][CurrentRotation]);
        VInfo[id][IsUsed] = false;
    }
    return 1;
}