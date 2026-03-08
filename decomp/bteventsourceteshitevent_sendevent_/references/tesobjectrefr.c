
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1406b7bc0
void TESObjectREFR::sub(float *param_1,float *param_2)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  longlong *plVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  char cVar9;
  undefined1 uVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  undefined4 *puVar14;
  longlong lVar15;
  undefined8 *puVar16;
  longlong lVar17;
  longlong *plVar18;
  longlong lVar19;
  float *pfVar20;
  undefined8 uVar21;
  float *pfVar22;
  uint uVar23;
  byte bVar24;
  longlong unaff_GS_OFFSET;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  undefined4 uVar29;
  float *in_stack_fffffffffffffbe8;
  float *in_stack_fffffffffffffbf0;
  float *pfStack_3f8;
  longlong *plStack_3f0;
  uint uStack_3e8;
  longlong lStack_3e0;
  float afStack_3d8 [2];
  float *pfStack_3d0;
  longlong lStack_3c8;
  longlong lStack_3c0;
  longlong lStack_3b8;
  float fStack_3b0;
  float fStack_3ac;
  float fStack_3a8;
  float fStack_3a0;
  undefined4 uStack_39c;
  float fStack_398;
  undefined4 uStack_394;
  float fStack_390;
  float fStack_38c;
  float fStack_388;
  undefined4 uStack_384;
  longlong lStack_380;
  longlong *plStack_378;
  longlong lStack_370;
  longlong lStack_368;
  undefined4 uStack_360;
  undefined4 uStack_35c;
  byte bStack_358;
  float fStack_350;
  float fStack_34c;
  float fStack_348;
  float fStack_344;
  float fStack_340;
  float fStack_33c;
  float fStack_338;
  float fStack_334;
  float fStack_330;
  float fStack_328;
  float fStack_324;
  float fStack_320;
  undefined4 uStack_318;
  undefined1 auStack_314 [4];
  undefined1 auStack_310 [4];
  undefined1 auStack_30c [4];
  float *pfStack_308;
  undefined8 uStack_300;
  undefined1 uStack_2f8;
  float *pfStack_2f0;
  undefined8 uStack_2e8;
  undefined1 uStack_2e0;
  undefined8 uStack_2d8;
  undefined1 auStack_2c8 [656];

  uStack_2d8 = 0xfffffffffffffffe;
  if (((uint)param_1[0x32] & 0xe000000) == 0xa000000) {
    return;
  }
  if (*(longlong *)(param_1 + 0x3e) == 0) {
    return;
  }
  Character::sub();
  cVar8 = IsTaskPoolRequired();
  if (cVar8 != '\0') {
    FUN_140655390(gBSTaskPool,param_1,param_2);
    return;
  }
  uVar23 = (uint)param_1[0x81] >> 0xe & 0xffffff01;
  lVar15 = *(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)TlsIndex * 8);
  uVar29 = *(undefined4 *)(lVar15 + 0x768);
  *(undefined4 *)(lVar15 + 0x768) = 0x74;
  uStack_3e8 = uVar23;
  uStack_318 = uVar29;
  if (*(longlong *)(param_1 + 0x3e) != 0) {
    FUN_140714e50(*(longlong *)(param_1 + 0x3e),param_2);
  }
  *(undefined4 *)(lVar15 + 0x768) = uVar29;
  fStack_3a0 = param_2[6];
  pfStack_3f8 = (float *)0x0;
  LookupObjectByRefHandle(&fStack_3a0,&pfStack_3f8);
  lVar15 = *(longlong *)(param_2 + 0xc);
  if (*(longlong *)(param_2 + 0xc) == 0) {
    lVar15 = _DAT_143137658;
  }
  uVar29 = *(undefined4 *)(lVar15 + 0x14);
  uVar13 = GetOrCreateObjectRefHandle_Safe(param_1,auStack_314);
  lStack_3b8 = 0;
  LookupObjectByRefHandle(uVar13,&lStack_3b8);
  pfVar22 = pfStack_3f8;
  uStack_39c = gNullRefHandleId;
  if (pfStack_3f8 != (float *)0x0) {
    puVar14 = (undefined4 *)GetOrCreateObjectRefHandle_Safe(pfStack_3f8,auStack_310);
    uStack_39c = *puVar14;
  }
  lStack_3c0 = 0;
  LookupObjectByRefHandle(&uStack_39c,&lStack_3c0);
  lVar15 = func_0x0001401d5230();
  if (lStack_3b8 != 0) {
    LOCK();
    *(int *)(lStack_3b8 + 0x28) = *(int *)(lStack_3b8 + 0x28) + 1;
    UNLOCK();
    pfVar22 = pfStack_3f8;
  }
  lStack_370 = lStack_3b8;
  if (lStack_3c0 != 0) {
    LOCK();
    *(int *)(lStack_3c0 + 0x28) = *(int *)(lStack_3c0 + 0x28) + 1;
    UNLOCK();
    pfVar22 = pfStack_3f8;
  }
  lStack_368 = lStack_3c0;
  uStack_35c = 0;
  fVar4 = param_2[0x20];
  bStack_358 = ((byte)((uint)fVar4 >> 0xb) & 1 | -(((uint)fVar4 & 3) != 0) & 4U |
               -(((uint)fVar4 & 0xc000) != 0) & 2U) * '\x02' | (byte)((uint)fVar4 >> 0x10) & 1 |
               bStack_358 & 0xf0;
  uStack_360 = uVar29;
  BSTEventSource_SendEvent(lVar15 + 0x5d8,&lStack_370);
  if (lStack_368 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_368 + 0x28);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    pfVar22 = pfStack_3f8;
    if ((iVar3 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_368 + 0x20) + 8))();
      pfVar22 = pfStack_3f8;
    }
  }
  if (lStack_370 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_370 + 0x28);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    pfVar22 = pfStack_3f8;
    if ((iVar3 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_370 + 0x20) + 8))();
      pfVar22 = pfStack_3f8;
    }
  }
  bVar7 = false;
  fVar4 = param_2[0x14];
  fVar27 = param_2[0x15];
  fVar28 = param_2[0x17];
  if ((((pfVar22 != (float *)0x0) && (pfVar22 == gPlayerCharacter3)) &&
      (cVar8 = (**(code **)(*(longlong *)param_1 + 0x4c8))(param_1,0), cVar8 == '\0')) &&
     (param_1 != gPlayerCharacter3)) {
    memset(auStack_2c8,0,500);
    uVar13 = _DAT_14200c2e8;
    fVar25 = param_2[0x20];
    if (((uint)fVar25 >> 3 & 1) != 0) {
      in_stack_fffffffffffffbe8 = (float *)TESObjectREFR::sub(param_1);
      f_snprintf(auStack_2c8,500,&UNK_14179dde0,uVar13,in_stack_fffffffffffffbe8);
      ShowHUDMessage(auStack_2c8,&UNK_14189f788,1);
      uStack_300 = *(undefined8 *)(param_2 + 0xc);
      uStack_2f8 = 0;
      pfStack_308 = pfVar22;
      uVar13 = FUN_1406beca0();
      FUN_1406be640(uVar13,&pfStack_308);
      fVar25 = param_2[0x20];
    }
    if (((uint)fVar25 >> 0xb & 1) != 0) {
      lVar15 = *(longlong *)(param_2 + 0xc);
      uVar29 = _DAT_142003b28;
      if ((lVar15 != 0) && ((*(char *)(lVar15 + 0x19d) - 7U & 0xfd) == 0)) {
        uVar29 = _DAT_142003b10;
      }
      (**(code **)(*(longlong *)_gPlayerCharacter + 0x7b8))
                (_gPlayerCharacter,0xf,uVar29,lVar15,
                 (ulonglong)in_stack_fffffffffffffbe8 & 0xffffffff00000000);
      in_stack_fffffffffffffbe8 = (float *)(double)param_2[0x1c];
      in_stack_fffffffffffffbf0 = _DAT_14200c2d0;
      f_snprintf(auStack_2c8,500,&UNK_14189f798,_DAT_14200c2b8,in_stack_fffffffffffffbe8,
                 _DAT_14200c2d0);
      ShowHUDMessage(auStack_2c8,&UNK_14189f788,1);
      uStack_2e8 = *(undefined8 *)(param_2 + 0xc);
      uStack_2e0 = 1;
      pfStack_2f0 = pfVar22;
      uVar13 = FUN_1406beca0();
      FUN_1406be640(uVar13,&pfStack_2f0);
    }
  }
  cVar8 = (**(code **)(*(longlong *)param_1 + 0x4c8))(param_1,0);
  fStack_398 = param_2[8];
  plStack_3f0 = (longlong *)0x0;
  LookupObjectByRefHandle(&fStack_398,&plStack_3f0);
  uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
  if ((0.0 < fVar4) || (0.0001 < ABS(param_2[0x16]))) {
    fVar25 = (float)(**(code **)(*(longlong *)(param_1 + 0x2e) + 8))(param_1 + 0x2e,0x18);
    cVar9 = Character::sub(param_1);
    if ((cVar9 == '\0') &&
       (((pfVar22 == (float *)0x0 || (((uint)pfVar22[0x81] >> 0xe & 1) == 0)) &&
        (cVar9 = PlayerCharacter::sub(param_1), cVar9 == '\0')))) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (cVar8 == '\0') {
      if (((((uint)param_2[0x20] >> 3 & 1) != 0) && (*(longlong *)(param_2 + 0xe) != 0)) &&
         ((((cVar9 = Character::sub(param_1,0), cVar9 == '\0' && (bVar6)) ||
           (((uint)param_2[0x20] >> 4 & 1) == 0)) &&
          ((DAT_142013638 == '\0' &&
           (lVar15 = (**(code **)(*(longlong *)param_1 + 0x2e0))(param_1,3), lVar15 != 0)))))) {
        ActorMagicCaster::sub(lVar15,*(undefined8 *)(param_2 + 0xe));
        uStack_394 = 0;
        in_stack_fffffffffffffbf0 =
             (float *)((ulonglong)in_stack_fffffffffffffbf0 & 0xffffffffffffff00);
        in_stack_fffffffffffffbe8 =
             (float *)((ulonglong)in_stack_fffffffffffffbe8 & 0xffffffffffffff00);
        MagicCaster::sub(lVar15);
        MagicTarget::sub(param_1 + 0x28,*(undefined8 *)(param_2 + 0xe));
      }
      if ((bVar6) && (pfVar22 != (float *)0x0)) {
        bVar24 = (byte)((uint)param_2[0x20] >> 0x11) & 1;
        if ((*(longlong *)(pfVar22 + 0x3e) != 0) &&
           ((puVar16 = (undefined8 *)
                       ActorProcess::GetCurrentlyEquippedWeapon
                                 (*(longlong *)(pfVar22 + 0x3e),bVar24),
            puVar16 != (undefined8 *)0x0 &&
            (lVar15 = ExtraContainerChanges__ItemEntry::GetEnchantment(puVar16), lVar15 != 0)))) {
          in_stack_fffffffffffffbe8 =
               (float *)(CONCAT44((int)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20),(uint)bVar24)
                        ^ 1);
          Character::sub(pfVar22,param_1,*puVar16,lVar15,in_stack_fffffffffffffbe8);
        }
      }
    }
    uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
    if (plStack_3f0 != (longlong *)0x0) {
      lVar15 = (**(code **)(*plStack_3f0 + 0x470))(plStack_3f0);
      uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
      if (lVar15 != 0) {
        lVar17 = PlayerCharacter::sub(param_1);
        uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
        lStack_380 = lVar17;
        if (lVar17 != 0) {
          plVar18 = (longlong *)Explosion::sub(lVar15,param_1);
          uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
          while (plVar18 != (longlong *)0x0) {
            uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
            plVar5 = (longlong *)plVar18[1];
            if ((plVar5 == (longlong *)0x0) && (*plVar18 == 0)) break;
            lVar15 = BGSBodyPartData::sub(lVar17,*(undefined4 *)*plVar18);
            if ((lVar15 != 0) && (cVar9 = *(char *)(lVar15 + 0x7f), lVar17 = lStack_380, -1 < cVar9)
               ) {
              bVar24 = *(byte *)(lVar15 + 0x7e);
              fVar26 = (float)(**(code **)(*(longlong *)(param_1 + 0x2e) + 0x18))
                                        (param_1 + 0x2e,0x18);
              afStack_3d8[0] = (fVar4 / (fVar26 * (float)bVar24 * 0.01)) * 100.0;
              lVar15 = _DAT_143137658;
              if (*(longlong *)(param_2 + 0xc) != 0) {
                lVar15 = *(longlong *)(param_2 + 0xc);
              }
              ApplyPerkEntryPoint(4,param_1,pfVar22,lVar15,afStack_3d8);
              in_stack_fffffffffffffbe8 = pfVar22;
              Character::sub(param_1,2,(int)cVar9,-afStack_3d8[0],pfVar22);
              lVar17 = lStack_380;
            }
            uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffbe8 >> 0x20);
            plVar18 = plVar5;
          }
        }
      }
    }
    lVar15 = (**(code **)(*(longlong *)param_1 + 0x380))(param_1);
    uVar23 = uStack_3e8;
    if (lVar15 != 0) {
      fStack_390 = param_2[8];
      lStack_3e0 = 0;
      LookupObjectByRefHandle(&fStack_390,&lStack_3e0);
      lVar15 = lStack_3e0;
      if (lStack_3e0 != 0) {
        lVar17 = 0;
        if (*(char *)(lStack_3e0 + 0x1a) == '>') {
          lVar17 = lStack_3e0;
        }
        if (lVar17 != 0) {
          BSExtraDataList::GetLeveledNPC(lStack_3e0 + 0x70);
        }
      }
      uVar23 = uStack_3e8;
      if ((char)uStack_3e8 == '\0') {
        if (cVar8 == '\0') {
          if (bVar6) {
            cVar8 = Character::sub(param_1,0);
            if ((((cVar8 == '\0') && (cVar8 = Character::sub(param_1,pfVar22), cVar8 != '\0')) &&
                (fVar26 = (float)Character::sub(param_1), 0.0 < fVar26)) &&
               (pfVar22 != (float *)0x0)) {
              cVar8 = PlayerCharacter::sub(param_1);
              if (cVar8 == '\0') {
                fStack_38c = param_2[7];
                lStack_3c8 = 0;
                LookupObjectByRefHandle(&fStack_38c,&lStack_3c8);
                lVar17 = lStack_3c8;
                if (lStack_3c8 != 0) {
                  fStack_388 = param_2[8];
                  plStack_378 = (longlong *)0x0;
                  LookupObjectByRefHandle(&fStack_388,&plStack_378);
                  plVar18 = plStack_378;
                  if ((plStack_378 == (longlong *)0x0) ||
                     (lVar19 = (**(code **)(*plStack_378 + 0x478))(plStack_378), lVar19 == 0)) {
                    uVar10 = 0;
                  }
                  else {
                    uVar10 = 1;
                  }
                  fStack_350 = *param_2;
                  fStack_34c = param_2[1];
                  fStack_348 = param_2[2];
                  fStack_344 = param_2[3];
                  fStack_340 = param_2[4];
                  fStack_33c = param_2[5];
                  in_stack_fffffffffffffbf0 = &fStack_350;
                  pfVar20 = &fStack_344;
                  Character::sub(lVar17,pfVar22,param_2[0x14],0x3f800000,pfVar20,
                                 in_stack_fffffffffffffbf0,uVar10,param_2);
                  uVar29 = (undefined4)((ulonglong)pfVar20 >> 0x20);
                  if (plVar18 != (longlong *)0x0) {
                    LOCK();
                    plVar5 = plVar18 + 5;
                    lVar19 = *plVar5;
                    *(int *)plVar5 = (int)*plVar5 + -1;
                    UNLOCK();
                    pfVar22 = pfStack_3f8;
                    lVar17 = lStack_3c8;
                    lVar15 = lStack_3e0;
                    if (((int)lVar19 - 1U & 0x3ff) == 0) {
                      (**(code **)(plVar18[4] + 8))();
                      pfVar22 = pfStack_3f8;
                      lVar17 = lStack_3c8;
                      lVar15 = lStack_3e0;
                    }
                  }
                }
                uVar23 = uStack_3e8;
                if (lVar17 != 0) {
                  LOCK();
                  piVar1 = (int *)(lVar17 + 0x28);
                  iVar3 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  pfVar22 = pfStack_3f8;
                  lVar15 = lStack_3e0;
                  if ((iVar3 - 1U & 0x3ff) == 0) {
                    (**(code **)(*(longlong *)(lVar17 + 0x20) + 8))();
                    pfVar22 = pfStack_3f8;
                    lVar15 = lStack_3e0;
                    uVar23 = uStack_3e8;
                  }
                }
              }
              else {
                FUN_140656c20(gBSTaskPool,param_2);
              }
            }
            goto LAB_1406b84fa;
          }
        }
        else {
LAB_1406b84fa:
          if (bVar6) goto LAB_1406b8623;
        }
        cVar8 = Character::sub(param_1);
        if (((cVar8 == '\0') && (cVar8 = Actor::unk_IsInDialogue(param_1), cVar8 == '\0')) &&
           (cVar8 = FUN_1406e26a0(*(longlong *)(param_1 + 0x3e)), fVar26 = _DAT_1420029a0,
           cVar8 == '\0')) {
          if (fVar4 / fVar25 <= _DAT_1420029b8) {
            uVar13 = func_0x0001401e5190();
            uVar11 = FUN_140cca350(uVar13,0xffffffff);
            if (fVar26 < (float)uVar11 * 2.3283064e-10) goto LAB_1406b8579;
          }
          bVar7 = true;
        }
LAB_1406b8579:
        cVar8 = Character::sub(param_1);
        if (cVar8 == '\0') {
          if (((uint)param_2[0x20] >> 0xf & 1) == 0) {
            if (0.0 < param_2[0x1a]) {
              if ((((param_1 != gPlayerCharacter3) || (DAT_142013a88 == '\0')) &&
                  (((uint)param_2[0x20] & 0x4001) == 0)) &&
                 ((*(longlong *)(param_2 + 0xc) == 0 ||
                  ((int)*(char *)(*(longlong *)(param_2 + 0xc) + 0x19d) + 1U < 8)))) {
                uVar13 = func_0x0001401e5190();
                uVar11 = FUN_140cca350(uVar13,0xffffffff);
                if (_DAT_142002ca0 <= uVar11 % 100) goto LAB_1406b8623;
              }
              Character::sub(param_1);
            }
          }
          else {
            Character::sub(param_1,1);
          }
        }
      }
LAB_1406b8623:
      if (lVar15 != 0) {
        LOCK();
        piVar1 = (int *)(lVar15 + 0x28);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        pfVar22 = pfStack_3f8;
        if ((iVar3 - 1U & 0x3ff) == 0) {
          (**(code **)(*(longlong *)(lVar15 + 0x20) + 8))();
          pfVar22 = pfStack_3f8;
        }
      }
    }
  }
  lVar15 = (**(code **)(*(longlong *)param_1 + 0x380))(param_1);
  if (lVar15 == 0) {
LAB_1406b8af0:
    if (pfVar22 != (float *)0x0) goto LAB_1406b8bbe;
  }
  else {
    if (fVar28 <= 0.0) {
      if ((char)uVar23 == '\0') {
        fVar28 = (float)Character::sub(param_1);
        if (((0.0 < fVar28) && ((*(uint *)(*(longlong *)(param_1 + 0x7e) + 0x108) >> 10 & 1) == 0))
           && ((plStack_3f0 == (longlong *)0x0 ||
               (lVar15 = (**(code **)(*plStack_3f0 + 0x478))(plStack_3f0), lVar15 == 0)))) {
          fVar28 = param_2[0x1e];
          if (fVar28 <= 0.0) {
            fVar28 = (float)FUN_140418660(param_1 + 0x2e,(int)fVar27);
          }
          if (pfVar22 == (float *)0x0) {
            fStack_3ac = param_2[1];
            fStack_3a8 = param_2[2];
            pfVar20 = param_2;
          }
          else {
            fStack_3ac = pfVar22[0x16];
            fStack_3a8 = pfVar22[0x17];
            pfVar20 = pfVar22 + 0x15;
          }
          fStack_3a8 = param_1[0x17] - fStack_3a8;
          fStack_3ac = param_1[0x16] - fStack_3ac;
          fStack_3b0 = param_1[0x15] - *pfVar20;
          fVar27 = _DAT_142003f00;
          if (fVar28 <= _DAT_142003f00) {
            fVar27 = fVar28;
          }
          FUN_1402b08d0(&fStack_3b0);
          fStack_330 = fStack_3a8 * fVar27;
          fStack_334 = fStack_3ac * fVar27;
          fStack_338 = fStack_3b0 * fVar27;
          lVar15 = Actor::unk_GetMoveController(param_1);
          if (lVar15 != 0) {
            bhkCharacterController::sub(lVar15,&fStack_338,_DAT_142003f18);
          }
        }
        uVar13 = _DAT_14319a088;
        if ((param_1 != gPlayerCharacter3) && ((SUB41(param_1[0x9f],0) & 7) == 7)) {
          uVar21 = TESObjectREFR::sub(param_1,auStack_30c);
          FUN_1407c7750(uVar13,uVar21,param_2);
        }
      }
      uVar11 = Character::sub(param_1);
      if ((pfVar22 != (float *)0x0) && (pfVar22 == gPlayerCharacter3)) {
        uVar11 = uVar11 & 0xfffffff7;
      }
      if ((((uint)param_2[0x20] & 0xc000) == 0) &&
         (((0.0 < fVar4 ||
           ((*(longlong *)(param_2 + 0xc) != 0 && (*(longlong *)(param_2 + 0xc) != _DAT_143137658)))
           ) && ((uVar11 & 0xe) == 0)))) {
        cVar8 = IsTaskPoolRequired();
        if (cVar8 == '\0') {
          Character::sub(param_1);
          if (pfVar22 != (float *)0x0) {
            Character::sub(pfVar22);
          }
        }
        else {
          FUN_140655470(gBSTaskPool,param_1,param_2);
        }
      }
      if ((param_1 == gPlayerCharacter3) ||
         ((param_2[6] == _gBarterMenuActorRefHandleId && (plStack_3f0 == (longlong *)0x0)))) {
        if ((pfVar22 == (float *)0x0) ||
           ((pfVar22 == gPlayerCharacter3 || (*(int *)(_VATS_MODE_GetSingleton + 0x20) != 0)))) {
          if ((*(int *)(_VATS_MODE_GetSingleton + 0x20) != 0) &&
             ((*(char *)(_VATS_MODE_GetSingleton + 0x78) != '\0' &&
              (*(int *)(_gMenuManager + 0x160) == 0)))) {
            *(undefined1 *)(_VATS_MODE_GetSingleton + 0x78) = 0;
          }
        }
        else {
          (**(code **)(*(longlong *)pfVar22 + 0x380))(pfVar22);
          uVar13 = FUN_1406be160();
          func_0x00014029e0c0(uVar13);
        }
        if (*(int *)(_gMenuManager + 0x160) == 0) {
          uVar13 = 0;
          goto LAB_1406b8a83;
        }
      }
    }
    else {
      PlayerCharacter::sub(param_1);
      uVar13 = CONCAT44(uVar29,0x23);
      FUN_1408022b0(_DAT_1431ab110,param_1,0,3,uVar13,
                    (ulonglong)in_stack_fffffffffffffbf0 & 0xffffffffffffff00,0);
      uVar29 = (undefined4)((ulonglong)uVar13 >> 0x20);
      if ((((plStack_3f0 == (longlong *)0x0) && (pfVar22 != (float *)0x0)) &&
          (((uint)param_2[0x20] >> 0xe & 1) == 0)) &&
         (cVar8 = (**(code **)(*(longlong *)param_1 + 0x4c8))(param_1,0), cVar8 == '\0')) {
        Character::sub(pfVar22,0);
      }
      fVar27 = (float)(**(code **)(*(longlong *)(param_1 + 0x2e) + 8))(param_1 + 0x2e,0x1a);
      if ((0.0 < fVar27) && (fVar27 = (float)FUN_1404184d0(param_2), 0.0 < fVar27)) {
        (**(code **)(*(longlong *)(param_1 + 0x2e) + 0x30))(param_1 + 0x2e,2,0x1a,-fVar27);
      }
      if (param_1 == _gPlayerCharacter) {
        if (*(int *)(_VATS_MODE_GetSingleton + 0x20) == 0) {
          uVar13 = FUN_1406be160();
          func_0x00014029e0c0(uVar13);
        }
        if (*(int *)(_gMenuManager + 0x160) == 0) {
          uVar13 = 1;
LAB_1406b8a83:
          FUN_140cd3e40(uVar13);
        }
      }
      else if (((param_2[6] == _gBarterMenuActorRefHandleId) && (plStack_3f0 == (longlong *)0x0)) &&
              (*(int *)(_gMenuManager + 0x160) == 0)) {
        uVar13 = 1;
        goto LAB_1406b8a83;
      }
    }
    if ((*(longlong *)(param_2 + 0x10) != 0) && (pfVar22 != (float *)0x0)) {
      Actor::DoCombatSpellApply(pfVar22,*(longlong *)(param_2 + 0x10),param_1);
    }
    if ((char)uVar23 != '\0') goto LAB_1406b8af0;
    if (pfVar22 != (float *)0x0) {
      if ((*(longlong *)(param_2 + 10) != 0) &&
         (0.0 < *(float *)(*(longlong *)(param_2 + 10) + 0x40))) {
        fStack_328 = pfVar22[0x15];
        fStack_324 = pfVar22[0x16];
        fStack_320 = pfVar22[0x17];
        FUN_140710c80(*(longlong *)(param_1 + 0x3e),param_1,&fStack_328);
      }
      goto LAB_1406b8af0;
    }
  }
  if (((plStack_3f0 != (longlong *)0x0) &&
      (puVar14 = (undefined4 *)(**(code **)(*plStack_3f0 + 0x288))(plStack_3f0),
      puVar14 != (undefined4 *)0x0)) && (cVar8 = FUN_14043aa20(puVar14), cVar8 != '\0')) {
    uStack_384 = *puVar14;
    pfStack_3d0 = (float *)0x0;
    LookupObjectByRefHandle(&uStack_384,&pfStack_3d0);
    pfVar20 = pfVar22;
    if (pfVar22 != pfStack_3d0) {
      if (pfStack_3d0 != (float *)0x0) {
        LOCK();
        pfStack_3d0[10] = (float)((int)pfStack_3d0[10] + 1);
        UNLOCK();
      }
      pfStack_3f8 = pfStack_3d0;
      pfVar20 = pfStack_3d0;
      if (pfVar22 != (float *)0x0) {
        LOCK();
        pfVar2 = pfVar22 + 10;
        fVar27 = *pfVar2;
        *pfVar2 = (float)((int)*pfVar2 + -1);
        UNLOCK();
        if (((int)fVar27 - 1U & 0x3ff) == 0) {
          (**(code **)(*(longlong *)(pfVar22 + 8) + 8))();
          pfVar20 = pfStack_3f8;
        }
      }
    }
    pfVar22 = pfVar20;
    if (pfStack_3d0 != (float *)0x0) {
      LOCK();
      pfVar22 = pfStack_3d0 + 10;
      fVar27 = *pfVar22;
      *pfVar22 = (float)((int)*pfVar22 + -1);
      UNLOCK();
      pfVar22 = pfStack_3f8;
      if (((int)fVar27 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(pfStack_3d0 + 8) + 8))();
        pfVar22 = pfStack_3f8;
      }
    }
  }
