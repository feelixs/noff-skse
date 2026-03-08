

undefined8 UndefinedFunction_140659710(int *param_1)
// 140659710
{
  int *piVar1;
  int iVar2;
  longlong lVar3;
  longlong alStackX_8 [4];

  if (*param_1 != gNullRefHandleId) {
    alStackX_8[0] = 0;
    LookupObjectByRefHandle(param_1,alStackX_8);
    lVar3 = alStackX_8[0];
    if (alStackX_8[0] != 0) {
      Actor::Kill_impl2(alStackX_8[0],0,0,1,0);  // 140659757
      LOCK();
      piVar1 = (int *)(lVar3 + 0x28);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar2 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lVar3 + 0x20) + 8))();
      }
    }
  }
  return 1;
}

