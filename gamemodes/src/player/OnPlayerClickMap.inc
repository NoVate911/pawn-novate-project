public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerVehicleSeat(playerid) != 0)
                return 1;
                
            SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
        }
        else
            SetPlayerPosFindZ(playerid, fX, fY, fZ);
    }
    return 1;
}