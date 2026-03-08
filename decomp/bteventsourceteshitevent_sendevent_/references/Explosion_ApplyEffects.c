
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 1407d12d0
void UndefinedFunction_1407d12d0(longlong *param_1)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  char cVar5;
  undefined8 uVar6;
  undefined4 *puVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined4 uVar10;
  uint uVar11;
  longlong *plVar12;
  byte bVar13;
  longlong *plVar14;
  longlong unaff_GS_OFFSET;
  float fVar15;
  float fVar16;
  undefined4 auStackX_8 [2];
  undefined4 auStackX_10 [2];
  undefined4 auStackX_18 [2];
  undefined1 auStackX_20 [8];
  longlong *plStack_188;
  longlong lStack_180;
  longlong lStack_178;
  undefined8 uStack_170;
  longlong *plStack_168;
  longlong *plStack_160;
  longlong lStack_158;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  byte bStack_148;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined8 uStack_120;
  undefined4 auStack_118 [20];
  float fStack_c8;

  uStack_120 = 0xfffffffffffffffe;
  *(uint *)((longlong)param_1 + 0x144) = *(uint *)((longlong)param_1 + 0x144) | 4;
  plVar12 = param_1 + 0x19;
  do {
    do {
      if ((plVar12 == (longlong *)0x0) ||
         ((plStack_168 = (longlong *)plVar12[1], plStack_168 == (longlong *)0x0 && (*plVar12 == 0)))
         ) {
        return;
      }
      puVar7 = (undefined4 *)*plVar12;
      plVar12 = plStack_168;
    } while ((puVar7 == (undefined4 *)0x0) || (((uint)puVar7[1] >> 2 & 1) != 0));
    auStackX_8[0] = *puVar7;
    plStack_188 = (longlong *)0x0;
    LookupObjectByRefHandle(auStackX_8,&plStack_188);
    plVar9 = plStack_188;
    if (plStack_188 != (longlong *)0x0) {
      puVar1 = (uint *)(plStack_188 + 2);
      uVar11 = *puVar1;
      if (((uVar11 >> 0x17 & 1) == 0) && ((uVar11 >> 0xb & 1) == 0)) {
        fVar16 = *(float *)((longlong)plStack_188 + 0x5c) - *(float *)((longlong)param_1 + 0x5c);
        fVar15 = *(float *)((longlong)plStack_188 + 0x54) - *(float *)((longlong)param_1 + 0x54);
        fVar16 = SQRT(fVar15 * fVar15 +
                      (*(float *)(plStack_188 + 0xb) - *(float *)(param_1 + 0xb)) *
                      (*(float *)(plStack_188 + 0xb) - *(float *)(param_1 + 0xb)) + fVar16 * fVar16)
        ;
        fVar15 = (float)func_0x000140418df0(*(undefined4 *)((longlong)param_1 + 0xb4),fVar16);
        if (*(float *)(param_1 + 0x17) <= 0.0) {
          fVar16 = 1.0;
        }
        else {
          fVar16 = (float)func_0x000140418df0(*(float *)(param_1 + 0x17),fVar16);
        }
        plVar14 = (longlong *)0x0;
        if (*(char *)((longlong)plVar9 + 0x1a) == '>') {
          plVar14 = plVar9;
        }
        if ((plVar14 == (longlong *)0x0) || (plVar14 != gPlayerCharacter3)) {
          bVar13 = 0;
        }
        else {
          bVar13 = 1;
        }
        if (((0.0 < fVar16) && (bVar13 != 0)) &&
           (lVar8 = *(longlong *)(param_1[8] + 0x90), lVar8 != 0)) {
          uVar6 = (**(code **)(*param_1 + 0x380))(param_1);
          func_0x00014029e0c0(lVar8,fVar16,uVar6);
        }
        plVar12 = plStack_168;
        if (0.0 < fVar15) {
          if (((uint)puVar7[1] >> 1 & 1) != 0) {
            lVar8 = *plVar9;
            uVar6 = (**(code **)(*param_1 + 0x288))(param_1);
            (**(code **)(lVar8 + 0x280))(plVar9,uVar6);
          }
          if (plVar14 != (longlong *)0x0) {
            Character::sub(plVar14);
          }
          puVar7 = (undefined4 *)(**(code **)(*param_1 + 0x288))(param_1);
          auStackX_10[0] = gNullRefHandleId;
          if (puVar7 != (undefined4 *)0x0) {
            auStackX_10[0] = *puVar7;
          }
          lStack_178 = 0;
          LookupObjectByRefHandle(auStackX_10,&lStack_178);
          uVar10 = gNullRefHandleId;
          if (lStack_178 != 0) {
            puVar7 = (undefined4 *)GetOrCreateObjectRefHandle_Safe(lStack_178,auStackX_20);
            uVar10 = *puVar7;
          }
          lStack_180 = 0;
          auStackX_18[0] = uVar10;
          LookupObjectByRefHandle(auStackX_18,&lStack_180);
          lVar8 = param_1[0x23];
          if (lVar8 == 0) {
            lVar8 = param_1[8];
          }
          uVar10 = *(undefined4 *)(lVar8 + 0x14);
          if ((*(int *)(*(longlong *)
                         (*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)TlsIndex * 8) + 0x2a08)
               < DAT_1420f8920) && (FUN_14153b45c(&DAT_1420f8920), DAT_1420f8920 == -1)) {
            FUN_1401a7d30(&DAT_1420f7690);
                    /* WARNING: Subroutine does not return */
            FUN_14153b080(&DAT_1416c8170);
          }
          lVar8 = lStack_180;
          plVar12 = plStack_188;
          LOCK();
          *(int *)(plVar9 + 5) = (int)plVar9[5] + 1;
          UNLOCK();
          plStack_160 = plStack_188;
          if (lStack_180 != 0) {
            LOCK();
            *(int *)(lStack_180 + 0x28) = *(int *)(lStack_180 + 0x28) + 1;
            UNLOCK();
          }
          lStack_158 = lStack_180;
          uStack_14c = 0;
          bStack_148 = bStack_148 & 0xf0;
          uStack_150 = uVar10;
          BSTEventSource_SendEvent(0x1420f7c68,&plStack_160);  // 1407d15bd
          if (lStack_158 != 0) {
            LOCK();
            piVar2 = (int *)(lStack_158 + 0x28);
            iVar3 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            plVar12 = plStack_188;
            lVar8 = lStack_180;
            if ((iVar3 - 1U & 0x3ff) == 0) {
              (**(code **)(*(longlong *)(lStack_158 + 0x20) + 8))();
              plVar12 = plStack_188;
              lVar8 = lStack_180;
            }
          }
          if (plStack_160 != (longlong *)0x0) {
            LOCK();
            plVar12 = plStack_160 + 5;
            lVar4 = *plVar12;
            *(int *)plVar12 = (int)*plVar12 + -1;
            UNLOCK();
            plVar12 = plStack_188;
            lVar8 = lStack_180;
            if (((int)lVar4 - 1U & 0x3ff) == 0) {
              (**(code **)(plStack_160[4] + 8))();
              plVar12 = plStack_188;
              lVar8 = lStack_180;
            }
          }
          fVar16 = (float)func_0x0001407d0d20(param_1);
          if (((*puVar1 >> 0x17 & 1) != 0) && ((int)param_1[0x1f] == _gBarterMenuActorRefHandleId))
          {
            PlayerCharacter::sub(_gPlayerCharacter,9,plVar12);
          }
          if (plVar14 == (longlong *)0x0) {
            (**(code **)(*plVar12 + 0x210))(plVar12,fVar16 * fVar15,0);
          }
          else {
            uStack_140 = *(undefined4 *)((longlong)param_1 + 0x54);
            uStack_13c = (undefined4)param_1[0xb];
            uStack_138 = *(undefined4 *)((longlong)param_1 + 0x5c);
            cVar5 = func_0x0001407d2fb0(param_1,&uStack_140);
            if (cVar5 != '\0') {
              FUN_1407dab30(auStack_118);
              if (((*(uint *)((longlong)param_1 + 0x144) >> 7 & 1) == 0) &&
                 (plVar9 = (longlong *)func_0x0001407d0de0(param_1), plVar9 != plVar14)) {
                func_0x0001407db590(auStack_118,plVar9,plVar14,param_1,fVar16 * fVar15);
                TESObjectREFR::sub(plVar14,auStack_118); // 1407d16e2
              }
              lVar4 = *(longlong *)(param_1[8] + 0x70);
              if (lVar4 != 0) {
                if (param_1[0x22] == 0) {
                  plVar9 = (longlong *)func_0x0001407d0de0(param_1);
                  if ((plVar9 != (longlong *)0x0) &&
                     ((plVar9 != plVar14 || (*(int *)(lVar4 + 0x70) < 1)))) {
                    plVar9 = (longlong *)(**(code **)(*plVar9 + 0x2e0))(plVar9,3);
                    goto LAB_1407d1757;
                  }
                }
                else {
                  plVar9 = (longlong *)(**(code **)(*(longlong *)(param_1[0x22] + 0x10) + 0x60))();
                  if (((plVar9 != plVar14) || (*(int *)(lVar4 + 0x70) < 1)) && (param_1[0x22] != 0))
                  {
                    plVar9 = (longlong *)(param_1[0x22] + 0x10);
LAB_1407d1757:
                    if (plVar9 != (longlong *)0x0) {
                      (**(code **)(*plVar9 + 8))(plVar9,lVar4,0,plVar14,0x3f800000,0,0,0);
                    }
                  }
                }
              }
              cVar5 = (**(code **)(*plVar14 + 0x4c8))(plVar14,1);
              if (cVar5 == '\0') {
                uVar11 = *(uint *)(param_1[8] + 0xdc) >> 2 & 3;
                if (uVar11 != 1) {
                  if (uVar11 == 2) {
                    bVar13 = func_0x000140418510(plVar14 + 0x17,(int)fStack_c8);
                  }
                  else {
                    if (uVar11 != 3) goto LAB_1407d1879;
                    bVar13 = bVar13 ^ 1;
                  }
                  if (bVar13 == 0) goto LAB_1407d1879;
                }
                if ((plVar14[0x1f] != 0) && (_DAT_142006870 < fVar15)) {
                  uStack_130 = *(undefined4 *)((longlong)param_1 + 0x54);
                  uStack_12c = (undefined4)param_1[0xb];
                  uStack_128 = *(undefined4 *)((longlong)param_1 + 0x5c);
                  FUN_140710c80(plVar14[0x1f],plVar14,&uStack_130,0);
                }
              }
              else {
                if (bVar13 == 0) {
                  uVar6 = (**(code **)(*plVar14 + 0x380))(plVar14);
                }
                else {
                  uVar6 = (**(code **)(*_gPlayerCharacter + 0x378))(_gPlayerCharacter,0);
                }
                NiNode::sub(uVar6,1,1,0,1);
                uStack_170 = 0;
                NiAVObject::UpdateObjectUpwards(uVar6,&uStack_170);
              }
LAB_1407d1879:
              FUN_1407dad30(auStack_118);
            }
          }
          if (lVar8 != 0) {
            LOCK();
            piVar2 = (int *)(lVar8 + 0x28);
            iVar3 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            plVar12 = plStack_188;
            if ((iVar3 - 1U & 0x3ff) == 0) {
              (**(code **)(*(longlong *)(lVar8 + 0x20) + 8))();
              plVar12 = plStack_188;
            }
          }
          plVar9 = plVar12;
          plVar12 = plStack_168;
          if (lStack_178 != 0) {
            LOCK();
            piVar2 = (int *)(lStack_178 + 0x28);
            iVar3 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            plVar9 = plStack_188;
            if ((iVar3 - 1U & 0x3ff) == 0) {
              (**(code **)(*(longlong *)(lStack_178 + 0x20) + 8))();
              plVar9 = plStack_188;
              plVar12 = plStack_168;
            }
          }
        }
      }
    }
    if (plVar9 != (longlong *)0x0) {
      LOCK();
      plVar14 = plVar9 + 5;
      lVar8 = *plVar14;
      *(int *)plVar14 = (int)*plVar14 + -1;
      UNLOCK();
      if (((int)lVar8 - 1U & 0x3ff) == 0) {
        (**(code **)(plVar9[4] + 8))();
      }
    }
  } while( true );
}

