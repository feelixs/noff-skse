
// 1406be880
ulonglong BSTEventSource_SendEvent(longlong *param_1,undefined8 param_2)

{
  longlong *plVar1;
  ulonglong *puVar2;
  char cVar3;
  ulonglong uVar4;
  longlong *plVar5;
  ulonglong *puVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  ulonglong uVar13;
  int *piStackX_8;
  undefined8 uVar14;

  uVar14 = 0xfffffffffffffffe;
  FUN_1401949b0(&piStackX_8,param_1 + 9);
  cVar3 = (char)param_1[10];
  *(undefined1 *)(param_1 + 10) = 1;
  uVar13 = 0;
  if ((cVar3 == '\0') && ((int)param_1[5] != 0)) {
    if (*(uint *)(param_1 + 5) != 0) {
      plVar5 = (longlong *)param_1[3];
      plVar1 = plVar5 + *(uint *)(param_1 + 5);
      for (; plVar5 != plVar1; plVar5 = plVar5 + 1) {
        uVar4 = 0xffffffff;
        uVar8 = uVar13;
        if (*(uint *)(param_1 + 2) == 0) {
LAB_1406be926:
          FUN_1406bdff0(param_1,plVar5);
        }
        else {
          do {
            uVar7 = uVar8;
            if ((int)uVar4 != -1) goto LAB_1406be931;
            iVar10 = (int)uVar7;
            if (*(longlong *)(*param_1 + uVar7 * 8) != *plVar5) {
              uVar7 = 0xffffffff;
            }
            uVar11 = iVar10 + 1;
            uVar4 = uVar7;
            uVar8 = (ulonglong)uVar11;
          } while (uVar11 < *(uint *)(param_1 + 2));
          if ((int)uVar7 == -1) goto LAB_1406be926;
        }
LAB_1406be931:
      }
    }
    if (param_1[3] != 0) {
      *(undefined4 *)(param_1 + 5) = 0;
    }
  }
  uVar4 = (ulonglong)*(uint *)(param_1 + 2);
  if (*(uint *)(param_1 + 2) != 0) {
    puVar6 = (ulonglong *)*param_1;
    puVar2 = puVar6 + uVar4;
    uVar8 = uVar13;
    while ((puVar2 != puVar6 && ((int)uVar8 == 0))) {
      if ((int)param_1[8] == 0) {
LAB_1406be9a7:
        uVar4 = (**(code **)(*(longlong *)*puVar6 + 8))((longlong *)*puVar6,param_2,param_1);
        uVar8 = uVar4 & 0xffffffff;
      }
      else {
        iVar10 = -1;
        uVar7 = uVar13;
        if (*(uint *)(param_1 + 8) == 0) goto LAB_1406be9a7;
        do {
          if (iVar10 != -1) goto LAB_1406be9b9;
          uVar4 = *puVar6;
          iVar10 = (int)uVar7;
          if (*(ulonglong *)(param_1[6] + uVar7 * 8) != uVar4) {
            iVar10 = -1;
          }
          uVar11 = (int)uVar7 + 1;
          uVar7 = (ulonglong)uVar11;
        } while (uVar11 < *(uint *)(param_1 + 8));
        if (iVar10 == -1) goto LAB_1406be9a7;
      }
LAB_1406be9b9:
      puVar6 = puVar6 + 1;
    }
  }
  *(char *)(param_1 + 10) = cVar3;
  if ((cVar3 == '\0') && ((int)param_1[8] != 0)) {
    uVar4 = (ulonglong)*(uint *)(param_1 + 8);
    if (*(uint *)(param_1 + 8) != 0) {
      puVar6 = (ulonglong *)param_1[6];
      puVar2 = puVar6 + uVar4;
      for (; puVar6 != puVar2; puVar6 = puVar6 + 1) {
        uVar11 = *(uint *)(param_1 + 2);
        uVar8 = 0xffffffff;
        uVar7 = uVar13;
        if (uVar11 != 0) {
          do {
            uVar9 = uVar7;
            if ((int)uVar8 != -1) goto LAB_1406bea26;
            iVar10 = (int)uVar9;
            uVar4 = *puVar6;
            if (*(ulonglong *)(*param_1 + uVar9 * 8) != uVar4) {
              uVar9 = 0xffffffff;
            }
            uVar12 = iVar10 + 1;
            uVar8 = uVar9;
            uVar7 = (ulonglong)uVar12;
          } while (uVar12 < uVar11);
          if ((int)uVar9 != -1) {
LAB_1406bea26:
            uVar12 = (uint)(uVar11 - (int)uVar8 != 1);
            uVar4 = FUN_140cc67f0(param_1 + 2,*param_1,uVar8,uVar11 - uVar12,uVar12,8,uVar14);
            *(int *)(param_1 + 2) = (int)param_1[2] + -1;
          }
        }
      }
    }
    if (param_1[6] != 0) {
      *(undefined4 *)(param_1 + 8) = 0;
    }
  }
  if ((piStackX_8 != (int *)0x0) && (uVar4 = GetCurrentThreadId(), *piStackX_8 == (int)uVar4)) {
    if (piStackX_8[1] == 1) {
      *piStackX_8 = 0;
      uVar4 = 1;
      LOCK();
      uVar11 = piStackX_8[1];
      if (uVar11 == 1) {
        piStackX_8[1] = 0;
      }
      else {
        uVar4 = (ulonglong)uVar11;
      }
      UNLOCK();
    }
    else {
      LOCK();
      piStackX_8[1] = piStackX_8[1] + -1;
      UNLOCK();
    }
  }
  return uVar4;
}

