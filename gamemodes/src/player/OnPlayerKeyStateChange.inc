public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) // Анти-баннихоп | Anti-bannyhop
            {
                if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
                {
                    if(newkeys & KEY_SPRINT && newkeys & KEY_JUMP)
                    {
                        AnimationStop(playerid);
                        ApplyAnimation(playerid, "PED", "IDLE_TIRED", 4.0, 0, 1, 0, 0, 3000, 1);
                    }
                }
            }

            VehicleKeyStateChange(playerid, newkeys);
            WorkLoaderLVKeyStateChange(playerid, newkeys);
            WorkFarmerLVKeyStateChange(playerid, newkeys);
            WorkDiverLVKeyStateChange(playerid, newkeys);
        }
    }
    return 1;
}