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
                case WORK_LOADER_LV_ID: MoneyGive(playerid, PlayerWLLVInfo[playerid][MovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
                case WORK_FARMER_LV_ID: MoneyGive(playerid, PlayerWFLVInfo[playerid][MovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
                case WORK_DIVER_LV_ID: MoneyGive(playerid, PlayerWDLVInfo[playerid][TotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
            }
        }

        DataSetPlayerInfo(playerid);
        DataSetCharacterInfo(playerid);
        printf("%s %s %s(%d) [%s:%s] отключился от сервера.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], PInfo[playerid][LastIP]);
    }

    DataClearCharacterInfo(playerid);
    DataClearPlayerInfo(playerid);
    DataClearPlayerTimerInfo(playerid);
    DataClearPlayerKickInfo(playerid);
    DataClearPlayerAFKInfo(playerid);
    DataClearAdminSpectateInfo(playerid);
    DataClearPlayerWorksInfo(playerid);
    DataClearPlayerTextDrawInfo(playerid);
    return 1;
}