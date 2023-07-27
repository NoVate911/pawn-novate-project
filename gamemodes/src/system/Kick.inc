/*      [ ПОЗИЦИЯ КАМЕРЫ ПРИ КИКЕ ]      */
/*      [ CAMERA POSITION AT KICK ]      */
new const Float:Positions_Camera_Kick[3][3] = {
    {1372.3881, -2197.2434, 88.6293},
    {1561.8575, -2255.2761, 43.5144},
    {1478.7219, -2283.5388, 22.3047}
};

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ КИКАЕМ ИГРОКА С ДИАЛОГОМ И КАМЕРОЙ ]      */
/*      [ KICK THE PLAYER WITH DIALOGUE AND CAMERA ]      */
stock Player_Kick(playerid, author[]="Сервер", reason[]="Неизвестно")
{
    strmid(PKickInfo[playerid][Nick], author, 0, strlen(author), MAX_PLAYER_NAME);
    strmid(PKickInfo[playerid][Reason], reason, 0, strlen(reason), MAX_PLAYER_NAME*2);

    Dialog_Show(playerid, Dialog:Dlg_Kick);
    Chat_Clear(playerid);
    SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Для отключения от сервера, используйте "C_EMERALD"/q"C_WHITE".");
    TogglePlayerSpectating(playerid, true);
    InterpolateCameraPos(playerid, Positions_Camera_Kick[0][0], Positions_Camera_Kick[0][1], Positions_Camera_Kick[0][2], Positions_Camera_Kick[1][0], Positions_Camera_Kick[1][1], Positions_Camera_Kick[1][2], 120000);
    InterpolateCameraLookAt(playerid, Positions_Camera_Kick[2][0], Positions_Camera_Kick[2][1], Positions_Camera_Kick[2][2], Positions_Camera_Kick[2][0], Positions_Camera_Kick[2][1], Positions_Camera_Kick[2][2], 120000);
    return PTimerInfo[playerid][Kicks] = SetTimerEx("Timer_OnPlayerKick", 200, false, "i", playerid);
}

function Timer_OnPlayerKick(playerid)
{
    Kick(playerid);
    return KillTimer(PTimerInfo[playerid][Kicks]);
}

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ДИАЛОГОВЫЕ ОКНА ]      */
/*      [ DIALOG BOXES ]      */
dCreate:Dlg_Kick(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВы были кикнуты с сервера.\n\n\
    "C_WHITE"\\cКто кикнул: "C_EMERALD"%s\n\
    "C_WHITE"\\cПричина кика: "C_EMERALD"%s\n\n";
    new string[sizeof(message)+(-2+MAX_PLAYER_NAME)+(-4+MAX_PLAYER_NAME*2)];
    format(string, sizeof(string), message, PKickInfo[playerid][Nick], PKickInfo[playerid][Reason]);
    return Dialog_Open(playerid, Dialog:Dlg_Kick, DIALOG_STYLE_MSGBOX, ""C_WHITE"Вы были кикнуты", string, "X", "");
}