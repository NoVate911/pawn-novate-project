/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ СЕРВЕРА ]      */
/*      [ SECOND TIMER FOR THE SERVER ]      */
function TimerOnServerSecond()
{
    // Получение времени | Getting the time
    gettime(TInfo[Hour], TInfo[Minute], TInfo[Second]);

    // Проверка зарплаты (PAYDAY) | Salary Check (PAYDAY)
    if(PayDayCheck())
        PayDayLaunch();

    return STimerInfo[Second] = SetTimer("TimerOnServerSecond", 1000, false);
}