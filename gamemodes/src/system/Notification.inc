/*      [ ОТОБРАЖЕНИЕ УВЕДОМЛЕНИЙ ]      */
/*      [ DISPLAYING NOTIFICATIONS ]      */
stock NotificationShow(playerid, message[], color = -1, bool:sound = true)
{
    PlayerTextDrawSetString(playerid, PTDInfo[playerid][Notification], message);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Notification], color);
    PlayerTextDrawShow(playerid, PTDInfo[playerid][Notification]);
    if(PTimerInfo[playerid][Notification])
        KillTimer(PTimerInfo[playerid][Notification]);
    if(sound)
        PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
    PTimerInfo[playerid][Notification] = SetTimerEx("TimerOnNotificationShow", 2000, false, "i", playerid);
    return 1;
}

function TimerOnNotificationShow(playerid)
{
    PlayerTextDrawHide(playerid, PTDInfo[playerid][Notification]);
    return KillTimer(PTimerInfo[playerid][Notification]);
}