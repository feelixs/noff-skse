
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1406672b0
void Character::sub(longlong *param_1,float param_2)

{
  longlong *plVar1;
  longlong lVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  undefined1 uVar8;
  int iVar9;
  undefined4 uVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong *plVar13;
  uint uVar14;
  undefined8 uVar15;
  float fVar16;
  float fVar17;
  undefined1 *apuStackX_8 [4];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [72];

  if ((*(uint *)(param_1 + 2) >> 0xb & 1) != 0) {
    return;
  }
  if ((*(uint *)(param_1 + 0x1d) >> 1 & 1) == 0) {
    return;
  }
  if ((((*(uint *)(param_1 + 0x1d) >> 3 & 1) != 0) &&
      (lVar11 = (**(code **)(*param_1 + 0x250))(param_1), lVar11 != 0)) &&
     ((lVar2 = *(longlong *)(lVar11 + 0x98), (*(byte *)(lVar2 + 0xdc) & 1) == 0 ||
      ((*(char *)(lVar2 + 0xdc) < '\0' || (*(longlong *)(lVar2 + 0x248) != 0)))))) {
    if (*(char *)(lVar11 + 0xb0) == '\0') {
      (**(code **)(*param_1 + 600))(param_1,0);
    }
    else {
      BGSScene::sub(lVar11);
    }
  }
  bVar3 = true;
  if (((int)param_1[0x1d] < 0) ||
     (cVar5 = (**(code **)(*param_1 + 0x4c8))(param_1,0), cVar5 != '\0')) {
    bVar3 = false;
  }
  uVar15 = 0;
  bVar4 = false;
  if ((*(uint *)(param_1 + 0x19) & 0xe000000) == 0) {
    bVar4 = bVar3;
  }
  bVar3 = false;
  if ((*(uint *)(param_1 + 0x19) & 0x1e00000) != 0x600000) {
    bVar3 = bVar4;
  }
  if (bVar3) {
    *(uint *)((longlong)param_1 + 0x204) = *(uint *)((longlong)param_1 + 0x204) | 0x2000;
  }
  else {
    *(uint *)((longlong)param_1 + 0x204) = *(uint *)((longlong)param_1 + 0x204) & 0xffffdfff;
  }
  Character::sub(param_1,0);
  (**(code **)(*param_1 + 0x200))(param_1);
  if (((param_1[0x1f] != 0) && (cVar5 = ActorProcess::IsDoingFavor(), cVar5 != '\0')) &&
     (cVar5 = Character::sub(param_1,_gPlayerCharacter), cVar5 != '\0')) {
    lVar11 = FUN_1406e2590(param_1[0x1f]);
    fVar17 = _DAT_141ffc1f8;
    if (0.0 <= *(float *)(_gPlayerCharacter + 0x15c)) {
      if (lVar11 != 0) goto LAB_140667455;
LAB_140667494:
      *(float *)(_gPlayerCharacter + 0x15c) =
           *(float *)(_gPlayerCharacter + 0x15c) - _gSecondsSinceLastFrame_WorldTime;
    }
    else {
      if (lVar11 != 0) {
LAB_140667455:
        uVar12 = TESPackage::sub(lVar11,auStack_90,param_1);
        fVar16 = (float)FUN_1402edb50(param_1,uVar12);
        if (fVar16 <= fVar17 * fVar17) goto LAB_140667494;
      }
      Character::sub(param_1,0);
    }
  }
  cVar5 = Character::sub(param_1);
  if (cVar5 == '\0') {
    *(uint *)(param_1 + 0x1d) = *(uint *)(param_1 + 0x1d) & 0xffbfffff;
  }
  else {
    *(uint *)(param_1 + 0x1d) = *(uint *)(param_1 + 0x1d) | 0x400000;
  }
  if (param_1[0x1f] != 0) {
    FUN_140713340(param_1[0x1f],param_1);
    fVar17 = _gSecondsSinceLastFrame_WorldTime;
    fVar16 = (float)GetGlobalTimeMultiplier(_VATS_MODE_GetSingleton);
    FUN_1407133b0(param_1[0x1f],param_1,fVar16 * fVar17);
  }
  if ((*(uint *)((longlong)param_1 + 0x204) >> 0x1b & 1) != 0) {
    Character::sub(param_1);
    *(uint *)((longlong)param_1 + 0x204) = *(uint *)((longlong)param_1 + 0x204) & 0xf7ffffff;
  }
  if ((param_1[0x1f] != 0) && (*(char *)(param_1[0x1f] + 0x137) == '\0')) {
    Character::sub(param_1);
    lVar11 = FUN_1406e34c0(param_1[0x1f]);
    if ((lVar11 != 0) && ((*(uint *)(param_1[0x3f] + 0x108) >> 1 & 1) == 0)) {
      FUN_1406e3690(param_1[0x1f],lVar11,param_1);
    }
  }
  fVar17 = _gSecondsSinceLastFrame_WorldTime;
  if ((*(int *)(_VATS_MODE_GetSingleton + 0x20) == 4) &&
     (param_1 == *(longlong **)(_VATS_MODE_GetSingleton + 0x98))) {
    fVar16 = (float)GetGlobalTimeMultiplier();
    fVar17 = fVar17 * fVar16;
  }
  if (*(float *)(param_1 + 0x24) <= 0.0) {
    *(undefined4 *)((longlong)param_1 + 0x11c) = 0;
  }
  else {
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - fVar17;
  }
  cVar5 = -1;
  if (((param_1[0x1f] == 0) || (*(char *)(param_1[0x1f] + 0x137) != '\0')) ||
     (cVar6 = PlayerCharacter::sub(_gPlayerCharacter), cVar6 != '\0')) {
    cVar5 = PlayerCharacter::sub(_gPlayerCharacter);
    if (cVar5 == '\0') {
      if (param_1[0x1f] == 0) {
        fVar17 = -1.0;
      }
      else {
        fVar17 = *(float *)(param_1[0x1f] + 0x48);
      }
      if (_DAT_14319aec4 != fVar17) {
        FUN_140633650(_Calendar_Singleton);
      }
    }
    apuStackX_8[0] = auStack_80;
                    /* WARNING: Subroutine does not return */
    FUN_140cc6b20(auStack_80);
  }
  if ((*(uint *)(param_1 + 2) >> 5 & 1) != 0) {
    return;
  }
  if ((*(uint *)(param_1 + 0x1d) >> 0x10 & 1) != 0) {
    Character::EvaluatePackage(param_1,1,(byte)(*(uint *)(param_1 + 0x1d) >> 0x11) & 1);
  }
  cVar6 = (**(code **)(*param_1 + 0x4c8))(param_1,0);
  if (((cVar6 != '\0') && ((*(uint *)(param_1 + 0x19) & 0x1e00000) != 0xa00000)) ||
     (((*(uint *)(param_1 + 0x1d) >> 0xb & 1) != 0 ||
      ((*(char *)(_gProcessLists + 0x1e4) == '\0' ||
       ((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0xe00000)))))) {
    cVar5 = (**(code **)(*param_1 + 0x4c8))(param_1,0);
    if (cVar5 != '\0') {
      if ((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0x400000) {
        ActorProcess::ComputeLastTimeProcessed(param_1[0x1f]);
        *(float *)((longlong)param_1 + 0x10c) = *(float *)((longlong)param_1 + 0x10c) - fVar17;
      }
      else {
        if ((((*(uint *)((longlong)param_1 + 0x204) >> 5 & 1) == 0) &&
            ((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0xe00000)) &&
           (fVar17 = (float)FUN_1406d6ae0(param_1[0x1f]), 0.0 < fVar17)) {
          FUN_1406d6ac0(param_1[0x1f]);
          fVar17 = (float)FUN_1406d6ae0(param_1[0x1f]);
          if ((fVar17 <= 0.0) &&
             ((**(code **)(*param_1 + 0x728))(param_1),
             (*(uint *)(param_1 + 0x19) & 0x1e00000) == 0xe00000)) {
            Actor::Combat_unk1(param_1,0);
            cVar5 = FUN_1401bccd0(_gDataHandler);
            if ((cVar5 == '\0') &&
               (fVar17 = (float)Actor::unk_GetActorValue(param_1,2,0x18), fVar17 < 0.0)) {
              Actor::RestoreActorValue(param_1,0x18,1.0 - fVar17);
            }
            *(uint *)((longlong)param_1 + 0x204) = *(uint *)((longlong)param_1 + 0x204) & 0xffffffbf
            ;
          }
        }
        FUN_1406d3c10(param_1[0x1f],param_1);
      }
      if (((*(uint *)((longlong)param_1 + 0x204) >> 0x12 & 1) == 0) &&
         ((*(uint *)((longlong)param_1 + 0x204) >> 0x13 & 1) == 0)) {
        if ((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0xe00000) {
          Actor::Combat_unk1(param_1,0); // 140667c50
          if ((param_1[0x1f] == 0) || (cVar5 = ActorProcess::sub(), cVar5 == '\0')) {
            *(int *)(param_1 + 0x21) = gNullRefHandleId;
            FUN_140655640(gBSTaskPool,param_1,0,0,1,0);
          }
        }
        else {
          cVar5 = TESForm::sub(param_1);
          if ((cVar5 != '\0') && (cVar5 = TES::sub(_gTES,param_1[0xc],0), cVar5 == '\0')) {
            uVar10 = FUN_140633530(_Calendar_Singleton);
            cVar5 = Character::sub(param_1,uVar10,0);
            if (cVar5 != '\0') {
              FUN_14076e5c0(_gProcessLists,param_1);
            }
          }
        }
      }
    }
    goto LAB_140667ce3;
  }
  Actor::GetActorMover(param_1);
  if (DAT_142013680 != '\0') {
    FUN_1407106a0(param_1[0x1f]);
  }
  cVar6 = FUN_1406d5870(param_1[0x1f]);
  cVar7 = FUN_1406334b0(_Calendar_Singleton);
  plVar1 = param_1 + 0xe;
  if (cVar7 != cVar6) {
    FUN_14015e750(plVar1);
  }
  cVar6 = FUN_1406d8930(_gPlayerCharacter[0x1f]);
  if (cVar6 != '\0') {
    plVar13 = (longlong *)FUN_14015f860(plVar1);
    for (; plVar13 != (longlong *)0x0; plVar13 = (longlong *)plVar13[1]) {
      if (*plVar13 == 0) break;
      lVar11 = *(longlong *)(*plVar13 + 0x60);
      if (lVar11 != 0) {
        TESFaction::sub(lVar11,0);
      }
    }
    uVar14 = *(uint *)((longlong)param_1 + 0x204);
    if ((uVar14 >> 0xb & 1) != 0) {
      Character::sub(_gPlayerCharacter,1);
      uVar14 = *(uint *)((longlong)param_1 + 0x204);
    }
    *(uint *)((longlong)param_1 + 0x204) = uVar14 & 0xfffff7ff;
    lVar11 = Character::GetCrimeFaction(param_1);
    if (lVar11 != 0) {
      TESFaction::sub(lVar11);
    }
    BSExtraDataList::sub(plVar1,param_1);
  }
  if (((*(uint *)(param_1 + 0x19) & 0xe000000) == 0) &&
     (((*(char *)(_gProcessLists + 0xc) != '\0' ||
       ((*(longlong *)(param_1[0x1f] + 0x20) != 0 && (cVar6 = TESPackage::sub(), cVar6 != '\0'))))
      && (cVar6 = FUN_1406e25d0(param_1[0x1f]), cVar6 == '\0')))) {
    if ((*(longlong *)(param_1[0x1f] + 0x20) == 0) ||
       (cVar5 = *(char *)(*(longlong *)(param_1[0x1f] + 0x20) + 0x24), cVar5 != '\x1b')) {
      cVar6 = bhkRigidBody::sub(param_1);
      if (cVar6 != '\0') {
        lVar11 = GetDefaultObjectManager();
        if (*(char *)(lVar11 + 0xc2b) != '\0') {
          uVar15 = *(undefined8 *)(lVar11 + 0x4f8);
        }
        cVar6 = (**(code **)(*param_1 + 0x240))(param_1,uVar15);
        if (((cVar6 != '\0') ||
            (((param_1[0x3f] != 0 && ((*(uint *)(param_1[0x3f] + 0x164) >> 3 & 1) != 0)) ||
             ((*(uint *)((longlong)param_1 + 0x204) >> 3 & 1) != 0)))) &&
           (*(byte *)(param_1[0x1f] + 0x137) < 2)) {
          if (cVar5 != '+') {
            if ((*(uint *)((longlong)param_1 + 0x204) >> 2 & 1) == 0) {
              FUN_140699bb0(param_1);
            }
            else {
              FUN_14066d1a0();
            }
          }
          goto LAB_140667ad1;
        }
      }
      if ((param_2 <= 0.0) || (param_1 == _gPlayerCharacter)) {
        FUN_1406d3c10(param_1[0x1f],param_1);
      }
      else {
        FUN_1406d49b0(param_1[0x1f],param_1,param_2);
      }
    }
    else {
      cVar5 = FUN_1406efa60();
      if (cVar5 != '\0') {
        iVar9 = gNullRefHandleId;
        if ((*(uint *)(param_1 + 5) & 0x3ff) != 0) {
          FUN_140178ec0(apuStackX_8,param_1);
          iVar9 = (int)apuStackX_8[0];
        }
        if (*(int *)(_gMenuTopicManager + 0x6c) != iVar9) {
          Character::sub(param_1,0);
        }
      }
    }
  }
LAB_140667ad1:
  uVar8 = FUN_1406334b0(_Calendar_Singleton);
  ??_C@_0BM@JININMII@Xilleon?5225?5DAIO?91?5for?5X225@(plVar1,uVar8);
  FUN_1406d7c50(param_1[0x1f],param_1);
LAB_140667ce3:
  if (((param_1 != _gPlayerCharacter) && (param_1[8] != 0)) &&
     ((param_1[0x1f] == 0 || (*(char *)(param_1[0x1f] + 0x137) != '\0')))) {
    Character::sub(param_1);
  }
  return;
}

