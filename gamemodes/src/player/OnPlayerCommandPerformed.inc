public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(result == -1)
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
        // SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Команда введена неверно или не найдена.");
    return 1;
}