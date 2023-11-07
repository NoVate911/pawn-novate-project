public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            switch(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType])
            {
                case WORK_LOADER_ID: Money_Give(playerid, PlayerWLInfo[playerid][MovedBoxCount] * WORK_LOADER_PRICE_PER_BOX);
            }
        }

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
    Data_Clear_PlayerWorkLoaderInfo(playerid);
    return 1;
}