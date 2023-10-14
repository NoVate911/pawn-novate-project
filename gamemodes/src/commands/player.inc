cmd:menu(playerid)
{
    return Dialog_Show(playerid, Dialog:Dlg_Player_Menu);
}
alias:menu("mn")

cmd:n(playerid, params[])
{
    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 65)
    {
        new first[18+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+66)], second[7+(-2+123)];
        strmid(message, params, 66, 128, 128);
        strdel(params, 66, 128);
        format(first, sizeof(first), "(( %s %s(%d): %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params);
        Chat_SendMessage(playerid, 10.0, C_F_LIGHTGRAY, first);
        format(second, sizeof(second), "..%s ))", message);
        Chat_SendMessage(playerid, 10.0, C_F_LIGHTGRAY, second);
        SetPlayerChatBubble(playerid, second, C_F_LIGHTGRAY, 10.0, 3000);
    }
    else
    {
        format(message, sizeof(message), "(( %s %s(%d): %s ))", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params);
        Chat_SendMessage(playerid, 10.0, C_F_LIGHTGRAY, message);
        SetPlayerChatBubble(playerid, message, C_F_LIGHTGRAY, 10.0, 3000);
    }
    return 1;
}