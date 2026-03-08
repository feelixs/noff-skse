
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1406bc4a0
ulonglong UndefinedFunction_1406bc4a0(longlong *param_1,longlong param_2,float param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined4 *puVar8;
  longlong lVar9;
  ulonglong uVar10;
  float fVar11;
  float fVar12;
  undefined4 auStackX_8 [2];
  undefined4 auStackX_20 [2];
  undefined1 auStack_68 [8];
  longlong lStack_60;
  longlong *plStack_58;
  undefined8 uStack_50;

  uStack_50 = 0xfffffffffffffffe;
  uVar10 = 0;
  puVar5 = (undefined1 *)register0x00000020;
  if ((((param_1 != gPlayerCharacter3) &&
       (puVar5 = (undefined1 *)(**(code **)(*param_1 + 0x4c8))(param_1,0), (char)puVar5 == '\0')) &&
      (puVar5 = (undefined1 *)Character::sub(param_1,0), (char)puVar5 == '\0')) &&
     ((param_1[0x1f] == 0 || (puVar5 = (undefined1 *)func_0x000140715b50(), (char)puVar5 == '\0'))))
  {
    uVar3 = *(uint *)(param_1 + 0x19);
    puVar5 = (undefined1 *)(ulonglong)uVar3;
    if (((uVar3 & 0x3c000) == 0) &&
       ((puVar5 = (undefined1 *)(ulonglong)(uVar3 & 0x1e00000), (uVar3 & 0x1e00000) != 0x800000 &&
        (puVar5 = (undefined1 *)0x0, -1 < (int)param_1[0x1d])))) {
      lVar6 = (**(code **)(*param_1 + 0x380))(param_1);
      puVar5 = (undefined1 *)0x0;
      if (lVar6 != 0) {
        lVar6 = param_1[8];
        uVar7 = Character::sub(param_1);
        fVar11 = (float)ActorValueOwner::sub(param_1 + 0x17,lVar6,uVar7);
        if (param_1[0x1f] != 0) {
          func_0x000140715330(param_1[0x1f],fVar11);
        }
        if (fVar11 <= param_3) {
          return 0;
        }
        if ((0.0 < param_3) && ((*(uint *)(param_1 + 0x19) & 0x1e00000) != 0x1000000)) {
          fVar12 = (float)func_0x000140416930(param_3,fVar11);
          uVar7 = func_0x0001401e5190();
          uVar3 = FUN_140cca350(uVar7,0xffffffff);
          if ((_DAT_141ffdff8 <= fVar12) && ((float)uVar3 * 2.3283064e-10 <= _DAT_141ffe010)) {
            Actor::Combat_unk1(param_1,8);  // 1406bc620
            if (param_1[0x1f] != 0) {
              func_0x0001407152b0(param_1[0x1f],fVar11 / _DAT_141ffdfe0);
              if (param_1[0x1f] != 0) {
                FUN_1407152f0(param_1[0x1f],fVar12);
              }
            }
            plStack_58 = param_1;
            uVar7 = func_0x0001406beac0();
            func_0x0001406be1c0(uVar7,&plStack_58);
            uVar10 = 1;
          }
        }
        if ((*(uint *)(param_1 + 0x19) & 0x1e00000) == 0x1000000) {
          uVar4 = gNullRefHandleId;
          if (param_2 != 0) {
            puVar8 = (undefined4 *)TESObjectREFR::sub(param_2,auStack_68);
            uVar4 = *puVar8;
          }
          if (param_1[0x1f] != 0) {
            auStackX_20[0] = uVar4;
            func_0x000140715350(param_1[0x1f],auStackX_20);
          }
        }
        if (0.0 < param_3) {
          return uVar10;
        }
        if (param_1[0x1f] == 0) {
          auStackX_8[0] = gNullRefHandleId;
        }
        else {
          func_0x000140715370(param_1[0x1f],auStackX_8);
        }
        lStack_60 = 0;
        LookupObjectByRefHandle(auStackX_8,&lStack_60);
        lVar6 = lStack_60;
        lVar9 = lStack_60;
        if (param_2 != 0) {
          lVar9 = param_2;
        }
        Actor::Kill_impl2(param_1,lVar9,0,1,0);  // 1406bc726
        if (lVar6 == 0) {
          return uVar10;
        }
        LOCK();
        piVar1 = (int *)(lVar6 + 0x28);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((iVar2 - 1U & 0x3ff) != 0) {
          return uVar10;
        }
        (**(code **)(*(longlong *)(lVar6 + 0x20) + 8))();
        return uVar10;
      }
    }
  }
  return (ulonglong)puVar5 & 0xffffffffffffff00;
}

