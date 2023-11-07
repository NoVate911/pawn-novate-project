/*      [ СПИСОК БИБЛИОТЕК С АНИМАЦИЯМИ ДЛЯ ПРЕДЗАГРУЗКИ ]      */
/*      [ LIST OF LIBRARIES WITH ANIMATIONS FOR PRELOADING ]      */
stock Animations_Preload(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;
    
    Animation_Preload(playerid, "PED");
    Animation_Preload(playerid, "CARRY");
    return 1;
}

/*      [ ПРЕДЗАГРУЗКА БИБЛИОТЕКИ АНИМАЦИИ ]      */
/*      [ PRELOADING THE ANIMATION LIBRARY ]      */
stock Animation_Preload(playerid, animlib[])
{
    ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0, 0);
    return 1;
}

/*      [ ОСТАНОВКА АНИМАЦИИ ]      */
/*      [ STOPPING ANIMATION ]      */
function Timer_Animation_Stop(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
    return KillTimer(PTimerInfo[playerid][Animation]);
}

stock Animation_Stop(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    return ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
}