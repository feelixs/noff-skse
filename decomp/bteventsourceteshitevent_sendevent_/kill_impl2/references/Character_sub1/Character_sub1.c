
undefined8 UndefinedFunction_1407babc0(longlong *param_1,undefined8 param_2,char param_3)

{
  int *piVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined8 uStack_98;
  undefined4 uStack_90;
  longlong *plStack_88;
  longlong lStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  longlong lStack_68;
  longlong lStack_60;
  longlong *plStack_58;
  longlong *plStack_50;
  undefined1 auStack_48 [8];
  undefined8 uStack_40;

  uStack_40 = 0xfffffffffffffffe;
  plStack_88 = (longlong *)0x0;
  Character::sub(param_1,&plStack_88);
  if (plStack_88 != (longlong *)0x0) {
    iVar4 = (**(code **)(*plStack_88 + 8))();
    iVar5 = func_0x0001404ee010();
    if (iVar4 == iVar5) {
      plStack_58 = plStack_88;
      lStack_68 = 0;
      LookupObjectByRefHandle((longlong)plStack_88 + 300,&lStack_68);
      lVar2 = lStack_68;
      if (lStack_68 != 0) {
        plVar6 = (longlong *)TESObjectREFR::GetNiNode(param_1);
        plStack_50 = plVar6;
        lStack_60 = TESObjectREFR::GetNiNode(lVar2);
        if (plVar6 == (longlong *)0x0) {
          lVar8 = 0;
        }
        else {
          uVar7 = BSFixedString::Set(auStack_48,param_2);
          lVar8 = (**(code **)(*plVar6 + 0x150))(plVar6,uVar7);
          BSFixedString::Release(auStack_48);
        }
        if (lVar8 == 0) {
          uStack_98 = 0;
        }
        else {
          uStack_98 = NiAVObject::GetCollisionObject(lVar8);
        }
        if (param_1[0xc] == 0) {
          lStack_80 = 0;
        }
        else {
          lStack_80 = TESObjectCELL::GetHavokWorld();
        }
        lVar11 = 0;
        if (*(char *)(lVar2 + 0x1a) == '>') {
          lVar11 = lVar2;
        }
        if (((lVar11 == 0) || (lVar9 = func_0x00014065f140(lVar11,4), lVar9 == 0)) ||
           (lVar10 = NiAVObject::GetCollisionObject(lVar9), lVar10 == 0)) {
          lVar10 = 0;
          if ((lStack_60 == 0) || (lVar10 = NiAVObject::sub(lStack_60), lVar10 == 0)) {
            lVar9 = 0;
          }
          else {
            lVar9 = *(longlong *)(lVar10 + 0x10);
          }
        }
        if (((lVar8 != 0) && (lVar9 != 0)) &&
           ((uStack_98 != 0 && ((lVar10 != 0 && (lStack_80 != 0)))))) {
          if ((param_3 != '\0') && (lVar11 != 0)) {
            cVar3 = func_0x0001406b9ef0(lVar11);
            if (cVar3 != '\0') {
              Actor::EndDeferredKill(lVar11,0);
            }
            Actor::Kill_impl2(lVar11,param_1,0,1,1); // 1407bada1
          }
          uStack_98 = CONCAT44(DAT_143272c9c,gNiPoint3_Zero);
          uStack_90 = DAT_143272ca0;
          uStack_78 = gNiPoint3_Zero;
          uStack_74 = DAT_143272c9c;
          uStack_70 = DAT_143272ca0;
          lVar11 = func_0x00014014ef60();
          func_0x00014054b660(param_1 + 7,lVar11 + 0x5c8,&uStack_98);
          cVar3 = IsTaskPoolRequired();
          lVar11 = lStack_60;
          if (cVar3 == '\0') {
            lVar10 = lStack_80;
            cVar3 = func_0x000140e8e190(0,plStack_50,lStack_60,lVar8,lVar9,&uStack_98,&uStack_78,
                                        lStack_80,param_3);
            uVar12 = (undefined4)((ulonglong)lVar10 >> 0x20);
            if (cVar3 != '\0') {
              if (param_3 == '\0') {
                uVar13 = 0x461c4000;
              }
              else {
                uVar13 = 0x38d1b717;
              }
              func_0x000140e8d770(lVar11,uVar13);
              if (param_3 == '\0') {
                plVar6 = param_1 + 0x11;
                plStack_50 = plVar6;
                MutexRW::EnterWriteLock(plVar6);
                func_0x000140151a90(param_1 + 0xe,0xae);
                if (plVar6 != (longlong *)0x0) {
                  MutexRW::ExitWriteLock(plVar6);
                }
              }
              else {
                uVar13 = *(undefined4 *)((longlong)plStack_58 + 0x15c);
                uVar7 = GetOrCreateObjectRefHandle_Safe(lVar2,&lStack_80);
                func_0x00014016f270(param_1 + 0xe,0,uVar7,lVar8 + 0x10,lVar9 + 0x10,&uStack_98,
                                    &uStack_78,CONCAT44(uVar12,uVar13),0x38d1b717);
              }
              (**(code **)(*param_1 + 0x50))(param_1,0x80000000);
            }
          }
          else {
            if (param_3 == '\0') {
              uVar12 = 0x461c4000;
            }
            else {
              uVar12 = 0x38d1b717;
            }
            func_0x000140655dd0(gBSTaskPool,0,param_1,lVar2,lVar8,lVar9,&uStack_98,&uStack_78,
                                *(undefined4 *)((longlong)plStack_58 + 0x15c),uVar12,param_3);
          }
        }
      }
      if (lVar2 != 0) {
        LOCK();
        piVar1 = (int *)(lVar2 + 0x28);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((iVar4 - 1U & 0x3ff) == 0) {
          (**(code **)(*(longlong *)(lVar2 + 0x20) + 8))();
        }
      }
    }
  }
  if (plStack_88 != (longlong *)0x0) {
    LOCK();
    plVar6 = plStack_88 + 1;
    lVar2 = *plVar6;
    *(int *)plVar6 = (int)*plVar6 + -1;
    UNLOCK();
    if ((int)lVar2 == 1) {
      (**(code **)*plStack_88)(plStack_88,1);
    }
  }
  return 1;
}

