public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        {
            Vehicle_KeyStateChange(playerid, newkeys);
            Work_Loader_KeyStateChange(playerid, newkeys);
        }
    }
    return 1;
}