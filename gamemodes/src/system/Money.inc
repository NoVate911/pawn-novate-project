/*      [ УСТАНОВИТЬ ДЕНЬГИ ПЕРСОНАЖУ ]      */
/*      [ SET MONEY TO THE CHARACTER ]      */
stock Money_Set(playerid, money)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Money] = money;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Money]);
    if(GetPlayerMoney(playerid) == CInfo[playerid][PInfo[playerid][CharacterSelect]][Money])
        return true;
    return false;
}

/*      [ ОТНЯТЬ ДЕНЬГИ У ПЕРСОНАЖА ]      */
/*      [ TAKE MONEY AWAY FROM A CHARACTER ]      */
stock Money_Take(playerid, money)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Money] -= money;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Money]);
    if(GetPlayerMoney(playerid) == CInfo[playerid][PInfo[playerid][CharacterSelect]][Money])
        return true;
    return false;
}

/*      [ ВЫДАТЬ ДЕНЬГИ ПЕРСОНАЖУ ]      */
/*      [ GIVE MONEY TO A CHARACTER ]      */
stock Money_Give(playerid, money)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Money] += money;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Money]);
    if(GetPlayerMoney(playerid) == CInfo[playerid][PInfo[playerid][CharacterSelect]][Money])
        return true;
    return false;
}

/*      [ ОБНОВИТЬ ДЕНЬГИ У ПЕРСОНАЖА ]      */
/*      [ UPGRADE YOUR CHARACTER'S MONEY ]      */
stock Money_Update(playerid)
{
    if(GetPlayerMoney(playerid) != CInfo[playerid][PInfo[playerid][CharacterSelect]][Money])
    {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Money]);
        return true;
    }
    return false;
}