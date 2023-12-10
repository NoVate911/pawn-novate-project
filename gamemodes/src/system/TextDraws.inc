/*      [ СОЗДАНИЕ TEXTDRAW'a ДЛЯ СЕРВЕРА ]      */
/*      [ CREATING A TEXTDRAW FOR THE SERVER ]      */
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

/*      [ СОЗДАНИЕ TEXTDRAW'a ДЛЯ ИГРОКА ]      */
/*      [ CREATING A TEXTDRAW FOR THE PLAYER ]      */
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

    // Спидометер | Speedometer
    PTDInfo[playerid][Speedometer][0] = CreatePlayerTextDraw(playerid, 406.000000, 424.611083, "usebox");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][0], 0.000000, -10.456583);
    PlayerTextDrawTextSize(playerid, PTDInfo[playerid][Speedometer][0], 613.666625, 0.000000);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][0], 1);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][0], 0);
    PlayerTextDrawUseBox(playerid, PTDInfo[playerid][Speedometer][0], true);
    PlayerTextDrawBoxColor(playerid, PTDInfo[playerid][Speedometer][0], 136);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][0], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][0], -22);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][0], -1);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][0], 0);
    PTDInfo[playerid][Speedometer][1] = CreatePlayerTextDraw(playerid, 445.333801, 338.903625, "DOOR");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][1], 0.400999, 1.400889);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][1], 2);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][1], C_F_GREEN);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][1], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][1], 1);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][1], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][1], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Speedometer][1], 1);
    PTDInfo[playerid][Speedometer][2] = CreatePlayerTextDraw(playerid, 507.333465, 339.318389, "ENGINE");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][2], 0.400000, 1.400889);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][2], 2);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][2], C_F_RED);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][2], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][2], 1);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][2], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][2], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Speedometer][2], 1);
    PTDInfo[playerid][Speedometer][3] = CreatePlayerTextDraw(playerid, 572.333251, 339.318420, "LIGHT");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][3], 0.400999, 1.400889);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][3], 2);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][3], C_F_RED);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][3], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][3], 1);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][3], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][3], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Speedometer][3], 1);
    PTDInfo[playerid][Speedometer][4] = CreatePlayerTextDraw(playerid, 507.666595, 369.185180, "0 KM/H");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][4], 0.600332, 1.600000);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][4], 2);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][4], -1);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][4], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][4], 0);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][4], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][4], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Speedometer][4], 1);
    PTDInfo[playerid][Speedometer][5] = CreatePlayerTextDraw(playerid, 414.666259, 401.955780, "0 KM");
    PlayerTextDrawLetterSize(playerid, PTDInfo[playerid][Speedometer][5], 0.400999, 1.400887);
    PlayerTextDrawAlignment(playerid, PTDInfo[playerid][Speedometer][5], 1);
    PlayerTextDrawColor(playerid, PTDInfo[playerid][Speedometer][5], -86);
    PlayerTextDrawSetShadow(playerid, PTDInfo[playerid][Speedometer][5], 0);
    PlayerTextDrawSetOutline(playerid, PTDInfo[playerid][Speedometer][5], 1);
    PlayerTextDrawBackgroundColor(playerid, PTDInfo[playerid][Speedometer][5], 51);
    PlayerTextDrawFont(playerid, PTDInfo[playerid][Speedometer][5], 3);
    PlayerTextDrawSetProportional(playerid, PTDInfo[playerid][Speedometer][5], 1);
    return 1;
}

/*      [ ОБНОВЛЕНИЕ СЕРВЕРНОГО TEXTDRAW'a У ИГРОКА ]      */
/*      [ UPDATING THE PLAYER'S SERVER TEXTDRAW ]      */
stock TextDrawsUpdateForServer(playerid, Text:textdraw, string[] = "Null", color = C_F_WHITE)
{
    TextDrawHideForPlayer(playerid, textdraw);
    if(strcmp(string, "Null") != 0)
        TextDrawSetString(textdraw, string);
    TextDrawColor(textdraw, color);
    TextDrawShowForPlayer(playerid, textdraw);
    return 1;
}

/*      [ ОБНОВЛЕНИЕ TEXTDRAW'a У ИГРОКА ]      */
/*      [ UPDATING THE PLAYER'S TEXTDRAW ]      */
stock TextDrawsUpdateForPlayer(playerid, PlayerText:textdraw, string[] = "Null", color = C_F_WHITE)
{
    PlayerTextDrawHide(playerid, textdraw);
    if(strcmp(string, "Null") != 0)
        PlayerTextDrawSetString(playerid, textdraw, string);
    PlayerTextDrawColor(playerid, textdraw, color);
    PlayerTextDrawShow(playerid, textdraw);
    return 1;
}