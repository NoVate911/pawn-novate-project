public OnPlayerText(playerid, text[])
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для использования чата необходимо авторизоваться.");
        return Player_Kick(playerid, _, "Не авторизирован");
    }

    return 0;
}