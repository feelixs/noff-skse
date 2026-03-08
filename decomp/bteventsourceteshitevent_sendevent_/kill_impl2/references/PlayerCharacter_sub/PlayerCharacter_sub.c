// 1406b9dc0
void UndefinedFunction_1406b9dc0(longlong param_1)

{
  int *piVar1;
  int iVar2;
  longlong lVar3;
  undefined4 auStackX_8 [2];
  longlong lStackX_10;

  auStackX_8[0] = *(undefined4 *)(param_1 + 0x108);
  lStackX_10 = 0;
  LookupObjectByRefHandle(auStackX_8,&lStackX_10);
  lVar3 = lStackX_10;
  if (lStackX_10 != 0) {
    Actor::Kill_impl2(param_1,lStackX_10,0,1,0); // 1406b9e15
  }
  if (*(longlong *)(param_1 + 0xf8) != 0) {
    FUN_140715ae0(*(longlong *)(param_1 + 0xf8),0,param_1);
  }
  *(uint *)(param_1 + 0x204) = *(uint *)(param_1 + 0x204) & 0xffffbfff;
  if (lVar3 != 0) {
    LOCK();
    piVar1 = (int *)(lVar3 + 0x28);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar2 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lVar3 + 0x20) + 8))();
    }
  }
  return;
}

