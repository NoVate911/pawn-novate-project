stock Works_Init()
{
    new tickCount = GetTickCount();
    Work_Loader_Init();
    return printf("%s Начальные работы загружены за %dms.", DEBUG_INFO, GetTickCount() - tickCount);
}