/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ СЕРВЕРА ]      */
/*      [ SECOND TIMER FOR THE SERVER ]      */
function Timer_OnServerSecond()
{
    // Получение времени | Getting the time
    gettime(TInfo[Hour], TInfo[Minute], TInfo[Second]);

    // Обновление времени на сервере | Updating the time on the server
    if(TInfo[TimeOfDayTime] > 0)
        TInfo[TimeOfDayTime]--;
    else
    {
        Time_Set();
        TInfo[TimeOfDayTime] = MAX_TIME_UPDATE_TIME;
    }

    // Проверка зарплаты (PAYDAY) | Salary Check (PAYDAY)
    if(PayDay_Check())
        PayDay_Launch();
    return STimerInfo[Second] = SetTimer("Timer_OnServerSecond", 1000, false);
}