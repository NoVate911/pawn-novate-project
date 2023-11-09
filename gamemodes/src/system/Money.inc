/*      [ УСТАНОВИТЬ ДЕНЬГИ ПЕРСОНАЖУ ]      */
/*      [ SET MONEY TO THE CHARACTER ]      */
stock MoneySet(playerid, money)
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
stock MoneyTake(playerid, money)
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
stock MoneyGive(playerid, money)
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
stock MoneyUpdate(playerid)
{
    if(GetPlayerMoney(playerid) != CInfo[playerid][PInfo[playerid][CharacterSelect]][Money])
    {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Money]);
        return true;
    }
    return false;
}