/*      [ ПРОВЕРКА УРОВНЯ ИГРОКА ]      */
/*      [ CHECKING THE PLAYER'S LEVEL ]      */
stock LevelCheck(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][ExpTime] > 0)
        CInfo[playerid][PInfo[playerid][CharacterSelect]][ExpTime]--;
    else
    {
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp]++;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][ExpTime] = MAX_TIME_UPDATE_LEVEL;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp] >= LevelNeedExp(playerid, PInfo[playerid][CharacterSelect]))
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Level] >= MAX_LEVEL)
                SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"У вас уже максимальный уровень.");
            else
                LevelUpdate(playerid);
        }
    }
    return 1;
}

/*      [ ОБНОВЛЕНИЕ УРОВНЯ ИГРОКА ]      */
/*      [ PLAYER LEVEL UPGRADE ]      */
stock LevelUpdate(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Level]++;
    CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp] = 0;
    
    ChatClear(playerid, _, 1);
    SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Поздравляем! Ваш уровень повышен.");
    SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"У вас %d уровень.", CInfo[playerid][PInfo[playerid][CharacterSelect]][Level]);
    ChatClear(playerid, _, 1);
    return 1;
}

/*      [ ВЫЧИСЛЕНИЕ НУЖНОГО КОЛИЧЕСТВА ОПЫТА ДЛЯ ПОВЫШЕНИЯ УРОВНЯ ]      */
/*      [ CALCULATING THE RIGHT AMOUNT OF EXPERIENCE TO LEVEL UP ]      */
stock LevelNeedExp(playerid, characterid)
{
    new needExp;
    needExp = (MAX_EXP_UPDATE_LEVEL * (CInfo[playerid][characterid][Level] + 1)) * MAX_EXP_UPDATE_LEVEL;
    return needExp;
}