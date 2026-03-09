
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 140680740
void Actor::Combat_unk1(longlong *param_1,uint param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  uint uVar12;
  uint uVar13;
  float fVar14;
  longlong lStackX_8;
  undefined1 auStackX_10 [8];
  longlong lStackX_18;
  undefined4 uStack_b0;
  undefined1 uStack_ac;
  undefined4 uStack_a8;
  undefined *apuStack_98 [5];
  undefined1 auStack_70 [8];
  undefined1 auStack_68 [40];
  undefined4 uStack_40;

  if (((DAT_142013e08 != '\0') && ((*(uint *)((longlong)param_1 + 0x204) >> 0x12 & 1) != 0)) &&
     (param_2 - 1 < 2)) {
    param_2 = 7;
  }
  if (((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0) && ((param_2 - 1 < 2 || (param_2 == 7)))) {
    Actor::StopMovement(param_1);
  }
  uVar10 = 0;
  if (param_2 == 2) {
    lVar7 = (**(code **)(*param_1 + 0x318))(param_1);
    if (lVar7 != 0) {
      BSFaceGenAnimationData::sub(lVar7,1);
    }
    lVar7 = BSExtraDataList::GetContainerChanges(param_1 + 0xe);
    if (lVar7 != 0) {
      func_0x00014022e610(lVar7,param_1);
    }
    uStack_b0 = 0xffffffff;
    uStack_ac = 0;
    uStack_a8 = 0;
    FUN_14015f500(param_1 + 0xe,&uStack_b0);
    FUN_140caf520(&uStack_b0);
    FUN_140cafc50(&uStack_b0);
    FUN_14015b950(param_1 + 0xe,&uStack_b0);
    uVar8 = TESObjectREFR::GetNiNode(param_1);
    uVar9 = BSAudioManager::GetSingleton();
    FUN_140cb2970(uVar9,uVar8,0,0);
    if (((param_1[0x1f] != 0) && (lVar7 = *(longlong *)(param_1[0x1f] + 0x20), lVar7 != 0)) &&
       (cVar5 = TESPackage::sub(lVar7), cVar5 != '\0')) {
      FUN_14048fec0(lVar7,0);
    }
  }
  else if (param_2 == 0) goto LAB_1406808b5;
  if (((param_1[0x1f] != 0) && (*(char *)(param_1[0x1f] + 0x137) == '\0')) &&
     (iVar6 = ActorProcess::GetFadeState(), iVar6 - 3U < 2)) {
    ActorProcess::FadeIn(param_1[0x1f],param_1,0);
  }
LAB_1406808b5:
  uVar13 = *(uint *)(param_1 + 0x19);
  if ((uVar13 >> 0x15 & 0xf) != param_2) {
    (**(code **)(*param_1 + 0x50))(param_1,0x400);
    uVar13 = *(uint *)(param_1 + 0x19);
  }
  uVar12 = uVar13 >> 0x15 & 0xf;
  uVar13 = (param_2 << 0x15 ^ uVar13) & 0x1e00000 ^ uVar13;
  *(uint *)(param_1 + 0x19) = uVar13;
  uVar13 = uVar13 >> 0x15 & 0xf;
  if (uVar12 == uVar13) {
    return;
  }
  if (((uVar12 != 2) || (uVar13 == 1)) && (uVar13 != 2)) {
    bVar2 = uVar12 - 7 < 2;
    bVar3 = uVar13 - 7 < 2;
    if (((uVar13 == 1) && (bVar2)) && (param_1[0x1f] != 0)) {
      FUN_1407153c0(param_1[0x1f],1);
    }
    if (bVar2 != bVar3) {
      if ((bVar2) && (param_1[0x1f] != 0)) {
        FUN_1406d6af0(param_1[0x1f],0x40000000);
      }
      lVar7 = GetDefaultObjectManager();
      if (*(char *)(((ulonglong)bVar3 ^ 1) + 0xbdd + lVar7) != '\0') {
        uVar10 = *(undefined8 *)(lVar7 + 0x288 + ((ulonglong)bVar3 ^ 1) * 8);
      }
      func_0x0001401ee360(apuStack_98,0,param_1,uVar10,0);
      func_0x00014023a6d0(auStack_70);
      uStack_40 = 0;
      apuStack_98[0] = &UNK_14178c478;
      TESActionData::Func5(apuStack_98);
      if (bVar3) {
        uVar10 = GetOrCreateObjectRefHandle_Safe(param_1,auStackX_10);
        lStackX_8 = 0;
        LookupObjectByRefHandle(uVar10,&lStackX_8);
        lVar11 = func_0x0001401d5230();
        lVar7 = lStackX_8;
        if (lStackX_8 != 0) {
          LOCK();
          *(int *)(lStackX_8 + 0x28) = *(int *)(lStackX_8 + 0x28) + 1;
          UNLOCK();
        }
        lStackX_18 = lStackX_8;
        FUN_1406ad570(lVar11 + 0x420,&lStackX_18);
        if (lStackX_18 != 0) {
          LOCK();
          piVar1 = (int *)(lStackX_18 + 0x28);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          lVar7 = lStackX_8;
          if ((iVar6 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lStackX_18 + 0x20) + 8))();
            lVar7 = lStackX_8;
          }
        }
        fVar4 = _DAT_141ffdfe0;
        if (uVar13 == 7) {
          fVar14 = (float)ActorValueOwner::sub
                                    (param_1 + 0x17,param_1[8],*(undefined8 *)(param_1[8] + 0x1c0));
          Character::sub(param_1,fVar14 / fVar4);
        }
        cVar5 = (**(code **)(*param_1 + 0x718))(param_1);
        if ((cVar5 != '\0') &&
           (((cVar5 = Character::sub(param_1,_gPlayerCharacter), cVar5 != '\0' ||
             (cVar5 = Character::sub(param_1,_gPlayerCharacter,0xff), cVar5 != '\0')) &&
            (param_1[0x1f] != 0)))) {
          FUN_1406d6af0(param_1[0x1f],_DAT_1420066c0);
        }
        if (lVar7 != 0) {
          LOCK();
          piVar1 = (int *)(lVar7 + 0x28);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if ((iVar6 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lVar7 + 0x20) + 8))();
          }
        }
      }
      if (param_1 == gPlayerCharacter3) {
        if (bVar3) {
          TESCamera::sub();
          ShowHUDMessage(_DAT_14200b8f8,0,1);
          FUN_140cd56e0(_gInputManager);
          FUN_140cd5650(_gInputManager,0x424,0,0);
        }
        else {
          PlayerCamera::sub(_gPlayerCamera,0);
          FUN_140cd5700(_gInputManager);
        }
      }
      apuStack_98[0] = &UNK_14178c440;
      BSFixedString::Release(auStack_68);
      BSFixedString::Release(auStack_70);
      func_0x0001401ee240(apuStack_98);
      return;
    }
    return;
  }
  if (param_1 == gPlayerCharacter3) {
    return;
  }
  lVar7 = (**(code **)(*param_1 + 0x380))(param_1);
  if (lVar7 == 0) {
    return;
  }
  cVar5 = IsTaskPoolRequired();
  if (cVar5 == '\0') {
    return;
  }
  FUN_1406563f0(gBSTaskPool,param_1);
  return;
}

