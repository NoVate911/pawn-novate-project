/*      [ ОБНУЛЯЕМ ИНФОРМАЦИЮ ОБ ИГРОКЕ ]      */
/*      [ WE RESET THE INFORMATION ABOUT THE PLAYER ]      */
stock Data_Clear_PlayerInfo(playerid)
{
    PInfo[playerid][IsConnection] = false;
    PInfo[playerid][IsLogged] = false;
    PInfo[playerid][AuthorizationTime] = 0;
    PInfo[playerid][AuthorizationCountTry] = 0;

    PInfo[playerid][ID] = 0;
    PInfo[playerid][Nick] = EOS;
    PInfo[playerid][Password] = EOS;
    PInfo[playerid][Email] = EOS;
    PInfo[playerid][RegIP] = EOS;
    PInfo[playerid][LastIP] = EOS;
    PInfo[playerid][RegDate] = EOS;
    PInfo[playerid][LastDate] = EOS;

    PInfo[playerid][CharactersCount] = 0;
    PInfo[playerid][CharacterSelect] = 0;
    return 1;
}

/*      [ ОБНУЛЯЕМ ИНФОРМАЦИЮ О ТАЙМЕРАХ ИГРОКА ]      */
/*      [ WE RESET THE INFORMATION ABOUT THE TIMERS OF THE PLAYER ]      */
stock Data_Clear_PlayerTimerInfo(playerid)
{
    KillTimer(PTimerInfo[playerid][Second]);
    return 1;
}

/*      [ ОБНУЛЯЕМ ИНФОРМАЦИЮ О КИКЕ ИГРОКА ]      */
/*      [ WE RESET THE INFORMATION ABOUT THE PLAYER'S KICK ]      */
stock Data_Clear_PlayerKickInfo(playerid)
{
    PKickInfo[playerid][Nick] = EOS;
    PKickInfo[playerid][Reason] = EOS;
    return 1;
}

/*      [ ОБНУЛЯЕМ ИНФОРМАЦИЮ О КИКЕ ИГРОКА ]      */
stock Data_Clear_CharacterInfo(playerid)
{
    for(new i = 0; i < PInfo[playerid][CharactersCount]; i++)
    {
        CInfo[playerid][i][IsSpawning] = false;

        CInfo[playerid][i][ID] = 0;
        CInfo[playerid][i][Login] = EOS;
        CInfo[playerid][i][FirstName] = EOS;
        CInfo[playerid][i][LastName] = EOS;
        CInfo[playerid][i][Skin] = 0;
        CInfo[playerid][i][Age] = 0;
        CInfo[playerid][i][Sex] = 0;
        CInfo[playerid][i][Race] = 0;
        CInfo[playerid][i][Level] = 0;
        CInfo[playerid][i][Exp] = 0;
        CInfo[playerid][i][RegIP] = EOS;
        CInfo[playerid][i][LastIP] = EOS;
        CInfo[playerid][i][RegDate] = EOS;
        CInfo[playerid][i][LastDate] = EOS;
        for(new pos = 0; pos < 3; pos++)
            CInfo[playerid][i][Position][pos] = 0.0;
        CInfo[playerid][i][Rotation] = 0.0;
        CInfo[playerid][i][Interior] = 0;
        CInfo[playerid][i][VirtualWorld] = 0;
        CInfo[playerid][i][Health] = 0.0;
        CInfo[playerid][i][Armour] = 0.0;
    }
    return 1;
}

/*      [ ПОЛУЧАЕМ ДАННЫЕ ИГРОКА ИЗ БАЗЫ ДАННЫХ ]      */
/*      [ GETTING PLAYER DATA FROM THE DATABASE ]      */
stock Data_Get_PlayerInfo(playerid)
{
    cache_get_value_name_int(0, "id", PInfo[playerid][ID]);
    cache_get_value_name(0, "email", PInfo[playerid][Email], MAX_EMAIL_LEN);
    cache_get_value_name(0, "regIP", PInfo[playerid][RegIP], 16);
    GetPlayerIp(playerid, PInfo[playerid][LastIP], 16);
    cache_get_value_name(0, "regDate", PInfo[playerid][RegDate], 22);
    new year, month, day, hour, minute, second, date[15], time[15];
    getdate(year, month, day);
    gettime(hour, minute, second);
    format(date, 15, "%02d.%02d.%02d", year, month, day);
    format(time, 15, "%02d:%02d:%02d", hour, minute, second);
    format(PInfo[playerid][LastDate], 22, "%s / %s", date, time);
    return 1;
}

