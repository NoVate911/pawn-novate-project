public OnPlayerText(playerid, text[])
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для использования чата необходимо авторизоваться.");
        return Kick_Player(playerid, _, "Не авторизирован");
    }

    new message[128];
    if(strlen(text) > 60)
    {
        new first[24+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+1)+(-2+61)], second[4+(-2+124)];
        strmid(message, text, 64, 128, 128);
        strdel(text, 64, 128);
        format(first, sizeof(first), "%s %s(%d) сказал%s: %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName] == 0 ? ("а") : ("")), text);
        Chat_SendMessage(playerid, 10.0, C_F_WHITE, first);
        format(second, sizeof(second), "..%s", message);
        Chat_SendMessage(playerid, 10.0, C_F_WHITE, second);
        SetPlayerChatBubble(playerid, second, C_F_WHITE, 10.0, 3000);
    }
    else
    {
        format(message, sizeof(message), "%s %s(%d) сказал%s: %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName] == 0 ? ("а") : ("")), text);
        Chat_SendMessage(playerid, 10.0, C_F_WHITE, message);
        SetPlayerChatBubble(playerid, message, C_F_WHITE, 10.0, 3000);
    }

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1);
        PTimerInfo[playerid][AnimationChat] = SetTimerEx("Animation_Stop", 3200, false, "i", playerid);
    }

    if(PAFKInfo[playerid][IsTrue])
    {
        if(AFK_Exit(playerid))
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы написали сообщение в чат и автоматически вышли с AFK режима.");
    }

    return 0;
}