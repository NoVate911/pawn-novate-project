stock TextDrawsCreateForServer()
{
    // Время / Time
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