/*      [ ЗАМОРОЗКА/РАЗМОРОЗКА ИГРОКА ]      */
/*      [ FREEZING/DEFROSTING A PLAYER ]      */
stock FreezePlayer(playerid, bool:IsTemporary = true)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen] = !CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen];
    TogglePlayerControllable(playerid, !CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen]);
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen])
    {
        if(IsTemporary)
            PTimerInfo[playerid][Freeze] = SetTimerEx("TimerOnFreezePlayer", 5000, false, "i", playerid);
    }
    return 1;
}

/*      [ ТАЙМЕР ДЛЯ РАЗМОРОЗКИ ИГРОКА ]      */
/*      [ TIMER FOR DEFROSTING THE PLAYER ]      */
function TimerOnFreezePlayer(playerid)
{
    FreezePlayer(playerid, false);
    return KillTimer(PTimerInfo[playerid][Freeze]);
}