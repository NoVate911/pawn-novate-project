stock Works_Init()
{
    new tickCount = GetTickCount();
    Work_Loader_LV_Init();
    Work_Farmer_LV_Init();
    return printf("%s Начальные работы загружены за %dms.", DEBUG_INFO, GetTickCount() - tickCount);
}