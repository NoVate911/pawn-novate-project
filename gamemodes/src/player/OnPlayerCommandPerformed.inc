public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(result == -1)
        return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Команда введена неверно или не найдена.", cmd);
    return 1;
}