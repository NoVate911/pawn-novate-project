public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        Data_Set_PlayerInfo(playerid);
        Data_Set_CharacterInfo(playerid);
        printf("%s %s %s(%d) [%s:%s] отключился от сервера.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], PInfo[playerid][LastIP]);
    }

    Data_Clear_CharacterInfo(playerid);
    Data_Clear_PlayerInfo(playerid);
    Data_Clear_PlayerTimerInfo(playerid);
    Data_Clear_PlayerKickInfo(playerid);
    Data_Clear_PlayerAFKInfo(playerid);
    Data_Clear_AdminSpectateInfo(playerid);
    return 1;
}