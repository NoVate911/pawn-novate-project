public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(!PDialogInfo[playerid][IsActive])
        {
            WorkLoaderLVEnterDynamicCP(playerid, checkpointid);
            WorkFarmerLVEnterDynamicCP(playerid, checkpointid);
            WorkDiverLVEnterDynamicCP(playerid, checkpointid);
            DrivingSchoolEnterDynamicCP(playerid, checkpointid);
        }
    }
    return 1;
}