public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerVehicleSeat(playerid) == 0)
                SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
        }
        else
            SetPlayerPosFindZ(playerid, fX, fY, fZ);
            
        SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были телепортированы на метку.");
        printf("%s %s %s(%d) [%s:%s] телепортировался по метке на карте [%f, %f, %f].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], fX, fY, fZ);
    }
    return 1;
}