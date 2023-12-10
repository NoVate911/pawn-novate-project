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

        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerVehicleSeat(playerid) == 0)
            {
                new id = VehicleGetArrayID(GetPlayerVehicleID(playerid));
                VInfo[id][IsUsed] = false;
            }
        }

        DataSetPlayerInfo(playerid);
        DataSetCharacterInfo(playerid);
        DataSetCharacterLicenseInfo(playerid);
        DataClearPlayerAFKInfo(playerid);
        DataClearAdminSpectateInfo(playerid);
        DataClearPlayerWorksInfo(playerid);
        DataClearCharacterLicenseInfo(playerid);
        DataClearPlayerDialogInfo(playerid);
        printf("%s %s %s(%d) [%s:%s] отключился от сервера.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], PInfo[playerid][LastIP]);
    }

    DataClearCharacterInfo(playerid);
    DataClearPlayerTimerInfo(playerid);
    DataClearPlayerKickInfo(playerid);
    DataClearPlayerTextDrawInfo(playerid);
    DataClearPlayerInfo(playerid);
    return 1;
}