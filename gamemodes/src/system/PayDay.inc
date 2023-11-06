/*      [ ПРОВЕРКА НА ЗАРПЛАТУ (PAYDAY) ]      */
/*      [ SALARY CHECK (PAYDAY) ]      */
stock PayDay_Check()
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
stock PayDay_Launch()
{
    printf("%s Запущенный PayDay прошёл успешно.", DEBUG_INFO);

    foreach(new i : Player)
    {
        if(PInfo[i][IsLogged])
        {
            Chat_Clear(i, false, 1);
            SCM(i, -1, "===== ЗАРПЛАТА =====");
            SCM(i, -1, "");
            SCMf(i, -1, "Текущее время: %d:%d", TInfo[Hour], TInfo[Minute]);
            if(!PAFKInfo[i][IsTrue])
            {
                SCMf(i, -1, "Пособие по безработице: %d$", MAX_PAYDAY_BENEFIT);
                Money_Give(i, 500);
            }
            else
            {
                SCM(i, -1, "Для получения зарплаты нельзя находиться в AFK");
            }
            SCM(i, -1, "");
            SCM(i, -1, "====================");
            Chat_Clear(i, false, 1);
        }
    }

    PDInfo[IsPassed] = true;
    return 1;
}