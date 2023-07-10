public OnPlayerText(playerid, text[])
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"Для использования чата необходимо быть авторизированным.");
        return Player_Kick(playerid, _, "Не авторизирован");
    }

    return 0;
}