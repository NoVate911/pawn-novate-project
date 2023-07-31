/*      [ ЗАГРУЗКА БАНОВ АККАУНТОВ ]      */
/*      [ LOADING ACCOUNT BANS ]      */
stock Ban_Account_Init()
{
    static const query[] = "SELECT id,login,type,time,author,reason FROM accounts_bans LIMIT %d";
    new mysql[sizeof(query)+(-2+11)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, MAX_BAN_ACCOUNTS);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    BAccountCount = cache_num_rows();
    if(BAccountCount)
    {
        Data_Get_BanAccountInfo();
        printf("%s Загружено %d банов аккаунтов.", DEBUG_INFO, BAccountCount);
        cache_delete(cache);
        return true;
    }
    else
        printf("%s Ни одного бана аккаунта не найдено.", DEBUG_INFO);
    cache_delete(cache);
    return false;
}

/*      [ ПОИСК АККАУНТА В МАССИВЕ ]      */
/*      [ SEARCH FOR AN ACCOUNT IN THE ARRAY ]      */
stock Ban_Account_Find(playerid)
{
    for(new i = 0; i < BAccountCount; i++)
    {
        if(BAccountInfo[i][Login] == PInfo[playerid][Nick])
            return true;
    }
    return false;
}

/*      [ ПРОВЕРКА НА БЛОКИРОВКУ АККАУНТА ]      */
/*      [ CHECKING FOR ACCOUNT BLOCKING ]      */
stock Ban_Account_Check(playerid)
{
    for(new i = 0; i < BAccountCount; i++)
    {
        if(BAccountInfo[i][Login] == PInfo[playerid][Nick])
        {
            if(BAccountInfo[i][Type] != 0)
                return true;
        }
    }
    return false;
}

/*      [ УСТАНОВКА БЛОКИРОВКИ АККАУНТА ]      */
/*      [ SETTING AN ACCOUNT LOCK ]      */
stock Ban_Account_Set(playerid, type, time, author[], reason[])
{
    if(Ban_Account_Find(playerid))
    {
        if(Ban_Account_Update(playerid, type, time, author, reason))
        {
            Ban_Account_Init();
            return true;
        }
    }
    else
    {
        if(Ban_Account_Insert(playerid, type, time, author, reason))
        {
            Ban_Account_Init();
            return true;
        }
    }
    return false;
}

/*      [ ОБНОВЛЕНИЕ БЛОКИРОВКИ АККАУНТА В БАЗЕ ДАННЫХ ]      */
/*      [ UPDATING THE ACCOUNT LOCK IN THE DATABASE ]      */
stock Ban_Account_Update(playerid, type, time, author[], reason[])
{
    static const query[] = "UPDATE accounts_bans SET type = '%d', time = '%d', author = '%s', reason = '%s' WHERE login = '%s' LIMIT 1";
    new mysql[sizeof(query)+(-2+1)+(-2+11)+(-2+MAX_PLAYER_NAME)+(-2+(MAX_PLAYER_NAME*2))+(-2+MAX_PLAYER_NAME)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, type, time, author, reason, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login]);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    new const result = cache_num_results();
    cache_delete(cache);
    if(result)
        return true;
    return false;
}

/*      [ СОЗДАНИЕ БЛОКИРОВКИ АККАУНТА В БАЗЕ ДАННЫХ ]      */
/*      [ CREATING AN ACCOUNT LOCK IN THE DATABASE ]      */
stock Ban_Account_Insert(playerid, type, time, author[], reason[])
{
    static const query[] = "INSERT INTO accounts_bans (login,type,time,author,reason) VALUES ('%s','%d','%d','%s','%s')";
    new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+1)+(-2+11)+(-2+MAX_PLAYER_NAME)+(-2+(MAX_PLAYER_NAME*2))];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], type, time, author, reason);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    new const result = cache_num_results();
    cache_delete(cache);
    if(result)
        return true;
    return false;
}

