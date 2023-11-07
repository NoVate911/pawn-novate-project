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
                if(newkeys & KEY_SPRINT && newkeys & KEY_JUMP)
                {
                    Animation_Stop(playerid);
                    ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.0, 0, 1, 0, 0, 0, 1);
                }
            }

            Vehicle_KeyStateChange(playerid, newkeys);
            Work_Loader_KeyStateChange(playerid, newkeys);
        }
    }
    return 1;
}