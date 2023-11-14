cmd:menu(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        return 1;
        
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
    return Dialog_Show(playerid, Dialog:DlgPlayerMenu);
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
        ChatSendMessage(playerid, 10.0, C_F_LIGHTGRAY, first);
        format(second, sizeof(second), "..%s ))", message);
        ChatSendMessage(playerid, 10.0, C_F_LIGHTGRAY, second);
        SetPlayerChatBubble(playerid, second, C_F_LIGHTGRAY, 10.0, 3000);
    }
    else
    {
        format(message, sizeof(message), "(( %s %s(%d): %s ))", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params);
        ChatSendMessage(playerid, 10.0, C_F_LIGHTGRAY, message);
        SetPlayerChatBubble(playerid, message, C_F_LIGHTGRAY, 10.0, 3000);
    }
    return 1;
}

cmd:me(playerid, params[])
{
    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 75)
    {
        new first[10+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+76)], second[4+(-2+126)];
        strmid(message, params, 76, 128, 128);
        strdel(params, 76, 128);
        format(first, sizeof(first), "%s %s %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], params);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, first);
        format(second, sizeof(second), "..%s", message);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, second);
    }
    else
    {
        format(message, sizeof(message), "%s %s %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], params);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, message);
    }
    return 1;
}

cmd:ame(playerid, params[])
{
    new message[32];
    if(sscanf(params, "s[32]", message))
        return 1;
        
    SetPlayerChatBubble(playerid, params, C_F_PURPLE, 10.0, 3000);
    return 1;
}

cmd:do(playerid, params[])
{
    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 73)
    {
        new first[12+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+74)], second[4+(-2+126)];
        strmid(message, params, 74, 128, 128);
        strdel(params, 74, 128);
        format(first, sizeof(first), "%s.. (%s %s)", params, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, first);
        format(second, sizeof(second), "..%s", message);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, second);
    }
    else
    {
        format(message, sizeof(message), "%s (%s %s)", params, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
        ChatSendMessage(playerid, 10.0, C_F_PURPLE, message);
    }
    return 1;
}

cmd:td(playerid, params[])
{
    new string[4+(-2+4)];
    format(string, sizeof(string), "+%d$", (random(1000 - 1) + 1));
    TextDrawNotificationShow(playerid, string);
}