/*      [ ЗАГРУЗКА БАНОВ ПЕРСОНАЖЕЙ ]      */
/*      [ LOADING CHARACTER BANS ]      */
stock Ban_Character_Init()
{
    static const query[] = "SELECT id,login,characterID,type,time,author,reason FROM characters_bans LIMIT %d";
    new mysql[sizeof(query)+(-2+11)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, MAX_BAN_CHARACTERS);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    BCharacterCount = cache_num_rows();
    if(BCharacterCount)
    {
        Data_Get_BanCharacterInfo();
        printf("%s Загружено %d банов персонажей.", DEBUG_INFO, BCharacterCount);
        cache_delete(cache);
        return true;
    }
    else
        printf("%s Ни одного бана персонажа не найдено.", DEBUG_INFO);
    cache_delete(cache);
    return false;
}

/*      [ ПОИСК ПЕРСОНАЖА В МАССИВЕ ]      */
/*      [ SEARCH FOR A CHARACTER IN THE ARRAY ]      */
stock Ban_Character_Find(playerid, character = -1)
{
    for(new i = 0; i < BCharacterCount; i++)
    {
        if(character == -1)
        {
            if(BCharacterInfo[i][CharacterID] == CInfo[playerid][PInfo[playerid][CharacterSelect]][ID])
                return true;
        }
        else
        {
            if(BCharacterInfo[i][CharacterID] == CInfo[playerid][character][ID])
                return true;
        }
    }
    return false;
}

/*      [ ПРОВЕРКА НА БЛОКИРОВКУ ПЕРСОНАЖА ]      */
/*      [ CHECKING FOR CHARACTER BLOCKING ]      */
stock Ban_Character_Check(playerid, character = -1)
{
    for(new i = 0; i < BCharacterCount; i++)
    {
        if(character == -1)
        {
            if(BCharacterInfo[i][CharacterID] == CInfo[playerid][PInfo[playerid][CharacterSelect]][ID])
            {
                if(BCharacterInfo[i][Type] != 0)
                    return true;
            }
        }
        else
        {
            if(BCharacterInfo[i][CharacterID] == CInfo[playerid][character][ID])
            {
                if(BCharacterInfo[i][Type] != 0)
                    return true;
            }
        }
    }
    return false;
}

/*      [ УСТАНОВКА БЛОКИРОВКИ ПЕРСОНАЖА ]      */
/*      [ SETTING A CHARACTER LOCK ]      */
stock Ban_Character_Set(playerid, type, time, author[], reason[])
{
    if(Ban_Character_Find(playerid))
    {
        if(Ban_Character_Update(playerid, type, time, author, reason))
        {
            Ban_Character_Init();
            return true;
        }
    }
    else
    {
        if(Ban_Character_Insert(playerid, type, time, author, reason))
        {
            Ban_Character_Init();
            return true;
        }
    }
    return false;
}

/*      [ ОБНОВЛЕНИЕ БЛОКИРОВКИ ПЕРСОНАЖА В БАЗЕ ДАННЫХ ]      */
/*      [ UPDATING THE CHARACTER LOCK IN THE DATABASE ]      */
stock Ban_Character_Update(playerid, type, time, author[], reason[])
{
    static const query[] = "UPDATE characters_bans SET type = '%d', time = '%d', author = '%s', reason = '%s' WHERE login = '%s' AND characterID = '%d' LIMIT 1";
    new mysql[sizeof(query)+(-2+1)+(-2+11)+(-2+MAX_PLAYER_NAME)+(-2+(MAX_PLAYER_NAME*2))+(-2+MAX_PLAYER_NAME)+(-2+11)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, type, time, author, reason, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][ID]);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    new const result = cache_num_results();
    cache_delete(cache);
    if(result)
        return true;
    return false;
}

/*      [ СОЗДАНИЕ БЛОКИРОВКИ ПЕРСОНАЖА В БАЗЕ ДАННЫХ ]      */
/*      [ CREATING A CHARACTER LOCK IN THE DATABASE ]      */
stock Ban_Character_Insert(playerid, type, time, author[], reason[])
{
    static const query[] = "INSERT INTO characters_bans (login,characterID,type,time,author,reason) VALUES ('%s','%d','%d','%d','%s','%s')";
    new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+11)+(-2+1)+(-2+11)+(-2+MAX_PLAYER_NAME)+(-2+(MAX_PLAYER_NAME*2))];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][ID], type, time, author, reason);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    new const result = cache_num_results();
    cache_delete(cache);
    if(result)
        return true;
    return false;
}