/*      [ ПОЛУЧАЕМ ДАННЫЕ ПЕРСОНАЖА ИЗ БАЗЫ ДАННЫХ ]      */
/*      [ GETTING CHARACTER DATA FROM THE DATABASE ]      */
stock Data_Get_CharacterInfo(playerid)
{
    for(new i = 0; i < PInfo[playerid][CharactersCount]; i++)
    {
        cache_get_value_name_int(i, "id", CInfo[playerid][i][ID]);
        cache_get_value_name(i, "login", CInfo[playerid][i][Login], MAX_PLAYER_NAME);
        cache_get_value_name(i, "firstname", CInfo[playerid][i][FirstName], MAX_PLAYER_NAME);
        cache_get_value_name(i, "lastname", CInfo[playerid][i][LastName], MAX_PLAYER_NAME);
        cache_get_value_name_int(i, "age", CInfo[playerid][i][Age]);
        cache_get_value_name_int(i, "sex", CInfo[playerid][i][Sex]);
        cache_get_value_name_int(i, "race", CInfo[playerid][i][Race]);
        cache_get_value_name_int(i, "skin", CInfo[playerid][i][Skin]);
        cache_get_value_name_int(i, "level", CInfo[playerid][i][Level]);
        cache_get_value_name_int(i, "exp", CInfo[playerid][i][Exp]);
        cache_get_value_name_float(i, "positionX", CInfo[playerid][i][Position][0]);
        cache_get_value_name_float(i, "positionY", CInfo[playerid][i][Position][1]);
        cache_get_value_name_float(i, "positionZ", CInfo[playerid][i][Position][2]);
        cache_get_value_name_float(i, "rotation", CInfo[playerid][i][Rotation]);
        cache_get_value_name_int(i, "interior", CInfo[playerid][i][Interior]);
        cache_get_value_name_int(i, "vw", CInfo[playerid][i][VirtualWorld]);
        cache_get_value_name_float(i, "health", CInfo[playerid][i][Health]);
        cache_get_value_name_float(i, "armour", CInfo[playerid][i][Armour]);
        cache_get_value_name(i, "regIP", CInfo[playerid][i][RegIP], 15);
        cache_get_value_name(i, "lastIP", CInfo[playerid][i][LastIP], 15);
        cache_get_value_name(i, "regDate", CInfo[playerid][i][RegDate], 14);
        cache_get_value_name(i, "lastDate", CInfo[playerid][i][LastDate], 14);
    }
    return 1;
}

/*      [ ЗАПИСЫВАЕМ ДАННЫЕ ПЕРСОНАЖА В БАЗУ ДАННЫХ ]      */
/*      [ WE WRITE THE CHARACTER'S DATA TO THE DATABASE ]      */
stock Data_Set_CharacterInfo(playerid)
{
    GetPlayerPos(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][0], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][1], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][2]);
    GetPlayerFacingAngle(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Rotation]);
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Interior] = GetPlayerInterior(playerid);
    CInfo[playerid][PInfo[playerid][CharacterSelect]][VirtualWorld] = GetPlayerVirtualWorld(playerid);
    GetPlayerHealth(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Health]);
    GetPlayerArmour(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Armour]);

    static const query[] = "UPDATE characters SET level = '%d', exp = '%d', positionX = '%f', positionY = '%f', positionZ = '%f', rotation = '%f', interior = '%d', vw = '%d', health = '%f', armour = '%f' WHERE login = '%s' LIMIT 1";
    new mysql[sizeof(query)+(-2+3)+(-2+3)+(-2+8)+(-2+8)+(-2+8)+(-2+8)+(-2+3)+(-2+10)+(-2+3)+(-2+3)+(-2+MAX_PLAYER_NAME)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, CInfo[playerid][PInfo[playerid][CharacterSelect]][Level], CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][0], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][1], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][2], CInfo[playerid][PInfo[playerid][CharacterSelect]][Rotation], CInfo[playerid][PInfo[playerid][CharacterSelect]][Interior], CInfo[playerid][PInfo[playerid][CharacterSelect]][VirtualWorld], CInfo[playerid][PInfo[playerid][CharacterSelect]][Health], CInfo[playerid][PInfo[playerid][CharacterSelect]][Armour], CInfo[playerid][PInfo[playerid][CharacterSelect]][Login]);
    mysql_query(SInfo[MySQL], mysql, false);
    return 1;
}