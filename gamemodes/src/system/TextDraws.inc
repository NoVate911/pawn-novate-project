stock TextDrawsCreateForServer()
{
    // Время | Time
    TDInfo[Time] = TextDrawCreate(577.333435, 24.474081, "00:00");
    TextDrawLetterSize(TDInfo[Time], 0.449999, 1.600000);
    TextDrawAlignment(TDInfo[Time], 2);
    TextDrawColor(TDInfo[Time], -1);
    TextDrawSetShadow(TDInfo[Time], 0);
    TextDrawSetOutline(TDInfo[Time], 1);
    TextDrawBackgroundColor(TDInfo[Time], 51);
    TextDrawFont(TDInfo[Time], 3);
    TextDrawSetProportional(TDInfo[Time], 1);
    return 1;
}

stock TextDrawsCreateForPlayer(playerid)
{
    // Уведомления | Notifications
    PTDInfo[playerid][Notification] = CreatePlayerTextDraw(playerid, 83.333328, 309.452148, "+666$");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Notification], 0.449999, 1.600000);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Notification], 2);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Notification], -1);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Notification], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Notification], 1);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Notification], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Notification], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Notification], 1);
    return 1;
}

stock TextDrawsUpdateForServer(playerid, Text:textdraw, string[] = "Null", color = C_F_WHITE)
{
    TextDrawHideForPlayer(playerid, textdraw);
    if(strcmp(string, "Null") != 0)
        TextDrawSetString(textdraw, string);
    TextDrawColor(textdraw, color);
    TextDrawShowForPlayer(playerid, textdraw);
    return 1;
}

stock TextDrawsUpdateForPlayer(playerid, PlayerText:textdraw, string[] = "Null", color = C_F_WHITE)
{
    PlayerTextDrawHide(playerid, textdraw);
    if(strcmp(string, "Null") != 0)
        PlayerTextDrawSetString(playerid, textdraw, string);
    PlayerTextDrawColor(playerid, textdraw, color);
    PlayerTextDrawShow(playerid, textdraw);
    return 1;
}