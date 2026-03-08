
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1407ecd80
void UndefinedFunction_1407ecd80
               (longlong *param_1,ulonglong param_2,float *param_3,float *param_4,undefined4 param_5
               ,char param_6)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  ulonglong uVar5;
  longlong lVar6;
  undefined4 *puVar7;
  longlong lVar8;
  undefined8 uVar9;
  char *pcVar10;
  ulonglong uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  longlong lStackX_8;
  ulonglong uStackX_10;
  ulonglong in_stack_fffffffffffffe38;
  float *pfVar15;
  undefined8 in_stack_fffffffffffffe40;
  undefined4 uVar16;
  undefined8 in_stack_fffffffffffffe48;
  undefined4 uVar17;
  ulonglong in_stack_fffffffffffffe50;
  float fStack_1a8;
  float fStack_1a4;
  float fStack_1a0;
  undefined4 uStack_198;
  longlong lStack_190;
  longlong lStack_188;
  float fStack_180;
  float fStack_17c;
  float fStack_178;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  longlong lStack_150;
  longlong lStack_148;
  longlong lStack_140;
  longlong lStack_138;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  byte bStack_128;
  longlong lStack_118;
  longlong lStack_110;
  float fStack_108;
  float fStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  bool bStack_cc;
  undefined2 uStack_cb;
  undefined1 auStack_c8 [4];
  undefined1 auStack_c4 [4];
  longlong lStack_c0;
  float *pfStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined2 uStack_98;
  undefined1 uStack_96;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined1 auStack_80 [72];

  uVar16 = (undefined4)((ulonglong)in_stack_fffffffffffffe40 >> 0x20);
  uVar17 = (undefined4)((ulonglong)in_stack_fffffffffffffe48 >> 0x20);
  uStack_88 = 0xfffffffffffffffe;
  uVar2 = *(uint *)((longlong)param_1 + 0x1d4);
  if ((uVar2 >> 0x14 & 1) != 0) {
    return;
  }
  *(uint *)((longlong)param_1 + 0x1d4) = uVar2 | 0x100000;
  uVar11 = 0;
  uStackX_10 = param_2;
  if (param_1[0x37] == 0) {
    uVar5 = uVar11;
    if (param_1[0x2e] != 0) {
      uVar5 = func_0x0001401461f0(param_1[0x2e],(byte)(uVar2 >> 0x1c) & 1);
    }
  }
  else {
    uVar5 = *(ulonglong *)(param_1[0x37] + 0x1f8);
  }
  lVar6 = FUN_14031c090(param_5);
  if ((uVar5 == 0) || (lVar6 == 0)) {
    lVar6 = 0;
  }
  else {
    lVar6 = BGSImpactDataSet::sub(uVar5,lVar6);
    if (lVar6 != 0) {
      puVar7 = (undefined4 *)(**(code **)(*param_1 + 0x288))(param_1);
      uStack_160 = gNullRefHandleId;
      if (puVar7 != (undefined4 *)0x0) {
        uStack_160 = *puVar7;
      }
      lStack_148 = 0;
      LookupObjectByRefHandle(&uStack_160,&lStack_148);
      lVar8 = lStack_148;
      if ((lStack_148 != 0) && (lStackX_8 = *(longlong *)(lStack_148 + 0xf8), lStackX_8 != 0)) {
        uVar3 = func_0x000140317890(lVar6);
        in_stack_fffffffffffffe38 = 0;
        FUN_1406df9b0(lStackX_8,lVar8,param_3,uVar3,0);
      }
      if (lVar8 != 0) {
        LOCK();
        piVar1 = (int *)(lVar8 + 0x28);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((iVar4 - 1U & 0x3ff) == 0) {
          (**(code **)(*(longlong *)(lVar8 + 0x20) + 8))();
        }
      }
    }
  }
  if (uStackX_10 != 0) {
    uVar5 = uVar11;
    if (*(char *)(uStackX_10 + 0x1a) == '>') {
      uVar5 = uStackX_10;
    }
    if ((uVar5 != 0) && (param_1[0x2c] == 0)) {
      return;
    }
  }
  lVar8 = GetWorldCamera();
  fVar14 = param_3[2] - *(float *)(lVar8 + 0xa8);
  fVar13 = param_3[1] - *(float *)(lVar8 + 0xa4);
  fVar12 = *param_3 - *(float *)(lVar8 + 0xa0);
  if (((int)param_1[0x25] == _gBarterMenuActorRefHandleId) ||
     (_gSecondsSinceLastFrame_WorldTime < _DAT_142013650)) {
    uVar5 = uVar11;
    if (_DAT_142013668 <= _gSecondsSinceLastFrame_WorldTime) {
      uVar5 = 4;
    }
  }
  else {
    uVar5 = 0xc;
  }
  if ((_gSceneComplexCounter != 0) ||
     (_DAT_142002c10 / (float)((int)(uVar5 >> 2) + 1) <
      SQRT(fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14))) {
    uVar5 = (ulonglong)((uint)uVar5 | 3);
  }
  if (uStackX_10 != 0) {
    uStack_198 = 0;
    lVar8 = param_1[0x37];
    if ((lVar8 != 0) || (lVar8 = param_1[0x2c], lVar8 != 0)) {
      uStack_198 = *(undefined4 *)(lVar8 + 0x14);
    }
    puVar7 = (undefined4 *)(**(code **)(*param_1 + 0x288))(param_1);
    uStack_15c = gNullRefHandleId;
    if (puVar7 != (undefined4 *)0x0) {
      uStack_15c = *puVar7;
    }
    lStack_150 = 0;
    LookupObjectByRefHandle(&uStack_15c,&lStack_150);
    uStack_158 = gNullRefHandleId;
    if (lStack_150 != 0) {
      puVar7 = (undefined4 *)GetOrCreateObjectRefHandle_Safe(lStack_150,auStack_c8);
      uStack_158 = *puVar7;
    }
    lStack_188 = 0;
    LookupObjectByRefHandle(&uStack_158,&lStack_188);
    uVar9 = GetOrCreateObjectRefHandle_Safe(uStackX_10,auStack_c4);
    lStack_190 = 0;
    LookupObjectByRefHandle(uVar9,&lStack_190);
    uStack_154 = *(undefined4 *)(param_1[8] + 0x14);
    lVar8 = func_0x0001401d5230();
    if (lStack_190 != 0) {
      LOCK();
      *(int *)(lStack_190 + 0x28) = *(int *)(lStack_190 + 0x28) + 1;
      UNLOCK();
    }
    lStack_140 = lStack_190;
    if (lStack_188 != 0) {
      LOCK();
      *(int *)(lStack_188 + 0x28) = *(int *)(lStack_188 + 0x28) + 1;
      UNLOCK();
    }
    lStack_138 = lStack_188;
    uStack_130 = uStack_198;
    uStack_12c = uStack_154;
    bStack_128 = bStack_128 & 0xf0;
    BSTEventSource_SendEvent(lVar8 + 0x5d8,&lStack_140);  // 1407ed0d7
    if (lStack_138 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_138 + 0x28);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar4 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_138 + 0x20) + 8))();
      }
    }
    if (lStack_140 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_140 + 0x28);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar4 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_140 + 0x20) + 8))();
      }
    }
    if (lStack_190 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_190 + 0x28);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar4 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_190 + 0x20) + 8))();
      }
    }
    if (lStack_188 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_188 + 0x28);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar4 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_188 + 0x20) + 8))();
      }
    }
    if (lStack_150 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_150 + 0x28);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar4 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_150 + 0x20) + 8))();
      }
    }
  }
  if (lVar6 == 0) {
    return;
  }
  if ((uVar5 & 10) == 0) {
    uVar17 = 0;
    in_stack_fffffffffffffe38 = in_stack_fffffffffffffe38 & 0xffffffffffffff00;
    lVar8 = lVar6;
    FlameProjectile::sub
              (param_1,param_3,param_4,param_5,in_stack_fffffffffffffe38,lVar6,0,
               in_stack_fffffffffffffe50 & 0xffffffffffffff00);
    uVar16 = (undefined4)((ulonglong)lVar8 >> 0x20);
  }
  uVar3 = (undefined4)(in_stack_fffffffffffffe38 >> 0x20);
  if ((((uVar5 & 8) != 0) ||
      (pcVar10 = (char *)(**(code **)(*(longlong *)(lVar6 + 0x20) + 0x20))(), pcVar10 == (char *)0x0
      )) || (*pcVar10 == '\0')) goto LAB_1407ed3e0;
  iVar4 = *(int *)(lVar6 + 0x4c);
  if (iVar4 == 0) {
LAB_1407ed32a:
    fStack_1a8 = *param_4;
    fStack_1a4 = param_4[1];
    fStack_1a0 = param_4[2];
LAB_1407ed34a:
    FUN_1402b08d0(&fStack_1a8);
  }
  else {
    if (iVar4 == 1) {
      fStack_1a8 = -*(float *)(param_1 + 0x1f);
      fStack_1a4 = -*(float *)((longlong)param_1 + 0xfc);
      fStack_1a0 = -*(float *)(param_1 + 0x20);
      goto LAB_1407ed34a;
    }
    if (iVar4 != 2) goto LAB_1407ed32a;
    fStack_170 = -*(float *)(param_1 + 0x1f);
    fStack_16c = -*(float *)((longlong)param_1 + 0xfc);
    fStack_168 = -*(float *)(param_1 + 0x20);
    FUN_1402b08d0(&fStack_170);
    fStack_180 = *param_4;
    fStack_17c = param_4[1];
    fStack_178 = param_4[2];
    FUN_1402b08d0(&fStack_180);
    fVar12 = fStack_17c * fStack_16c + fStack_180 * fStack_170 + fStack_178 * fStack_168;
    fVar12 = fVar12 + fVar12;
    fStack_1a8 = fStack_180 * fVar12 - fStack_170;
    fStack_1a4 = fStack_17c * fVar12 - fStack_16c;
    fStack_1a0 = fStack_178 * fVar12 - fStack_168;
  }
  if (param_6 == '\0') {
    pfVar15 = param_3;
    TESObjectCELL::sub(param_1[0xc],*(undefined4 *)(lVar6 + 0x48),pcVar10,&fStack_1a8,param_3,
                       CONCAT44(uVar16,0x3f800000),CONCAT44(uVar17,7),0);
    uVar3 = (undefined4)((ulonglong)pfVar15 >> 0x20);
  }
  else {
    FUN_140e18a70(&fStack_1a8,auStack_80);
    pfVar15 = param_3;
    TESObjectCELL::sub(param_1[0xc],*(undefined4 *)(lVar6 + 0x48),pcVar10,auStack_80,param_3,
                       CONCAT44(uVar16,0x3f800000),CONCAT44(uVar17,7),0);
    uVar3 = (undefined4)((ulonglong)pfVar15 >> 0x20);
  }
