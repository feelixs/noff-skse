
// 1407ec640
undefined8 UndefinedFunction_1407ec640(longlong *param_1,longlong *param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  longlong *plVar5;
  undefined4 *puVar6;
  longlong lVar7;
  undefined4 uVar8;
  undefined4 auStackX_10 [2];
  longlong lStackX_20;
  longlong *plStack_28;
  longlong lStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  byte bStack_10;

  if (param_2 == (longlong *)0x0) {
    return 0;
  }
  plVar5 = (longlong *)(**(code **)(*param_2 + 0x478))(param_2);
  if (((plVar5 == (longlong *)0x0) || (*(longlong *)(plVar5[8] + 0x100) == 0)) ||
     ((*(byte *)(*(longlong *)(plVar5[8] + 0x100) + 0x38) & 1) == 0)) {
    if ((param_3 != 0xc) && (1 < param_3 - 0x17U)) {
      return 0;
    }
  }
  else {
    (**(code **)(*plVar5 + 0x5f8))();
  }
  uVar8 = 0;
  cVar4 = func_0x000140400780(param_2,param_1);
  if (cVar4 == '\0') {
    return 0;
  }
  lVar7 = param_1[0x37];
  if ((lVar7 != 0) || (lVar7 = param_1[0x2c], lVar7 != 0)) {
    uVar8 = *(undefined4 *)(lVar7 + 0x14);
  }
  puVar6 = (undefined4 *)(**(code **)(*param_1 + 0x288))(param_1);
  auStackX_10[0] = gNullRefHandleId;
  if (puVar6 != (undefined4 *)0x0) {
    auStackX_10[0] = *puVar6;
  }
  lStackX_20 = 0;
  LookupObjectByRefHandle(auStackX_10,&lStackX_20);
  LOCK();
  *(int *)(param_2 + 5) = (int)param_2[5] + 1;
  UNLOCK();
  uVar3 = *(undefined4 *)(param_1[8] + 0x14);
  lVar7 = func_0x0001401d5230();
  LOCK();
  *(int *)(param_2 + 5) = (int)param_2[5] + 1;
  UNLOCK();
  if (lStackX_20 != 0) {
    LOCK();
    *(int *)(lStackX_20 + 0x28) = *(int *)(lStackX_20 + 0x28) + 1;
    UNLOCK();
  }
  lStack_20 = lStackX_20;
  bStack_10 = bStack_10 & 0xf0;
  plStack_28 = param_2;
  uStack_18 = uVar8;
  uStack_14 = uVar3;
  BSTEventSource_SendEvent(lVar7 + 0x5d8,&plStack_28); // 1407ec772
  if (lStack_20 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_20 + 0x28);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar2 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_20 + 0x20) + 8))();
    }
  }
  if (plStack_28 != (longlong *)0x0) {
    LOCK();
    plVar5 = plStack_28 + 5;
    lVar7 = *plVar5;
    *(int *)plVar5 = (int)*plVar5 + -1;
    UNLOCK();
    if (((int)lVar7 - 1U & 0x3ff) == 0) {
      (**(code **)(plStack_28[4] + 8))();
    }
  }
  LOCK();
  plVar5 = param_2 + 5;
  lVar7 = *plVar5;
  *(int *)plVar5 = (int)*plVar5 + -1;
  UNLOCK();
  if (((int)lVar7 - 1U & 0x3ff) == 0) {
    (**(code **)(param_2[4] + 8))();
  }
  if (lStackX_20 != 0) {
    LOCK();
    piVar1 = (int *)(lStackX_20 + 0x28);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar2 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStackX_20 + 0x20) + 8))();
    }
  }
  return 1;
}

