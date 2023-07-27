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

    Chat_Clear(0, true, 1);
    foreach(new i : Player)
    {
        if(PInfo[i][IsLogged])
        {
            if(!PAFKInfo[i][IsTrue])
            {
                SCMf(i, -1, "===== ЗАРПЛАТА =====");
                SCMf(i, -1, "");
                SCMf(i, -1, "Текущее время: %d:%d", TInfo[Hour], TInfo[Minute]);
                SCMf(i, -1, "");
                SCMf(i, -1, "====================");
            }
        }
    }
    Chat_Clear(0, true, 1);

    PDInfo[IsPassed] = true;
    return 1;
}