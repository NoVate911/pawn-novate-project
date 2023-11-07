public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        {
            Work_Loader_LV_EnterDynamicCP(playerid, checkpointid);
            Work_Farmer_LV_EnterDynamicCP(playerid, checkpointid);
        }
    }
    return 1;
}