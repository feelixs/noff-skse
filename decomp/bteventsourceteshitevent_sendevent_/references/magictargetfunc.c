
// 1406c50a0
char MagicTarget::Func1(longlong param_1,longlong *param_2)

{
  int *piVar1;
  longlong lVar2;
  longlong *plVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  bool bVar12;
  undefined4 local_res8 [2];
  undefined4 local_res10;
  undefined1 local_res18 [8];
  undefined1 local_res20 [8];
  undefined8 in_stack_ffffffffffffff68;
  undefined4 uVar13;
  longlong local_88;
  longlong local_80 [3];
  longlong local_68;
  undefined4 local_60;
  undefined4 local_5c;
  byte local_58;

  uVar13 = (undefined4)((ulonglong)in_stack_ffffffffffffff68 >> 0x20);
  local_80[1] = 0xfffffffffffffffe;
  lVar2 = param_1 + -0xa0;
  local_res10 = Character::sub(lVar2);
  plVar3 = (longlong *)param_2[1];
  cVar4 = Actor::IsGhost(lVar2);
  uVar10 = 0;
  if ((cVar4 != '\0') &&
     ((iVar5 = (**(code **)(*plVar3 + 0x298))(plVar3), iVar5 != 6 ||
      (iVar5 = (**(code **)(*plVar3 + 0x2a8))(plVar3), iVar5 != 0)))) {
    if (lVar2 == gPlayerCharacter3) {
      cVar4 = func_0x00014014ad80();
      bVar12 = cVar4 == '\0';
    }
    else {
      iVar5 = (**(code **)(*plVar3 + 0x298))(plVar3);
      bVar12 = iVar5 != 4;
    }
    if (bVar12) {
      return '\0';
    }
  }
  if ((((*param_2 != 0) && (lVar2 != *param_2)) &&
      (cVar4 = func_0x000140143430(param_2[2]), cVar4 != '\0')) &&
     (cVar4 = (**(code **)(*(longlong *)*param_2 + 0x6b0))((longlong *)*param_2,lVar2),
     cVar4 == '\0')) {
    return '\0';
  }
  if ((((((char)param_2[9] != '\0') && (param_2[2] != 0)) &&
       (cVar4 = func_0x000140143430(), cVar4 != '\0')) &&
      (((gNiPoint3_Zero != *(float *)(param_2 + 6) ||
        (DAT_143272c9c != *(float *)((longlong)param_2 + 0x34))) ||
       (DAT_143272ca0 != *(float *)(param_2 + 7))))) &&
     (cVar4 = Character::sub(lVar2,param_2 + 6,DAT_142008700), cVar4 != '\0')) {
    local_res8[0] = 0x3f800000;
    lVar9 = param_2[2];
    cVar4 = Character::sub(lVar2,*param_2,param_2[1],local_res8,lVar9);
    uVar13 = (undefined4)((ulonglong)lVar9 >> 0x20);
    if (cVar4 != '\0') {
      return '\0';
    }
    *(undefined4 *)(param_2 + 8) = local_res8[0];
  }
  cVar4 = SUB_1405c3250(param_1,param_2);
  if (cVar4 == '\0') {
    return '\0';
  }
  uVar6 = (**(code **)(*(longlong *)param_2[1] + 0x298))();
  if ((uVar6 < 0xb) && ((0x412U >> (uVar6 & 0x1f) & 1) != 0)) {
    return cVar4;
  }
  if (*param_2 == 0) {
    return cVar4;
  }
  if (*(longlong *)(*param_2 + 0x40) == *(longlong *)(param_1 + -0x60)) {
    return cVar4;
  }
  if (param_2[2] == 0) {
    return cVar4;
  }
  if ((*(uint *)(*(longlong *)(param_2[2] + 0x10) + 0x68) >> 4 & 1) != 0) {
    return cVar4;
  }
  lVar9 = param_2[3];
  if ((lVar9 == 0) || (*(char *)(lVar9 + 0x1a) != ')')) {
    lVar9 = 0;
  }
  uVar7 = GetOrCreateObjectRefHandle_Safe(lVar2,local_res18);
  local_80[0] = 0;
  LookupObjectByRefHandle(uVar7,local_80);
  uVar7 = GetOrCreateObjectRefHandle_Safe(*param_2,local_res20);
  local_88 = 0;
  LookupObjectByRefHandle(uVar7,&local_88);
  lVar8 = *(longlong *)(*(longlong *)(param_2[2] + 0x10) + 200);
  if (lVar8 != 0) {
    uVar10 = *(undefined4 *)(lVar8 + 0x14);
  }
  if (lVar9 == 0) {
    uVar11 = *(undefined4 *)(param_2[1] + 0x14);
  }
  else {
    uVar11 = *(undefined4 *)(lVar9 + 0x14);
  }
  lVar8 = func_0x0001401d5230();
  lVar9 = local_88;
  if (local_80[0] != 0) {
    LOCK();
    *(int *)(local_80[0] + 0x28) = *(int *)(local_80[0] + 0x28) + 1;
    UNLOCK();
  }
  local_80[2] = local_80[0];
  if (local_88 != 0) {
    LOCK();
    *(int *)(local_88 + 0x28) = *(int *)(local_88 + 0x28) + 1;
    UNLOCK();
  }
  local_68 = local_88;
  local_58 = local_58 & 0xf0;
  local_60 = uVar11;
  local_5c = uVar10;
  BSTEventSource_SendEvent(lVar8 + 0x5d8,local_80 + 2);
  if (local_68 != 0) {
    LOCK();
    piVar1 = (int *)(local_68 + 0x28);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    lVar9 = local_88;
    if ((iVar5 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(local_68 + 0x20) + 8))();
      lVar9 = local_88;
    }
  }
  if (local_80[2] != 0) {
    LOCK();
    piVar1 = (int *)(local_80[2] + 0x28);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    lVar9 = local_88;
    if ((iVar5 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(local_80[2] + 0x20) + 8))();
      lVar9 = local_88;
    }
  }
  if (0 < (int)((longlong *)param_2[1])[0xe]) {
    iVar5 = (**(code **)(*(longlong *)param_2[1] + 0x298))();
    if (iVar5 == 6) {
      plVar3 = (longlong *)param_2[1];
      iVar5 = (**(code **)(*plVar3 + 0x2a8))(plVar3);
      if (((iVar5 == 1) && (iVar5 = (**(code **)(*plVar3 + 0x2b8))(plVar3), iVar5 == 1)) &&
         ((param_2[3] == 0 || ((*(char *)(param_2[3] + 0x1a) != '*' || ((char)param_2[9] == '\0'))))
         )) goto LAB_1406c5419;
    }
    iVar5 = (**(code **)(*(longlong *)param_2[1] + 0x298))();
    if (iVar5 != 7) {
      Actor_QueueHitTask(gBSTaskPool,lVar2,*param_2,param_2[2],CONCAT44(uVar13,local_res10));
    }
  }
LAB_1406c5419:
  if (lVar9 != 0) {
    LOCK();
    piVar1 = (int *)(lVar9 + 0x28);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar5 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lVar9 + 0x20) + 8))();
    }
  }
  if (local_80[0] != 0) {
    LOCK();
    piVar1 = (int *)(local_80[0] + 0x28);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar5 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(local_80[0] + 0x20) + 8))();
      return cVar4;
    }
    return cVar4;
  }
  return cVar4;
}

