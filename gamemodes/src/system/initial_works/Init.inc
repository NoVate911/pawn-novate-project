/*      [ ЗАГРУЗКА ВСЕХ РАБОТ ]      */
/*      [ UPLOADING ALL WORKS ]      */
stock WorksInit()
{
    new tickCount = GetTickCount();
    WorkLoaderLVInit();
    WorkFarmerLVInit();
    WorkDiverLVInit();
    printf("%s Начальные работы загружены за %dms.", DEBUG_INFO, GetTickCount() - tickCount);
    return 1;
}