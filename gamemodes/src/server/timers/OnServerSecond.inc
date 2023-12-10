/*      [ СЕКУНДНЫЙ ТАЙМЕР ДЛЯ СЕРВЕРА ]      */
/*      [ SECOND TIMER FOR THE SERVER ]      */
function TimerOnServerSecond()
{
    // Получение времени | Getting the time
    gettime(TInfo[Hour], TInfo[Minute], TInfo[Second]);
    if(!TInfo[IsChanged])
        TimeSet();

    // Проверка зарплаты (PAYDAY) | Salary Check (PAYDAY)
    if(PayDayCheck())
        PayDayLaunch();

    // Обновление скорости транспорта | Updating the speed of transport
    if(VehicleCount > 0)
    {
        for(new vehicle = 0; vehicle < MAX_VEHICLES; vehicle++)
            VehicleCalculateSpeedValue(vehicle);
    }

    return STimerInfo[Second] = SetTimer("TimerOnServerSecond", 1000, false);
}