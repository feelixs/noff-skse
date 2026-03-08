
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 140349010
undefined8
UndefinedFunction_140349010
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,ulonglong param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  longlong *plVar2;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined8 uStack_10;

  uStack_10 = 0;
  uStack_18 = 0xffffffff;
  uStack_14 = 0xffffffff;
  FUN_14033e640(param_1,param_2,param_8,param_3,param_4,param_5,param_6,&uStack_10,&uStack_18,
                &uStack_14);
  param_4 = param_4 & 0xffffffff00000000;
  plVar2 = (longlong *)__RTDynamicCast(param_3,0,0x14203a9e8,0x14203bde8,param_4);
  if ((plVar2 != (longlong *)0x0) && (cVar1 = (**(code **)(plVar2[0x14] + 0x20))(), cVar1 == '\0'))
  {
    if ((plVar2 == _gPlayerCharacter) &&
       (cVar1 = (**(code **)(*plVar2 + 0x2f0))(plVar2), cVar1 != '\0')) {
      uStack_18 = 0xffffffff;
    }
    if ((*(uint *)(plVar2 + 0x19) & 0x1e00000) == 0xe00000) {
      Actor::Combat_unk1(plVar2,0);
    }
    Actor::Kill_impl2(plVar2,uStack_10,0,1,param_4 & 0xffffffffffffff00);  // 140349102
  }
  return 1;
}

