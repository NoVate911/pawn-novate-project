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

/*      [ намскъел хмтнплюжхч на хцпнйе ]      */
/*      [ WE RESET THE INFORMATION ABOUT THE PLAYER ]      */
stock Data_Clear_PlayerInfo(playerid)
{
    PInfo[playerid][IsConnection] = false;
    PInfo[playerid][IsLogged] = false;
    PInfo[playerid][IsSpawning] = false;
    PInfo[playerid][AuthorizationTime] = 0;
    PInfo[playerid][AuthorizationCountTry] = 0;

    PInfo[playerid][Nick] = EOS;
    PInfo[playerid][Password] = EOS;
    PInfo[playerid][Email] = EOS;
    PInfo[playerid][RegIP] = EOS;
    PInfo[playerid][LastIP] = EOS;
    PInfo[playerid][RegDate] = EOS;
    PInfo[playerid][LastDate] = EOS;
    return 1;
}

/*      [ намскъел хмтнплюжхч н рюилепюу хцпнйю ]      */
/*      [ WE RESET THE INFORMATION ABOUT THE TIMERS OF THE PLAYER ]      */
stock Data_Clear_PlayerTimerInfo(playerid)
{
    KillTimer(PTimerInfo[playerid][Second]);
    return 1;
}

stock Data_Get_PlayerInfo(playerid)
{
    cache_get_value_name(0, "email", PInfo[playerid][Email], MAX_EMAIL_LEN);
    cache_get_value_name(0, "regIP", PInfo[playerid][RegIP], 15);
    GetPlayerIp(playerid, PInfo[playerid][LastIP], 15);
    cache_get_value_name(0, "regDate", PInfo[playerid][RegDate], 12);
    new year, month, day;
    getdate(year, month, day);
    format(PInfo[playerid][LastDate], 14, "%02d.%02d.%02d", year, month, day);
    return 1;
}

/*      [ йхйюел хцпнйю я дхюкнцнл ]      */
/*      [ KICK THE PLAYER WITH THE DIALOG ]      */
stock Player_Kick(playerid, author[]="яЕПБЕП", reason[]="мЕХГБЕЯРМН")
{
    strmid(PKickInfo[playerid][Nick], author, 0, strlen(author), MAX_PLAYER_NAME);
    strmid(PKickInfo[playerid][Reason], reason, 0, strlen(reason), MAX_PLAYER_NAME*2);

    Dialog_Show(playerid, Dialog:Dlg_Kick);
    SCM(playerid, C_F_WHITE, ""NOTIF_WARNING" "C_WHITE"дКЪ НРЙКЧВЕМХЪ НР ЯЕПБЕПЮ, ХЯОНКЭГСИРЕ "C_EMERALD"/q"C_WHITE".");
    return PTimerInfo[playerid][Kicks] = SetTimerEx("Timer_OnPlayerKick", 500, false, "i", playerid);
}

function Timer_OnPlayerKick(playerid)
{
    Kick(playerid);
    return KillTimer(PTimerInfo[playerid][Kicks]);
}

/*      [ онъбкемхе хцпнйю оняке юсремрхтхйюжхх ]      */
/*      [ THE APPEARANCE OF THE PLAYER AFTER AUTHENTICATION ]      */
stock Player_SpawnAfterAuthorization(playerid)
{
    TogglePlayerSpectating(playerid, false);
    SetPlayerVirtualWorld(playerid, 0);
    SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 3.0, 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    PInfo[playerid][IsLogged] = true;
    PInfo[playerid][IsSpawning] = true;
    return 1;
}