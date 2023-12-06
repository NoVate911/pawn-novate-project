public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
        return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Подождите %d секунд перед отправкой команды.", CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand]);

    if(result == -1)
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
        // SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Команда введена неверно или не найдена.");
    ChatDelaySendCommand(playerid);
    return 0;
}