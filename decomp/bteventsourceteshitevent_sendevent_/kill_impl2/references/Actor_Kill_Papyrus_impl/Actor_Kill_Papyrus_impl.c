// 1409f6370
void UndefinedFunction_1409f6370
               (longlong param_1,undefined8 param_2,undefined1 param_3,undefined8 param_4,
               undefined4 param_5)

{
  char cVar1;
  uint in_stack_ffffffffffffffe8;

  cVar1 = (**(code **)(*(longlong *)(param_1 + 0xa0) + 0x20))();
  if ((cVar1 != '\0') && (cVar1 = Actor::IsGhost(param_1), cVar1 == '\0')) {
    func_0x0001409b7e10(param_1,&UNK_1419165e8,param_4,param_5,2);
    return;
  }
  if ((*(uint *)(param_1 + 200) & 0x1e00000) == 0xe00000) {
    Actor::Combat_unk1(param_1,0);
  }
  Actor::Kill_impl2(param_1,param_2,0,param_3,in_stack_ffffffffffffffe8 & 0xffffff00); //1409f63fd
  return;
}

