/*      [ КИКАЕМ ИГРОКА С ДИАЛОГОМ ]      */
/*      [ KICK THE PLAYER WITH THE DIALOG ]      */
stock Player_Kick(playerid, author[]="Сервер", reason[]="Неизвестно")
{
    strmid(PKickInfo[playerid][Nick], author, 0, strlen(author), MAX_PLAYER_NAME);
    strmid(PKickInfo[playerid][Reason], reason, 0, strlen(reason), MAX_PLAYER_NAME*2);

    Dialog_Show(playerid, Dialog:Dlg_Kick);
    SCM(playerid, C_F_WHITE, ""NOTIF_WARNING" "C_WHITE"Для отключения от сервера, используйте "C_EMERALD"/q"C_WHITE".");
    return PTimerInfo[playerid][Kicks] = SetTimerEx("Timer_OnPlayerKick", 500, false, "i", playerid);
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