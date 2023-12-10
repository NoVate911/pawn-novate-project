/*      [ ПРОВЕРКА НА ЗАРПЛАТУ (PAYDAY) ]      */
/*      [ SALARY CHECK (PAYDAY) ]      */
stock PayDayCheck()
{
    if(TInfo[Minute] == 0 && (0 <= TInfo[Second] <= 3))
    {
        if(!PDInfo[IsPassed])
            return true;
    }
    else
        PDInfo[IsPassed] = false;
    return false;
}

/*      [ ЗАПУСК ЗАРПЛАТЫ (PAYDAY) ]      */
/*      [ SALARY LAUNCH (PAYDAY) ]      */
stock PayDayLaunch()
{
    printf("%s Текущее время %02d:%02d.", DEBUG_INFO, TInfo[Hour], TInfo[Minute]);
    WeatherSet();
    foreach(new p : Player)
    {
        if(PInfo[p][IsLogged])
        {
            ChatClear(p, false, 1);
            SCM(p, -1, "===== ЗАРПЛАТА =====");
            SCM(p, -1, "");
            SCMf(p, -1, "Текущее время: %02d:%02d", TInfo[Hour], TInfo[Minute]);
            if(!PAFKInfo[p][IsTrue])
            {
                if(CInfo[p][PInfo[p][CharacterSelect]][PlayedHourTime] < MAX_PAYDAY_PLAYED_HOUR)
                    SCMf(p, -1, "Для получения зарплаты нужно отыграть %d минут.", MAX_PAYDAY_PLAYED_HOUR);
                else
                {
                    SCMf(p, -1, "Пособие по безработице: %d$", MAX_PAYDAY_BENEFIT);
                    MoneyGive(p, MAX_PAYDAY_BENEFIT);
                }
            }
            else
                SCM(p, -1, "Для получения зарплаты нельзя находиться в AFK.");
            SCM(p, -1, "");
            SCM(p, -1, "====================");
            ChatClear(p, false, 1);
            CInfo[p][PInfo[p][CharacterSelect]][PlayedHourTime] = 0;
        }
    }

    PDInfo[IsPassed] = true;
    return 1;
}