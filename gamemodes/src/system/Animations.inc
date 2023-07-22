/*      [ СПИСОК БИБЛИОТЕК С АНИМАЦИЯМИ ДЛЯ ПРЕДЗАГРУЗКИ ]      */
/*      [ LIST OF LIBRARIES WITH ANIMATIONS FOR PRELOADING ]      */
stock Animation_PreloadAnimations(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;
    
    Animation_PreloadAnimation(playerid, "PED");
    return 1;
}

/*      [ ПРЕДЗАГРУЗКА БИБЛИОТЕКИ АНИМАЦИИ ]      */
/*      [ PRELOADING THE ANIMATION LIBRARY ]      */
stock Animation_PreloadAnimation(playerid, animlib[])
{
    ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0, 0);
    SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Библиотека анимаций \"%s\" была загружена.", animlib);
    return 1;
}

/*      [ ОСТАНОВКА АНИМАЦИИ ]      */
/*      [ STOPPING ANIMATION ]      */
function Animation_Stop(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    ApplyAnimation(playerid, "PED", "FACANGER", 4.1, 0, 0, 0, 0, 0, 1);
    return KillTimer(PTimerInfo[playerid][AnimationChat]);
}