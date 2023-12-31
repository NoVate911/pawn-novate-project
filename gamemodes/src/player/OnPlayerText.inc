public OnPlayerText(playerid, text[])
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для использования чата необходимо авторизоваться.");
        KickPlayer(playerid, _, "Не авторизирован");
        return 0;
    }

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendMessage] > 0)
    {
        SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой сообщения.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendMessage]);
        return 0;
    }

    new message[128];
    if(strlen(text) > 60)
    {
        new first[24+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+1)+(-2+61)], second[4+(-2+126)];
        strmid(message, text, 61, 128, 128);
        strdel(text, 61, 128);
        format(first, sizeof(first), "%s %s(%d) сказал%s: %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? ("") : ("а")), text);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, first);
        format(second, sizeof(second), "..%s", message);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, second);
        SetPlayerChatBubble(playerid, second, C_F_WHITE, MAX_DISTANCE_CHAT/2, 3000);
    }
    else
    {
        format(message, sizeof(message), "%s %s(%d) сказал%s: %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? ("") : ("а")), text);
        ChatSendMessage(playerid, MAX_DISTANCE_CHAT, C_F_WHITE, message);
        SetPlayerChatBubble(playerid, message, C_F_WHITE, MAX_DISTANCE_CHAT/2, 3000);
    }

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsFrozen])
        {
            CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAnimation] = true; 
            ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1);
            PTimerInfo[playerid][Animation] = SetTimerEx("TimerOnAnimationStop", 3200, false, "i", playerid);
        }
    }

    if(PAFKInfo[playerid][IsTrue])
    {
        if(AFKExit(playerid))
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы написали сообщение в чат и автоматически вышли с AFK режима.");
    }
    ChatDelaySendMessage(playerid);
    return 0;
}