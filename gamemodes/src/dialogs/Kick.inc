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