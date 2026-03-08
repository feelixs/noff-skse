
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
// 140663720
void UndefinedFunction_140663720(longlong *param_1)

{
  char cVar1;

  func_0x0001402ed460();
  if (((((*(uint *)((longlong)param_1 + 0x204) >> 0x12 & 1) == 0) &&
       ((*(uint *)(param_1 + 2) >> 0xb & 1) == 0)) && ((*(uint *)(param_1 + 2) >> 5 & 1) == 0)) &&
     (cVar1 = (**(code **)(*param_1 + 0x4c8))(param_1,0), cVar1 == '\0')) {
    Character::sub(param_1,_gPlayerCharacter,0);
    if ((param_1[0x1f] != 0) && (cVar1 = ActorProcess::sub(), cVar1 != '\0')) {
      return;
    }
    *(undefined4 *)(param_1 + 0x21) = gNullRefHandleId;
    FUN_140655640(gBSTaskPool,param_1,0,0,1,0);
  }
  return;
}

