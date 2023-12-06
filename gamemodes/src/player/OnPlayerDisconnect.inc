public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            MoneyGive(playerid, PWInfo[playerid][LoaderMovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
            MoneyGive(playerid, PWInfo[playerid][FarmerMovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
            MoneyGive(playerid, PWInfo[playerid][DiverTotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
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