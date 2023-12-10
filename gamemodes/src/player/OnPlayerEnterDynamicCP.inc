public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        {
            WorkLoaderLVEnterDynamicCP(playerid, checkpointid);
            WorkFarmerLVEnterDynamicCP(playerid, checkpointid);
            WorkDiverLVEnterDynamicCP(playerid, checkpointid);
            DrivingSchoolEnterDynamicCP(playerid, checkpointid);
        }
    }
    return 1;
}