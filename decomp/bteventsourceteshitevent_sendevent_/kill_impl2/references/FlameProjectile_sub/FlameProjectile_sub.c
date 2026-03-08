
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong UndefinedFunction_1407ed8b0(longlong *param_1,float param_2)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  undefined4 *puVar6;
  longlong lVar7;
  char cVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  longlong lVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  longlong lVar15;
  longlong lVar16;
  longlong unaff_GS_OFFSET;
  undefined4 auStackX_8 [2];
  undefined4 auStackX_18 [2];
  undefined4 auStackX_20 [2];
  ulonglong in_stack_fffffffffffffeb8;
  longlong lStack_138;
  longlong lStack_130;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  longlong lStack_118;
  longlong lStack_110;
  longlong lStack_108;
  longlong lStack_100;
  longlong lStack_f8;
  longlong *plStack_f0;
  longlong lStack_e8;
  longlong lStack_e0;
  longlong lStack_d8;
  longlong lStack_d0;
  longlong *plStack_c8;
  longlong lStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined8 uStack_68;

  uStack_68 = 0xfffffffffffffffe;
  lVar16 = 0;
  lVar11 = param_1[0xc];
  if (lVar11 == 0) {
    return 0;
  }
  if (param_1[0x2b] == 0) {
    return 0;
  }
  if ((*(uint *)((longlong)param_1 + 0x1d4) >> 9 & 1) != 0) {
    return 0;
  }
  if ((*(uint *)((longlong)param_1 + 0x1d4) >> 0x1e & 1) == 0) {
    if ((*(uint *)(param_1[8] + 0x80) >> 2 & 1) == 0) {
      if ((param_1[0x15] == 0) && (param_1[0x14] == 0)) {
        return 0;
      }
    }
    else {
      if (((*(float *)(param_1 + 0x35) == 3.4028235e+38) && (*(float *)(param_1[8] + 0xa4) != 0.0))
         && (cVar8 = func_0x0001407edef0(param_1), cVar8 == '\0')) {
        func_0x0001407ee360(param_1);
        return 0;
      }
      fVar2 = *(float *)(param_1 + 0x35);
      *(float *)(param_1 + 0x35) = fVar2 - param_2;
      if (0.0 < fVar2 - param_2) {
        param_2 = *(float *)((longlong)param_1 + 0x1ac) - param_2;
        *(float *)((longlong)param_1 + 0x1ac) = param_2;
        if (0.0 < param_2) {
          return 0;
        }
        if ((*(int *)(*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)TlsIndex * 8)
                     + 0x2a08) < _DAT_1420f6960) &&
           (FUN_14153b45c(&DAT_1420f6960), _DAT_1420f6960 == -1)) {
          func_0x00014021f300(0x1420f6370);
                    /* WARNING: Subroutine does not return */
          FUN_14153b080(&UNK_1416c5a80);
        }
        uVar10 = (**(code **)(*param_1 + 0x380))(param_1);
        lVar11 = NiAVObject::LookupBoneNodeByName(uVar10,0x1420f6590,1);
        if (lVar11 != 0) {
          bVar5 = *(byte *)(lVar11 + 0xf4);
          uVar10 = (**(code **)(*param_1 + 0x380))(param_1);
          func_0x0001402e10d0(param_1,uVar10,bVar5 & 1);
        }
        if (_DAT_1420031f8 < *(float *)(param_1 + 0x35)) {
          *(float *)((longlong)param_1 + 0x1ac) = _DAT_142003210;
          FUN_140caf5b0((longlong)param_1 + 0x13c);
          return 0;
        }
        *(float *)((longlong)param_1 + 0x1ac) =
             (*(float *)(param_1 + 0x35) / _DAT_1420031f8) * (_DAT_142003210 - _DAT_142003228) +
             _DAT_142003228;
        FUN_140caf5b0((longlong)param_1 + 0x13c);
        return 0;
      }
    }
  }
  uStack_128 = *(undefined4 *)((longlong)param_1 + 0x54);
  uStack_124 = (undefined4)param_1[0xb];
  uStack_120 = *(undefined4 *)((longlong)param_1 + 0x5c);
  lVar12 = (**(code **)(*param_1 + 0x380))(param_1);
  if (lVar12 == 0) {
    puVar14 = (undefined4 *)&gNiMatrix33_Identity;
  }
  else {
    lVar12 = (**(code **)(*param_1 + 0x380))(param_1);
    puVar14 = (undefined4 *)(lVar12 + 0x7c);
  }
  uVar10 = (**(code **)(*param_1 + 0x380))(param_1);
  func_0x0001407e8100(param_1,uVar10,&uStack_128);
  auStackX_8[0] = (undefined4)param_1[0x25];
  lStack_130 = 0;
  LookupObjectByRefHandle(auStackX_8,&lStack_130);
  uVar9 = (undefined4)param_1[0x3a];
  if ((((*(uint *)((longlong)param_1 + 0x1d4) >> 0x1c & 1) != 0) && (param_1[0x2e] != 0)) &&
     (cVar8 = func_0x0001401462b0(), cVar8 == '\0')) {
    uVar9 = *(undefined4 *)(param_1[0x2e] + 0x110);
  }
  puVar6 = (undefined4 *)param_1[0x14];
  lStack_d0 = lVar16;
  if (puVar6 != (undefined4 *)0x0) {
    lStack_118 = 0;
    LookupREFRByHandle3(puVar6 + 6,&lStack_118);
    if ((lStack_118 != 0) && (*(char *)(lStack_118 + 0x1a) == '>')) {
      lStack_d0 = lStack_118;
    }
    if (lStack_118 != 0) {
      LOCK();
      piVar1 = (int *)(lStack_118 + 0x28);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar3 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lStack_118 + 0x20) + 8))();
      }
    }
  }
  uStack_b0 = 0;
  lStack_e8 = param_1[0x2b];
  lStack_d8 = lVar16;
  if ((*(uint *)((longlong)param_1 + 0x1d4) >> 10 & 1) == 0) {
    lStack_d8 = lStack_130;
  }
  lStack_e0 = lVar11;
  puVar13 = &uStack_128;
  if (puVar6 != (undefined4 *)0x0) {
    puVar13 = puVar6;
  }
  uStack_a8 = *puVar13;
  uStack_a4 = puVar13[1];
  uStack_a0 = puVar13[2];
  uStack_9c = *puVar14;
  uStack_98 = puVar14[1];
  uStack_94 = puVar14[2];
  uStack_90 = puVar14[3];
  uStack_8c = puVar14[4];
  uStack_88 = puVar14[5];
  uStack_84 = puVar14[6];
  uStack_80 = puVar14[7];
  uStack_7c = puVar14[8];
  lStack_c0 = param_1[0x2c];
  uStack_78 = uVar9;
  if (lStack_c0 == 0) {
    uStack_b8 = 0;
  }
  else {
    uStack_b8 = func_0x00014014c470(lStack_c0,5,1);
  }
  plStack_c8 = param_1;
  lVar11 = FUN_1407cf6a0(&lStack_e8);
  if (lVar11 != 0) {
    if (((param_1[0x15] != 0) || (param_1[0x14] != 0)) &&
       (cVar8 = (**(code **)(*param_1 + 0x510))(param_1), cVar8 != '\0')) {
      lVar12 = param_1[0x14];
      uVar9 = *(undefined4 *)(lVar12 + 0x10);
      uVar4 = *(undefined4 *)(lVar12 + 0x14);
      *(undefined4 *)(lVar11 + 0x130) = *(undefined4 *)(lVar12 + 0xc);
      *(undefined4 *)(lVar11 + 0x134) = uVar9;
      *(undefined4 *)(lVar11 + 0x138) = uVar4;
    }
    if (param_1[0x37] != 0) {
      *(longlong *)(lVar11 + 0x118) = param_1[0x37];
    }
  }
  if ((*(uint *)((longlong)param_1 + 0x1d4) >> 0xf & 1) != 0) {
    if (*(int *)(_VATS_MODE_GetSingleton + 0x20) == 4) {
      (**(code **)(*param_1 + 0x560))(param_1);
    }
    FlameProjectile::sub(param_1);
  }
  if ((0.0 < *(float *)(param_1[0x2b] + 0xcc)) &&
     ((*(uint *)((longlong)param_1 + 0x1d4) >> 10 & 1) != 0)) {
    auStackX_18[0] = *(undefined4 *)((longlong)param_1 + 300);
    lStack_138 = 0;
    LookupObjectByRefHandle(auStackX_18,&lStack_138);
    lVar12 = lStack_138;
    if (lStack_138 != 0) {
      lVar15 = lVar16;
      if (*(char *)(lStack_138 + 0x1a) == '>') {
        lVar15 = lStack_138;
      }
      lStack_108 = lVar15;
      if (lVar15 != 0) {
        auStackX_20[0] = (undefined4)param_1[0x25];
        lStack_110 = 0;
        LookupObjectByRefHandle(auStackX_20,&lStack_110);
        lVar7 = lStack_110;
        if ((lStack_110 != 0) && (*(char *)(lStack_110 + 0x1a) == '>')) {
          lVar16 = lStack_110;
        }
        lStack_100 = lVar15;
        lStack_f8 = lVar16;
        plStack_f0 = param_1;
        uVar10 = func_0x0001407f06f0();
        func_0x0001407f04b0(uVar10,&lStack_100);
        Actor::Kill_impl2(lVar15,lVar16,0,1,in_stack_fffffffffffffeb8 & 0xffffffffffffff00);  // 1407eddf5
        uVar10 = *(undefined8 *)(lVar16 + 0xf8);
        uVar9 = func_0x00014025ba90(param_1[0x2b]);
        FUN_1406df9b0(uVar10,lVar16,lStack_108 + 0x54,uVar9,lStack_108);
        if (lVar7 != 0) {
          LOCK();
          piVar1 = (int *)(lVar7 + 0x28);
          iVar3 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          lVar12 = lStack_138;
          if ((iVar3 - 1U & 0x3ff) == 0) {
            (**(code **)(*(longlong *)(lVar7 + 0x20) + 8))();
            lVar12 = lStack_138;
          }
        }
      }
    }
    if (lVar12 != 0) {
      LOCK();
      piVar1 = (int *)(lVar12 + 0x28);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if ((iVar3 - 1U & 0x3ff) == 0) {
        (**(code **)(*(longlong *)(lVar12 + 0x20) + 8))();
      }
    }
  }
  if (lStack_130 != 0) {
    LOCK();
    piVar1 = (int *)(lStack_130 + 0x28);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar3 - 1U & 0x3ff) == 0) {
      (**(code **)(*(longlong *)(lStack_130 + 0x20) + 8))();
    }
  }
  return lVar11;
}

