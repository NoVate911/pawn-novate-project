cmd:menu(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive])
        return 1;
        
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
    return Dialog_Show(playerid, Dialog:DlgPlayerMenu);
}
alias:menu("mn")

cmd:n(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 65)
    {
        new first[18+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+66)], second[7+(-2+123)];
        strmid(message, params, 66, 128, 128);
        strdel(params, 66, 128);
        format(first, sizeof(first), "(( %s %s(%d): %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_LIGHTGRAY, first);
        format(second, sizeof(second), "..%s ))", message);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_LIGHTGRAY, second);
        SetPlayerChatBubble(playerid, second, C_F_LIGHTGRAY, MAX_DISTANCE_CHAT/2, 3000);
    }
    else
    {
        format(message, sizeof(message), "(( %s %s(%d): %s ))", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_LIGHTGRAY, message);
        SetPlayerChatBubble(playerid, message, C_F_LIGHTGRAY, MAX_DISTANCE_CHAT/2, 3000);
    }
    return 1;
}

cmd:me(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 75)
    {
        new first[10+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+76)], second[4+(-2+126)];
        strmid(message, params, 76, 128, 128);
        strdel(params, 76, 128);
        format(first, sizeof(first), "%s %s %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, first);
        format(second, sizeof(second), "..%s", message);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, second);
    }
    else
    {
        format(message, sizeof(message), "%s %s %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, message);
    }
    return 1;
}

cmd:ame(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    new message[32];
    if(sscanf(params, "s[32]", message))
        return 1;
        
    SetPlayerChatBubble(playerid, params, C_F_PURPLE, MAX_DISTANCE_CHAT/2, 3000);
    return 1;
}

cmd:do(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 73)
    {
        new first[4+(-2+126)], second[12+(-2+74)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)];
        strmid(message, params, 74, 128, 128);
        strdel(params, 74, 128);
        format(first, sizeof(first), "%s..", params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, first);
        format(second, sizeof(second), "..%s (%s %s)", message, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, second);
    }
    else
    {
        format(message, sizeof(message), "%s (%s %s)", params, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_PURPLE, message);
    }
    return 1;
}

cmd:s(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    new message[128];
    if(sscanf(params, "s[128]", message))
        return 1;
        
    if(strlen(params) > 59)
    {
        new first[25+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+1)+(-2+60)], second[4+(-2+126)];
        strmid(message, params, 60, 128, 128);
        strdel(params, 60, 128);
        format(first, sizeof(first), "%s %s(%d) крикнул%s: %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? ("а") : ("")), params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, first);
        format(second, sizeof(second), "..%s", message);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, second);
        SetPlayerChatBubble(playerid, second, C_F_LIGHTGRAY, MAX_DISTANCE_CHAT/2, 3000);
    }
    else
    {
        format(message, sizeof(message), "%s %s(%d) крикнул%s: %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? ("а") : ("")), params);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, message);
        SetPlayerChatBubble(playerid, message, C_F_LIGHTGRAY, MAX_DISTANCE_CHAT/2, 3000);
    }
    
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen])
        {
            CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAnimation] = true;
            ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.1, 0, 0, 0, 0, 0, 1);
        }
    }
    return 1;
}

cmd:animationstop(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAnimation])
                AnimationStop(playerid);
        }
    }
    return 1;
}