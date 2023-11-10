/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ СЕРВЕРА ]      */
/*      [ SECOND TIMER FOR THE SERVER ]      */
function TimerOnServerSecond()
{
    // Получение времени | Getting the time
    gettime(TInfo[Hour], TInfo[Minute], TInfo[Second]);
    
    // Обновление времени на сервере | Updating the time on the server
    if(TInfo[TimeOfDayTime] > 0)
        TInfo[TimeOfDayTime]--;
    else
    {
        TimeSet();
        TInfo[TimeOfDayTime] = MAX_TIME_UPDATE_TIME;
    }

    // Проверка зарплаты (PAYDAY) | Salary Check (PAYDAY)
    if(PayDayCheck())
        PayDayLaunch();

    return STimerInfo[Second] = SetTimer("TimerOnServerSecond", 1000, false);
}