LAB_1406b8bbe:
  lVar15 = *(longlong *)(param_1 + 0x58);
  pfVar20 = pfVar22;
  if (((pfVar22 != (float *)0x0) && (*(longlong *)(pfVar22 + 0x3e) != 0)) &&
     (cVar8 = FUN_140715230(), cVar8 != '\0')) {
    pfStack_3f8 = (float *)0x0;
    pfVar20 = (float *)0x0;
    if (pfVar22 != (float *)0x0) {
      LOCK();
      pfVar20 = pfVar22 + 10;
      fVar27 = *pfVar20;
      *pfVar20 = (float)((int)*pfVar20 + -1);
      UNLOCK();
      pfVar20 = pfStack_3f8;
      if (((int)fVar27 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(pfVar22 + 8) + 8))();
        pfVar20 = pfStack_3f8;
      }
    }
  }
  uVar12 = Character::sub(param_1);
  fUnk_Attacked(param_1,pfVar20,0,uVar12);
  cVar8 = Character::sub(param_1);
  if ((cVar8 != '\0') || (cVar8 = Actor::unk_IsInDialogue(param_1), cVar8 != '\0')) {
    bVar7 = false;
  }
  if ((lVar15 == 0) && (lVar15 = *(longlong *)(param_1 + 0x58), lVar15 != 0)) {
    FUN_1405590e0(lVar15,pfVar20,fVar4);
  }
  if (bVar7) {
    FUN_1408022b0(_DAT_1431ab110,param_1,pfVar20,3,CONCAT44(uVar29,0x1d),1,lVar15);
  }
  Character::sub(param_1);
  if (plStack_3f0 != (longlong *)0x0) {
    LOCK();
    plVar18 = plStack_3f0 + 5;
    lVar15 = *plVar18;
    *(int *)plVar18 = (int)*plVar18 + -1;
    UNLOCK();
    pfVar20 = pfStack_3f8;
    if (((int)lVar15 - 1U & 0x3ff) == 0) {
      (**(code **)(plStack_3f0[4] + 8))();
      pfVar20 = pfStack_3f8;
    }
  }
  if (lStack_3c0 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_3c0 + 0x28);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    pfVar20 = pfStack_3f8;
    if ((iVar3 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_3c0 + 0x20) + 8))();
      pfVar20 = pfStack_3f8;
    }
  }
  if (lStack_3b8 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_3b8 + 0x28);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    pfVar20 = pfStack_3f8;
    if ((iVar3 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_3b8 + 0x20) + 8))();
      pfVar20 = pfStack_3f8;
    }
  }
  if (pfVar20 != (float *)0x0) {
    LOCK();
    pfVar22 = pfVar20 + 10;
    fVar4 = *pfVar22;
    *pfVar22 = (float)((int)*pfVar22 + -1);
    UNLOCK();
    if (((int)fVar4 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(pfVar20 + 8) + 8))();
    }
  }
  return;
}

