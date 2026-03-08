
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1406badd0
longlong * UndefinedFunction_1406badd0(longlong *param_1)

{
  int *piVar1;
  int iVar2;
  longlong lVar3;
  char cVar4;
  undefined1 uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  longlong *plVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong lVar14;
  longlong *plVar15;
  float *pfVar16;
  float *pfVar17;
  longlong lVar18;
  char *pcVar19;
  int iVar20;
  longlong *plVar21;
  byte bVar22;
  undefined4 uVar23;
  bool bVar24;
  float fVar25;
  undefined8 extraout_XMM0_Qa;
  undefined1 auVar26 [16];
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  undefined1 auStackX_18 [8];
  int iStackX_20;
  ulonglong in_stack_fffffffffffff998;
  longlong *plStack_648;
  float fStack_638;
  float fStack_634;
  float fStack_630;
  float fStack_628;
  float fStack_624;
  longlong lStack_620;
  longlong lStack_618;
  float fStack_610;
  float fStack_60c;
  float fStack_608;
  longlong lStack_600;
  longlong lStack_5f8;
  undefined4 uStack_5f0;
  float fStack_5ec;
  float fStack_5e8;
  float fStack_5e4;
  undefined4 uStack_5e0;
  uint uStack_5dc;
  uint auStack_5d8 [2];
  float fStack_5d0;
  float fStack_5cc;
  float fStack_5c8;
  float fStack_5c4;
  float fStack_5c0;
  float fStack_5bc;
  undefined4 uStack_5b8;
  undefined4 uStack_5b4;
  undefined4 uStack_5b0;
  float fStack_5a8;
  float fStack_5a4;
  float fStack_5a0;
  float fStack_598;
  float fStack_594;
  float fStack_590;
  ulonglong uStack_588;
  longlong *plStack_580;
  longlong lStack_578;
  longlong lStack_570;
  undefined4 uStack_568;
  undefined4 uStack_564;
  byte bStack_560;
  float fStack_558;
  float fStack_554;
  float fStack_550;
  float fStack_548;
  float fStack_544;
  float fStack_540;
  undefined4 uStack_53c;
  float fStack_538;
  float fStack_534;
  float fStack_530;
  float fStack_52c;
  float fStack_528;
  float fStack_524;
  float fStack_520;
  float fStack_51c;
  float fStack_518;
  undefined4 uStack_514;
  longlong *plStack_510;
  undefined1 auStack_508 [16];
  undefined8 uStack_4f8;
  undefined4 uStack_4f0;
  undefined4 uStack_4ec;
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  undefined8 uStack_4e0;
  undefined8 uStack_4d8;
  undefined8 uStack_4d0;
  undefined4 uStack_4c0;
  undefined8 uStack_4b8;
  undefined4 uStack_4b0;
  undefined8 uStack_4a8;
  undefined4 uStack_4a0;
  undefined4 uStack_49c;
  undefined4 uStack_498;
  undefined8 uStack_494;
  float fStack_48c;
  undefined4 uStack_488;
  uint uStack_484;
  byte bStack_480;
  uint uStack_47f;
  undefined2 uStack_47b;
  undefined1 uStack_479;
  undefined4 uStack_478;
  float fStack_468;
  float fStack_464;
  float fStack_460;
  float fStack_45c;
  float fStack_458;
  float fStack_454;
  undefined4 uStack_450;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined1 auStack_444 [4];
  undefined1 auStack_440 [4];
  float fStack_43c;
  float fStack_438;
  float fStack_434;
  undefined1 auStack_430 [4];
  float fStack_42c;
  float fStack_428;
  float fStack_424;
  undefined1 auStack_420 [24];
  undefined4 uStack_408;
  float fStack_3fc;
  longlong lStack_3f8;
  float *pfStack_3f0;
  undefined8 uStack_3e8;
  undefined8 uStack_3e0;
  undefined8 uStack_3d8;
  undefined2 uStack_3d0;
  undefined1 uStack_3ce;
  undefined8 uStack_3c8;
  undefined8 uStack_3c0;
  longlong lStack_3b8;
  undefined4 uStack_3b0;
  longlong lStack_3a8;
  undefined1 auStack_398 [48];
  longlong lStack_368;
  undefined4 uStack_348;
  uint uStack_318;
  undefined *puStack_308;
  undefined1 uStack_300;
  undefined1 *puStack_2f8;
  int iStack_2f0;
  undefined4 uStack_2ec;
  undefined1 auStack_2e8 [680];
  undefined1 auVar27 [16];
  undefined4 uVar28;

  uStack_3c0 = 0xfffffffffffffffe;
  plVar15 = (longlong *)0x0;
  plVar9 = plVar15;
  if (param_1[0xc] != 0) {
    plVar9 = (longlong *)TESObjectCELL::GetHavokWorld();
  }
  lVar10 = func_0x0001403f8000(0,1);
  if (param_1[0x1f] == 0) {
    plVar11 = (longlong *)0x14313fcb0;
    plVar21 = plVar15;
  }
  else {
    plVar11 = (longlong *)ActorProcess::sub();
    plVar21 = (longlong *)param_1[0x1f];
  }
  if (*plVar11 == 0) {
    bVar22 = 0;
  }
  else {
    bVar22 = (byte)(*(uint *)(*plVar11 + 0x28) >> 3) & 1;
  }
  uVar12 = ActorProcess::GetCurrentlyEquippedWeapon(plVar21,bVar22);
  FUN_1407dab30(auStack_398);
  in_stack_fffffffffffff998 = in_stack_fffffffffffff998 & 0xffffffffffffff00;
  func_0x0001407daff0(auStack_398,param_1,0,uVar12,in_stack_fffffffffffff998);
  uVar23 = (undefined4)(in_stack_fffffffffffff998 >> 0x20);
  lVar13 = lStack_368;
  if (lStack_368 == 0) {
    if ((uStack_318 >> 0xe & 1) != 0) {
      lVar13 = ActorProcess::GetEquippedInLeftHand(param_1[0x1f]);
      if (lVar13 == 0) {
        lVar13 = ActorProcess::GetEquippedInRightHand(param_1[0x1f]);
      }
      if (lVar13 != 0) goto LAB_1406baf39;
    }
    lVar13 = _DAT_143137658;
  }
LAB_1406baf39:
  fVar33 = (float)_DAT_142006738;
  if (((lStack_368 != 0) && (fVar33 = _DAT_142006768, *(char *)(lStack_368 + 0x19d) != '\0')) &&
     (fVar33 = _DAT_142006750, (byte)(*(char *)(lStack_368 + 0x19d) - 5U) < 2)) {
    fVar33 = _DAT_142006780;
  }
  if ((plVar9 == (longlong *)0x0) || (plVar15 = (longlong *)0x0, lVar10 == 0)) goto LAB_1406bc025;
  (**(code **)(*param_1 + 0x610))(param_1,auStack_420,&fStack_5a8,0);
  cVar4 = func_0x000140280270(param_1);
  if ((cVar4 == '\0') || (param_1 != gPlayerCharacter3)) {
LAB_1406bb029:
    lVar14 = Actor::sub(param_1,auStack_430);
    uVar6 = (uint)*(ushort *)(lVar14 + 2);
  }
  else {
    lVar14 = func_0x00014014ef60();
    uVar12 = (**(code **)(*param_1 + 0x380))(param_1);
    lVar14 = NiAVObject::LookupBoneNodeByName(uVar12,lVar14 + 0x228,1);
    if ((((lVar14 == 0) || (*(longlong **)(lVar14 + 0x40) == (longlong *)0x0)) ||
        (lVar14 = (**(code **)(**(longlong **)(lVar14 + 0x40) + 0x90))(), lVar14 == 0)) ||
       (*(longlong *)(lVar14 + 0x20) == 0)) goto LAB_1406bb029;
    lVar14 = *(longlong *)(*(longlong *)(lVar14 + 0x20) + 0x10);
    uVar6 = 0;
    if ((lVar14 != 0) && (lVar14 != -0x20)) {
      uVar6 = *(uint *)(lVar14 + 0x4c) >> 0x10;
    }
    if (uVar6 == 0) goto LAB_1406bb029;
  }
  if (*(uint *)(lVar10 + 0x22c) != uVar6) {
    func_0x0001403f8810(lVar10);
  }
  cVar4 = func_0x0001403f8600(lVar10,plVar9,auStack_420,&fStack_5a8,CONCAT44(uVar23,fVar33));
  if (cVar4 == '\0') goto LAB_1406bc025;
  lVar14 = ??_C@_07EEPKHIGP@rex?4xb?5@(*(undefined8 *)(*(longlong *)(lVar10 + 0x10) + 0x30));
  plStack_648 = (longlong *)0x0;
  if ((lVar14 != 0) && (plVar15 = (longlong *)NiNode::sub(lVar14), plVar15 != (longlong *)0x0)) {
    LOCK();
    *(int *)(plVar15 + 5) = (int)plVar15[5] + 1;
    UNLOCK();
    plStack_648 = plVar15;
  }
  lStack_618 = *(longlong *)(*(longlong *)(lVar10 + 0x10) + 0x30);
  if (*(char *)(lStack_618 + 0x28) == '\x01') {
    lStack_618 = *(char *)(lStack_618 + 0x20) + lStack_618;
  }
  else {
    lStack_618 = 0;
  }
  if (plStack_648 == (longlong *)0x0) {
    plStack_580 = (longlong *)0x0;
LAB_1406bb0f2:
    uStack_5e0 = uStack_348;
    uStack_5dc = Character::sub(param_1);
    fVar25 = DAT_143272ca0;
    fVar30 = DAT_143272c9c;
    fVar33 = gNiPoint3_Zero;
    if (lStack_618 != 0) {
      lStack_600 = *(longlong *)(lStack_618 + 0x18);
      fStack_624 = DAT_143272c9c;
      fStack_628 = DAT_143272ca0;
      lVar14 = (**(code **)(*param_1 + 0x378))(param_1,0);
      if ((lVar14 != 0) && (param_1[0x1f] != 0)) {
        pfVar16 = (float *)func_0x0001406e3b40(param_1[0x1f],bVar22);
        pfVar17 = (float *)func_0x0001406b7520(param_1,bVar22);
        fVar29 = pfVar17[2] - pfVar16[2];
        fVar30 = pfVar17[1] - pfVar16[1];
        fVar33 = *pfVar17 - *pfVar16;
        fVar25 = SQRT(fVar30 * fVar30 + fVar33 * fVar33 + fVar29 * fVar29);
        if (fVar25 <= 1e-06) {
          fVar33 = 0.0;
          fVar30 = 0.0;
          fVar25 = 0.0;
          fStack_628 = fVar25;
          fStack_624 = fVar30;
        }
        else {
          fVar25 = 1.0 / fVar25;
          fVar33 = fVar33 * fVar25;
          fVar30 = fVar25 * fVar30;
          fVar25 = fVar25 * fVar29;
          fStack_628 = fVar25;
          fStack_624 = fVar30;
        }
      }
      pfVar16 = *(float **)(lVar10 + 0x10);
      fStack_42c = *pfVar16;
      fStack_638 = fStack_42c * 69.99125;
      fStack_428 = pfVar16[1];
      fStack_634 = fStack_428 * 69.99125;
      fStack_424 = pfVar16[2];
      fStack_630 = fStack_424 * 69.99125;
      fVar29 = 0.0;
      bVar24 = lVar13 != _DAT_143137658;
      if (bVar24) {
        fVar29 = (float)func_0x0001401ee0f0(lVar13);
        pfVar16 = *(float **)(lVar10 + 0x10);
      }
      fVar32 = pfVar16[0xe];
      bVar22 = 0;
      iStackX_20 = 0;
      lVar14 = *(longlong *)(lStack_600 + 0x10);
      if ((lVar14 != 0) && (lVar14 != -0x20)) {
        bVar22 = (byte)*(undefined4 *)(lVar14 + 0x4c);
      }
      if ((bVar22 & 0x7f) == 0x11) {
        iStackX_20 = TES::sub(_gTES,&fStack_638);
      }
      else if (((((lVar14 != 0) && ((longlong *)(lVar14 + 0x20) != (longlong *)0x0)) &&
                (lVar14 = *(longlong *)(lVar14 + 0x20), lVar14 != 0)) &&
               ((plVar15 = *(longlong **)(lVar14 + 0x10), plVar15 != (longlong *)0x0 &&
                (iStackX_20 = (int)plVar15[4], fVar32 != -NAN)))) &&
              (plVar15 = (longlong *)(**(code **)(*plVar15 + 0x1a0))(), plVar15 != (longlong *)0x0))
      {
        iStackX_20 = (**(code **)(*plVar15 + 0x1b0))(plVar15,fVar32);
      }
      fVar32 = _DAT_142003288;
      if (fVar29 + 3.0 <= _DAT_142003288) {
        fVar32 = fVar29 + 3.0;
      }
      auVar26._0_4_ = fVar25 * _DAT_142003270 * fVar32;
      fVar31 = fVar30 * _DAT_142003270 * fVar32;
      fVar32 = fVar33 * _DAT_142003270 * fVar32;
      fVar29 = (float)hkpMotion::sub(lStack_618 + 0x150);
      if (fVar29 < _DAT_1420032a0) {
        fVar29 = fVar29 / _DAT_1420032a0;
        fVar31 = fVar31 * fVar29;
        auVar26._0_4_ = auVar26._0_4_ * fVar29;
        fVar32 = fVar32 * fVar29;
      }
      lVar14 = *(longlong *)(lStack_600 + 0x10);
      uVar6 = 0;
      if ((lVar14 != 0) && (lVar14 != -0x20)) {
        uVar6 = *(uint *)(lVar14 + 0x4c);
      }
      if (((uVar6 & 0x7f) == 8) || ((uVar6 & 0x7f) - 0x20 < 2)) {
        fVar31 = fVar31 * _DAT_1420032b8;
        auVar26._0_4_ = auVar26._0_4_ * _DAT_1420032b8;
        fVar32 = _DAT_1420032b8 * fVar32;
      }
      fStack_548 = fVar32 * 0.0142875;
      fStack_544 = fVar31 * 0.0142875;
      fStack_540 = auVar26._0_4_ * 0.0142875;
      uStack_53c = 0;
      uStack_3b0 = 1;
      lVar14 = (**(code **)(*plVar9 + 0x140))(plVar9);
      lStack_3b8 = lVar14;
      if ((lVar14 != 0) && (*(longlong *)(lVar14 + 0x430) != 0)) {
        bhkWorld::HavokWorldEnterWrite();
      }
      uVar12 = *(undefined8 *)(lVar10 + 0x10);
      hkpRigidBody::activate(lStack_618);
      (**(code **)(*(longlong *)(lStack_618 + 0x150) + 0xa0))
                ((longlong *)(lStack_618 + 0x150),&fStack_548,uVar12);
      if ((lVar14 != 0) && (*(longlong *)(lVar14 + 0x430) != 0)) {
        bhkWorld::HavokWorldExitWrite();
      }
      if (plStack_648 != (longlong *)0x0) {
        if (lVar13 == 0) {
          uVar23 = 0;
        }
        else {
          uVar23 = *(undefined4 *)(lVar13 + 0x14);
        }
        uVar12 = GetOrCreateObjectRefHandle_Safe(plStack_648,auStack_444);
        lStack_5f8 = 0;
        LookupObjectByRefHandle(uVar12,&lStack_5f8);
        uVar12 = GetOrCreateObjectRefHandle_Safe(param_1,auStack_440);
        lStack_620 = 0;
        LookupObjectByRefHandle(uVar12,&lStack_620);
        lVar18 = func_0x0001401d5230();
        lVar14 = lStack_620;
        if (lStack_5f8 != 0) {
          LOCK();
          *(int *)(lStack_5f8 + 0x28) = *(int *)(lStack_5f8 + 0x28) + 1;
          UNLOCK();
        }
        lStack_578 = lStack_5f8;
        if (lStack_620 != 0) {
          LOCK();
          *(int *)(lStack_620 + 0x28) = *(int *)(lStack_620 + 0x28) + 1;
          UNLOCK();
        }
        lStack_570 = lStack_620;
        uStack_564 = 0;
        bStack_560 = bStack_560 & 0xf0;
        uStack_568 = uVar23;
        BSTEventSource_SendEvent(lVar18 + 0x5d8,&lStack_578);
        if (lStack_570 != 0) {
          LOCK();
          piVar1 = (int *)(lStack_570 + 0x28);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          lVar14 = lStack_620;
          if ((iVar2 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lStack_570 + 0x20) + 8))();
            lVar14 = lStack_620;
          }
        }
        if (lStack_578 != 0) {
          LOCK();
          piVar1 = (int *)(lStack_578 + 0x28);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          lVar14 = lStack_620;
          if ((iVar2 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lStack_578 + 0x20) + 8))();
            lVar14 = lStack_620;
          }
        }
        if (lVar14 != 0) {
          LOCK();
          piVar1 = (int *)(lVar14 + 0x28);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if ((iVar2 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lVar14 + 0x20) + 8))();
          }
        }
        if (lStack_5f8 != 0) {
          LOCK();
          piVar1 = (int *)(lStack_5f8 + 0x28);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if ((iVar2 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lStack_5f8 + 0x20) + 8))();
          }
        }
      }
      uVar12 = FUN_14031c090(iStackX_20);
      if ((uStack_318 >> 0xe & 1) == 0) {
        if (*(char *)(lVar13 + 0x1a) == ')') {
          lVar13 = *(longlong *)(lVar13 + 0x1f8);
          goto LAB_1406bb650;
        }
LAB_1406bb66d:
        lVar13 = 0;
LAB_1406bb672:
        uStack_588 = 0;
      }
      else {
        lVar13 = func_0x0001401cccc0(lVar13);
        if (lVar13 == 0) {
          lVar13 = *(longlong *)(_DAT_143137658 + 0x1f8);
        }
        else {
          lVar13 = *(longlong *)(lVar13 + 8);
        }
LAB_1406bb650:
        if (lVar13 == 0) goto LAB_1406bb66d;
        lVar13 = BGSImpactDataSet::sub(lVar13,uVar12);
        if (lVar13 == 0) goto LAB_1406bb672;
        uStack_588 = *(ulonglong *)(lVar13 + 0x60);
      }
      if (uStack_588 != 0) {
        auVar26 = *(undefined1 (*) [16])(*(longlong *)(lVar10 + 0x10) + 0x10);
        fStack_43c = auVar26._0_4_;
        fStack_434 = auVar26._4_4_;
        fStack_438 = auVar26._8_4_;
        fStack_610 = fStack_43c * 69.99125;
        fStack_60c = fStack_434 * 69.99125;
        fStack_608 = fStack_438 * 69.99125;
        FUN_1402b08d0(&fStack_610);
        fStack_5ec = fStack_638;
        fStack_5e8 = fStack_634;
        fStack_5e4 = fStack_630;
        uVar12 = func_0x0001401d1780();
        uStack_5f0 = (undefined4)uVar12;
        uVar12 = FUN_140e98620(uVar12,1);
        hkpAllCdPointCollector::sub(uVar12,0);
        bhkCollisionFilter::sub(_gbhkCollisionFilter,0x2b,8);
        bhkCollisionFilter::sub(_gbhkCollisionFilter,0x2b,0x20);
        bhkCollisionFilter::sub(_gbhkCollisionFilter,0x2b,0x21);
        puStack_2f8 = auStack_2e8;
        uStack_2ec = 0x80000010;
        iStack_2f0 = 0;
        uStack_300 = 0;
        puStack_308 = &UNK_14189f770;
        hkpAllCdPointCollector::sub(uVar12,plVar9,&fStack_638,&puStack_308);
        iVar8 = iStack_2f0;
        lVar10 = (longlong)iStack_2f0;
        func_0x000140e18780(&fStack_610,&fStack_5d0);
        uVar12 = func_0x0001401e5190();
        uVar6 = FUN_140cca350(uVar12,0xffffffff);
        uVar12 = FUN_14153b7a0((float)uVar6 * 1.4629181e-09);
        fVar29 = (float)uVar12;
        fVar32 = (float)((ulonglong)uVar12 >> 0x20);
        fVar31 = -fVar29;
        fStack_468 = fStack_5c4 * fVar29 + fStack_5d0 * fVar32;
        fStack_5c4 = fStack_5c4 * fVar32 + fVar31 * fStack_5d0;
        fStack_464 = fStack_5c0 * fVar29 + fStack_5cc * fVar32;
        fStack_5c0 = fStack_5c0 * fVar32 + fVar31 * fStack_5cc;
        fStack_460 = fStack_5bc * fVar29 + fStack_5c8 * fVar32;
        fStack_5bc = fStack_5bc * fVar32 + fVar31 * fStack_5c8;
        uStack_448 = uStack_5b0;
        uStack_450 = uStack_5b8;
        uStack_44c = uStack_5b4;
        fStack_5d0 = fStack_468;
        fStack_5cc = fStack_464;
        fStack_5c8 = fStack_460;
        fStack_45c = fStack_5c4;
        fStack_458 = fStack_5c0;
        fStack_454 = fStack_5bc;
        uVar7 = func_0x0001401d1780();
        fVar31 = fStack_5e4;
        fVar32 = fStack_5e8;
        fVar29 = fStack_5ec;
        uVar23 = uStack_5f0;
        iVar2 = iStackX_20;
        auVar26._0_4_ = (float)extraout_XMM0_Qa;
        iVar20 = (int)auVar26._0_4_;
        if ((iVar20 != -0x80000000) && ((float)iVar20 != auVar26._0_4_)) {
          uVar28 = (undefined4)((ulonglong)extraout_XMM0_Qa >> 0x20);
          auVar27._8_4_ = uVar28;
          auVar27._0_8_ = extraout_XMM0_Qa;
          auVar27._12_4_ = uVar28;
          auVar26._8_8_ = auVar27._8_8_;
          auVar26._4_4_ = auVar26._0_4_;
          uVar6 = movmskps(uVar7,auVar26);
          auVar26._0_4_ = (float)(int)(iVar20 - (uVar6 & 1));
        }
        lStack_600 = CONCAT44(lStack_600._4_4_,(int)auVar26._0_4_);
        if (0 < iVar8) {
          lVar14 = 0;
          do {
            iVar8 = 0;
            plVar9 = *(longlong **)(puStack_2f8 + lVar14 + 0x10);
            if (plVar9 != (longlong *)0x0) {
              iVar20 = *(int *)(puStack_2f8 + lVar14 + 0x18);
              if (iVar20 == -1) {
                if ((*plVar9 != 0) && (lVar18 = *(longlong *)(*plVar9 + 0x10), lVar18 != 0)) {
                  iVar8 = *(int *)(lVar18 + 0x20);
                  goto LAB_1406bba19;
                }
              }
              else if ((*plVar9 != 0) &&
                      (plVar15 = *(longlong **)(*plVar9 + 0x10), plVar15 != (longlong *)0x0)) {
                plVar15 = (longlong *)(**(code **)(*plVar15 + 0x1a0))();
                if (plVar15 != (longlong *)0x0) {
                  iVar8 = (**(code **)(*plVar15 + 0x1b0))(plVar15,iVar20);
                }
LAB_1406bba19:
                if (iVar8 == iVar2) {
                  uVar6 = *(uint *)((longlong)plVar9 + 0x2c) >> 0x10;
                  if (uVar6 == 1) {
                    plVar15 = (longlong *)TES::sub(_gTES,&fStack_638);
                    if ((plVar15 != (longlong *)0x0) &&
                       (plVar9 = (longlong *)plVar15[6], plVar9 != (longlong *)0x0))
                    goto LAB_1406bba59;
                  }
                  else {
                    plVar9 = (longlong *)GetNiObjectFromHavokCollidable(plVar9);
LAB_1406bba59:
                    plVar15 = plVar9;
                  }
                  lVar18 = NiNode::sub(plVar15);
                  if (lVar18 != 0) {
                    LOCK();
                    *(int *)(lVar18 + 0x28) = *(int *)(lVar18 + 0x28) + 1;
                    UNLOCK();
                  }
                  lStack_3a8 = lVar18;
                  if ((uVar6 == 1) ||
                     ((lVar18 != 0 && (cVar4 = func_0x0001401fac40(lVar18), cVar4 != '\0')))) {
                    fStack_558 = fStack_638;
                    fStack_554 = fStack_634;
                    fStack_550 = fStack_630;
                    uVar12 = TES::sub(_gTES,&fStack_558);
                    plStack_510 = (longlong *)0x0;
                    fStack_520 = gNiPoint3_Zero;
                    fStack_51c = DAT_143272c9c;
                    fStack_518 = DAT_143272ca0;
                    uStack_514 = gNullRefHandleId;
                    uStack_4f0 = 0xffffffff;
                    uStack_4b8 = 0;
                    uStack_4a8 = 0;
                    uStack_498 = 0x41800000;
                    uStack_408 = 0x3f800000;
                    uStack_47b = 0;
                    uStack_488 = 0;
                    uStack_479 = 0;
                    uStack_478 = 0;
                    fStack_538 = fVar29;
                    fStack_534 = fVar32;
                    fStack_530 = fVar31;
                    fStack_52c = fStack_610;
                    fStack_528 = fStack_60c;
                    fStack_524 = fStack_608;
                    uStack_4ec = uVar23;
                    uStack_4e8 = uVar23;
                    uStack_4e4 = *(undefined4 *)(lVar13 + 0x98);
                    if (plVar15 != (longlong *)0x0) {
                      LOCK();
                      *(int *)(plVar15 + 1) = (int)plVar15[1] + 1;
                      UNLOCK();
                      plStack_510 = plVar15;
                    }
                    auStack_508._8_8_ = 0;
                    auStack_508._0_8_ = uStack_588;
                    auStack_508 = auStack_508 << 0x40;
                    uStack_4f8 = *(undefined8 *)(lVar13 + 0x68);
                    uStack_4e0 = CONCAT44(fStack_5cc,fStack_5d0);
                    uStack_4d8 = CONCAT44(fStack_5c4,fStack_5c8);
                    uStack_4d0 = CONCAT44(fStack_5bc,fStack_5c0);
                    uStack_4c0 = uStack_5b0;
                    bVar22 = *(byte *)(lVar13 + 0xa5);
                    uVar5 = (undefined1)lStack_600;
                    if ((bVar22 & 8) != 0) {
                      uVar5 = 0xff;
                    }
                    uStack_484 = CONCAT31(0x100,uVar5);
                    bStack_480 = bVar22 >> 2 & 1;
                    uStack_484 = CONCAT13(bVar22,(undefined3)uStack_484) & 0x1ffffff;
                    uStack_4b0 = *(undefined4 *)(lVar13 + 0xa0);
                    uStack_47f = (uint)(CONCAT11(*(undefined1 *)(lVar13 + 0xa4),bVar22 >> 1) &
                                       0xff01);
                    uStack_4a0 = *(undefined4 *)(lVar13 + 0x9c);
                    uStack_49c = *(undefined4 *)(lVar13 + 0x50);
                    uVar6 = *(uint *)(lVar13 + 0xa8);
                    fStack_48c = (float)(uVar6 >> 0x10 & 0xff) * 0.003921569;
                    uStack_494 = CONCAT44((float)(uVar6 >> 8 & 0xff) * 0.003921569,
                                          (float)(uVar6 & 0xff) * 0.003921569);
                    fStack_3fc = fStack_48c;
                    TESObjectCELL::sub(uVar12,&fStack_538,0);
                    if (plStack_510 != (longlong *)0x0) {
                      LOCK();
                      plVar9 = plStack_510 + 1;
                      lVar3 = *plVar9;
                      *(int *)plVar9 = (int)*plVar9 + -1;
                      UNLOCK();
                      if ((int)lVar3 == 1) {
                        (**(code **)(*plStack_510 + 8))();
                      }
                    }
                    if (lVar18 != 0) {
                      LOCK();
                      piVar1 = (int *)(lVar18 + 0x28);
                      iVar8 = *piVar1;
                      *piVar1 = *piVar1 + -1;
                      UNLOCK();
                      if ((iVar8 - 1U & 0x3ff) == 0) {
                        (**(code **)(*(longlong *)(lVar18 + 0x20) + 8))();
                      }
                    }
                  }
                  else if (lVar18 != 0) {
                    LOCK();
                    piVar1 = (int *)(lVar18 + 0x28);
                    iVar8 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if ((iVar8 - 1U & 0x3ff) == 0) {
                      (**(code **)(*(longlong *)(lVar18 + 0x20) + 8))();
                    }
                  }
                }
              }
            }
            lVar14 = lVar14 + 0x20;
            lVar10 = lVar10 + -1;
            fVar25 = fStack_628;
            fVar30 = fStack_624;
          } while (lVar10 != 0);
        }
        func_0x000140ed8500(&puStack_308);
      }
      uVar6 = uStack_5dc;
      if (((uStack_5dc & 0xe) == 0) && (bVar24)) {
        if (plStack_648 != (longlong *)0x0) {
          plVar9 = (longlong *)0x0;
          if (*(char *)((longlong)plStack_648 + 0x1a) == '>') {
            plVar9 = plStack_648;
          }
          if (plVar9 != (longlong *)0x0) {
            bVar24 = DAT_142013638 == '\0';
          }
        }
        if (!bVar24) goto LAB_1406bbf2a;
        if (lVar13 != 0) {
          lVar10 = (**(code **)(*(longlong *)(lVar13 + 0x20) + 0x20))(lVar13 + 0x20);
          if ((lVar10 != 0) &&
             (pcVar19 = (char *)(**(code **)(*(longlong *)(lVar13 + 0x20) + 0x20))(lVar13 + 0x20),
             *pcVar19 != '\0')) {
            fVar29 = fVar33 * fStack_5a8 + fVar30 * fStack_5a4 + fVar25 * fStack_5a0;
            fStack_598 = fVar33 - fStack_5a8 * fVar29;
            fStack_594 = fVar30 - fStack_5a4 * fVar29;
            fStack_590 = fVar25 - fStack_5a0 * fVar29;
            FUN_1402b08d0(&fStack_598);
            lVar10 = param_1[0xc];
            (**(code **)(*(longlong *)(lVar13 + 0x20) + 0x20))(lVar13 + 0x20);
            TESObjectCELL::sub(lVar10);
          }
          goto LAB_1406bbf2a;
        }
      }
      else {
LAB_1406bbf2a:
        if ((lVar13 != 0) && ((uVar6 & 9) == 0)) {
          pfStack_3f0 = &fStack_638;
          uStack_3e8 = 0;
          uStack_3e0 = 0;
          uStack_3d8 = 0;
          uStack_3d0 = 0x101;
          uStack_3ce = 0;
          uStack_3c8 = 0;
          lStack_3f8 = lVar13;
          func_0x00014062fb00(_gBGSImpactManager,&lStack_3f8,auStackX_18);
        }
      }
      if (plStack_648 != (longlong *)0x0) {
        auStack_5d8[0] = (uint)*(byte *)(lStack_618 + 0x160);
        cVar4 = FUN_140e94a00(auStack_5d8);
        if (cVar4 != '\0') {
          lVar10 = *plStack_648;
          uVar12 = (**(code **)(*param_1 + 0x288))(param_1);
          (**(code **)(lVar10 + 0x280))(plStack_648,uVar12);
        }
        (**(code **)(*plStack_648 + 0x210))(plStack_648);
        if (((*(uint *)(plStack_648 + 2) >> 0x17 & 1) != 0) && (param_1 == _gPlayerCharacter)) {
          PlayerCharacter::sub(_gPlayerCharacter,9,plStack_648);
        }
      }
    }
  }
  else {
    plStack_580 = (longlong *)0x0;
    if (*(char *)((longlong)plStack_648 + 0x1a) == '>') {
      plStack_580 = plStack_648;
    }
    if (plStack_580 == (longlong *)0x0) goto LAB_1406bb0f2;
  }
  plVar15 = plStack_580;
  if (plStack_648 != (longlong *)0x0) {
    LOCK();
    plVar9 = plStack_648 + 5;
    lVar10 = *plVar9;
    *(int *)plVar9 = (int)*plVar9 + -1;
    UNLOCK();
    if (((int)lVar10 - 1U & 0x3ff) == 0) {
      (**(code **)(plStack_648[4] + 8))();
      plVar15 = plStack_580;
    }
  }
LAB_1406bc025:
  FUN_1407dad30(auStack_398);
  return plVar15;
}

