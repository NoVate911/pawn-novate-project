/*      [ ПЕРЕМЕННЫЕ ДЛЯ СЕРВЕРА ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL,
    Weather
}
new SInfo[ServerInfo];

/*      [ ПЕРЕМЕННЫЕ ТАЙМЕРА ДЛЯ СЕРВЕРА ]      */
/*      [ TIMER VARIABLES FOR THE SERVER ]      */
enum ServerTimerInfo
{
    Second
}
new STimerInfo[ServerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ ВРЕМЕНИ ДЛЯ СЕРВЕРА ]      */
/*      [ TIME VARIABLES FOR THE SERVER ]      */
enum TimeInfo
{
    bool:IsChanged,

    Hour,
    Minute,
    Second
}
new TInfo[TimeInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ЗАРПЛАТЫ ]      */
/*      [ VARIABLES FOR SALARY ]      */
enum PayDayInfo
{
    bool:IsPassed
}
new PDInfo[PayDayInfo];

/*      [ ПЕРЕМЕННЫЕ АВТОШКОЛЫ ]      */
/*      [ VARIABLE DRIVING SCHOOLS ]      */
enum DrivingSchoolInfo
{
    STREAMER_TAG_PICKUP:BeginningPickup, // Чекпоинт начала сдачи экзамена | The checkpoint for the start of the exam
    STREAMER_TAG_3D_TEXT_LABEL:Beginning3DText, // Текст начала сдачи экзамена | The text of the beginning of the exam
}
new DSchoolInfo[MAX_DRIVING_SCHOOL][DrivingSchoolInfo];