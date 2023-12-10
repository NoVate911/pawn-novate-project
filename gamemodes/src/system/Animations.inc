/*      [ СПИСОК БИБЛИОТЕК С АНИМАЦИЯМИ ДЛЯ ПРЕДЗАГРУЗКИ ]      */
/*      [ LIST OF LIBRARIES WITH ANIMATIONS FOR PRELOADING ]      */
stock AnimationsPreload(playerid)
{   
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

/*      [ ОСТАНОВКА АНИМАЦИИ ЧЕРЕЗ ВРЕМЯ ]      */
/*      [ STOPPING THE ANIMATION AFTER A WHILE ]      */
function TimerOnAnimationStop(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAnimation] = false;
    ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
    KillTimer(PTimerInfo[playerid][Animation]);
    return 1;
}

/*      [ ОСТАНОВКА АНИМАЦИИ ]      */
/*      [ STOPPING THE ANIMATION ]      */
stock AnimationStop(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAnimation] = false;
    ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
    return 1;
}