LAB_1407ed3e0:
  if ((uVar5 & 1) == 0) {
    uStack_b0 = 0;
    uStack_a8 = 0;
    uStack_a0 = 0;
    uStack_98 = 1;
    uStack_96 = 0;
    uStack_90 = 0;
    lStack_c0 = lVar6;
    pfStack_b8 = param_3;
    func_0x00014062fb00(_gBGSImpactManager,&lStack_c0,&lStackX_8);
  }
  lStack_118 = *(longlong *)(lVar6 + 0x80);
  if ((lStack_118 != 0) && (lStack_110 = param_1[0xc], lStack_110 != 0)) {
    uStack_f0 = gNiPoint3_Zero;
    uStack_ec = DAT_143272c9c;
    uStack_e8 = DAT_143272ca0;
    uStack_d8 = 0;
    uStack_d0 = 0;
    uStack_cb = 0;
    fStack_108 = *param_3;
    fStack_104 = param_3[1];
    fStack_100 = param_3[2];
    fStack_fc = *param_4;
    fStack_f8 = param_4[1];
    fStack_f4 = param_4[2];
    uStack_e0 = (**(code **)(*param_1 + 0x288))(param_1);
    if ((longlong *)param_1[0x2c] == (longlong *)0x0) {
      bStack_cc = true;
    }
    else {
      iVar4 = (**(code **)(*(longlong *)param_1[0x2c] + 0x2a8))();
      bStack_cc = iVar4 != 2;
      uVar11 = param_1[0x2c];
    }
    func_0x0001407d8280(&lStack_118,uVar11,param_1[0x2e],
                        *(uint *)((longlong)param_1 + 0x1d4) >> 0x1c & 0xffffff01,
                        CONCAT44(uVar3,(int)param_1[0x32]));
    FUN_1407d8e10(&lStack_118);
  }
  return;
}

