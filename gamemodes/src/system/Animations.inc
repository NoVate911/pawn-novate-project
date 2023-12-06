/*      [ СПИСОК БИБЛИОТЕК С АНИМАЦИЯМИ ДЛЯ ПРЕДЗАГРУЗКИ ]      */
/*      [ LIST OF LIBRARIES WITH ANIMATIONS FOR PRELOADING ]      */
stock AnimationsPreload(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;
    
    AnimationPreload(playerid, "PED");
    AnimationPreload(playerid, "CARRY");
    AnimationPreload(playerid, "ON_LOOKERS");
    return 1;
}

/*      [ ПРЕДЗАГРУЗКА БИБЛИОТЕКИ АНИМАЦИИ ]      */
/*      [ PRELOADING THE ANIMATION LIBRARY ]      */
stock AnimationPreload(playerid, animlib[])
{
    ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0, 0);
    return 1;
}

/*      [ ОСТАНОВКА АНИМАЦИИ ]      */
/*      [ STOPPING ANIMATION ]      */
function TimerOnAnimationStop(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
    return KillTimer(PTimerInfo[playerid][Animation]);
}

stock AnimationStop(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    return ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
}