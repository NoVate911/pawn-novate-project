dCreate:Dlg_Kick(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\c�� ���� ������� � �������.\n\n\
    "C_WHITE"\\c��� ������: "C_EMERALD"%s\n\
    "C_WHITE"\\c������� ����: "C_EMERALD"%s\n\n";
    new string[sizeof(message)+(-2+MAX_PLAYER_NAME)+(-4+MAX_PLAYER_NAME*2)];
    format(string, sizeof(string), message, PKickInfo[playerid][Nick], PKickInfo[playerid][Reason]);
    return Dialog_Open(playerid, Dialog:Dlg_Kick, DIALOG_STYLE_MSGBOX, ""C_WHITE"�� ���� �������", string, "X", "");
}