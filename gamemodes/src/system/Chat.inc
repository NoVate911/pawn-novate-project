/*      [ нвхярйю цкнаюкэмнцн вюрю ]      */
/*      [ CLEARING THE GLOBAL CHAT ]      */
stock Chat_Clear_All()
{
    return 1;
}

/*      [ нвхярйю оепянмюкэмнцн вюрю ]      */
/*      [ CLEARING A PERSONAL CHAT ]      */
stock Chat_Clear_Player(playerid, count = 50)
{
    for(new i = 0; i < count; i++)
    {
        SCM(playerid, C_F_WHITE, " ");
    }
    return 1;
}