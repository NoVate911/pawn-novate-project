public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        SetPlayerPosFindZ(playerid, fX, fY, fZ);
        SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были телепортированы на метку.");
        printf("%s %s %s(%d) [%s] [%s] телепортировался по метке на карте.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
    }
    return 1;
}